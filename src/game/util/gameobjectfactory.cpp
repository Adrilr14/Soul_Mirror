#include <game/util/gameobjectfactory.hpp>
#include <ecs/man/entityManager.hpp>
#include <game/cmp/CollisionComponent.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/StaticComponent.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <game/cmp/CameraComponent.hpp>
#include <game/cmp/HPComponent.hpp>
#include <game/cmp/IAComponent.hpp>
#include "../../game/cmp/DimensionsComponent.hpp"
#include <include_json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

Entity_t& GameOBjectFactory_t::createEntity(float whd,int32_t ax,int32_t ay,int32_t az,const std::string_view nombre,const std::string_view ruta)
const {
	//auto& e = m_Entities.emplace_back(ax,ay,az);
	
	auto& e  = m_EntMan.createEntity(nombre);
	auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
	auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
	rn.loadFilesNames(ruta, "xd");
    ph.vx = 0.25;
    ph.vz = 0.25;
    ph.x = ax; ph.y = ay; ph.z = az;
    ph.initx = ax, ph.inity = ay; ph.initz = az;
    
    //ph.vy = 1.0;
    //el componente direccion no se si lo vamos a usar para todas las entitys o solo el player, de momento lo dejo comentado
    //auto& direccion = entManager.addComponent<DirecComponent_t>(e);
    //direccion.dir = 4;
    //e.addComponent(direccion);
	
	return e;
}

void GameOBjectFactory_t::createStaticEntity(const std::string_view nombre,const std::string_view rutamodel, const std::string_view rutatexture) const{
    auto& e = m_EntMan.createEntity(nombre);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& sc = m_EntMan.addComponent<StaticComponent_t>(e);
    auto& dim = m_EntMan.addComponent<DimensionsComponent_t>(e);
    m_EntMan.addComponent<CollisionComponent_t>(e);
    dim.setHeight(3.2936);
    dim.setWidth(90.5732);
    dim.setLength(4.117);
    rn.loadFilesNames(rutamodel, rutatexture);
}

void GameOBjectFactory_t::createPlayer(float ax, float ay, float az, const std::string_view rutatexture)
const {
    //std::cout<<"entro al create player";
    //auto& e = createEntity(whd,ax,ay,az,"player","media/z1_p1.STL");
    auto& e  = m_EntMan.createEntity("player");
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& input = m_EntMan.addComponent<InputComponent_t>(e);
    auto& direccion = m_EntMan.addComponent<DirecComponent_t>(e);
    auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
    auto& dimension = m_EntMan.addComponent<DimensionsComponent_t>(e);
    m_EntMan.addComponent<CollisionComponent_t>(e);
    //std::cout<<e.getEntityID()<<"\n";
    hp.life = 100;
    ph.vx = 0.25;
    ph.vz = 0.25;
    ph.x = ax; ph.y = ay; ph.z = az;
    rn.loadFilesNames(" ", rutatexture);
    dimension.setHeight(4.0);
    dimension.setWidth(4.0);
    dimension.setLength(4.0);
}

void GameOBjectFactory_t::createEnemy(int32_t ax, int32_t ay, int32_t az, const std::string_view nombre, const std::string_view model, const std::string_view texture) 
const{
    auto& e = m_EntMan.createEntity(nombre);
    auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    ph.x = ax; ph.y = ay; ph.z = az;
    ph.initx = ax, ph.inity = ay; ph.initz = az;
    //los tipos deIA que se contemplan son los siguientes: fuzzylogic,bhtree,stbehav,simple
    auto& ia = m_EntMan.addComponent<IAComponent_t>(e);
}

void GameOBjectFactory_t::createCamera(){
    std::string_view name = "camera";
    auto& e = m_EntMan.createEntity(name);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& cam = m_EntMan.addComponent<CameraComponent_t>(e);
}

void GameOBjectFactory_t::readLevel(std::string_view path){
    std::ifstream archivo(path.data());
    std::stringstream buff;
    buff << archivo.rdbuf();
    std::string jsonString = buff.str();
    json j = json::parse(jsonString);
    archivo.close();
    float x,y,z = 0;
    std::string nombre,modelpath, texturepath;
    //como player solo hay uno accedo a sus valores directamente
    x = j["PLAYER"]["x"].get<double>();
    y = j["PLAYER"]["y"].get<double>();
    z = j["PLAYER"]["z"].get<double>();
    texturepath = j["PLAYER"]["TEXTURE"].get<std::string>();
    createPlayer(x,y,z,texturepath);
    //como static hay mas, recorro los que hay en el for y accedo a ellos con su ID
    //va leyendo uno a uno y hace la llamada para crearlos al final
    int itemCount = j["STATIC"].size();
    for(int i = 0; i < itemCount; i++){
        std::string id = std::to_string(i);
        auto staticActual = j["STATIC"][id];
        nombre = staticActual["NAME"].get<std::string>();
        modelpath = staticActual["MODEL"].get<std::string>();
        texturepath = staticActual["TEXTURE"].get<std::string>(); 
        createStaticEntity(nombre,modelpath,texturepath);
    }
    //el mismo proceso que antes pero ahora para los enemigos
    itemCount = j["ENEMY"].size();
    for(int i = 0; i < itemCount; i++){
        std::string id = std::to_string(i);
        auto enemyActual = j["ENEMY"][id];
        x = enemyActual["x"].get<double>();
        y = enemyActual["y"].get<double>();
        z = enemyActual["z"].get<double>();
        nombre = enemyActual["NAME"].get<std::string>();
        modelpath = enemyActual["MODEL"].get<std::string>();
        texturepath = enemyActual["TEXTURE"].get<std::string>();
        createEnemy(x,y,z,nombre,modelpath,texturepath);
    }
}