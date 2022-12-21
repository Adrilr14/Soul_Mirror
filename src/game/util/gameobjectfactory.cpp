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
#include <game/cmp/DimensionsComponent.hpp>
#include <game/cmp/ZoneComponent.hpp>
#include <include_json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <EventManager/EventManager.hpp>
using json = nlohmann::json;


void GameOBjectFactory_t::createStaticEntity(float x,float y,float z,float rx,float ry,float rz,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const{
    
    std::cout<<"entro al static\n";
    auto& e = m_EntMan.createEntity(nombre);
    std::string a = rutamodel.data();
    std::string b = "media/obj/z1_p1.obj";

    if(a.compare(b) == 0){
        auto& dim = m_EntMan.addComponent<DimensionsComponent_t>(e);    
        m_EntMan.addComponent<CollisionComponent_t>(e);  
        dim.setHeight(3.2936);
        dim.setWidth(90.5732);
        dim.setLength(4.117);
    }
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    m_EntMan.addComponent<StaticComponent_t>(e);
    rn.loadFilesNames(rutamodel, rutatexture);
    phy.x = x;  phy.rx = rx;
    phy.y = y;  phy.ry = ry;
    phy.z = z;  phy.rz = rz; 
}

void GameOBjectFactory_t::createPlayer(float ax, float ay, float az, const std::string_view rutamodel, const std::string_view rutatexture)
const {
    std::cout<<"Estoy en el gameobject y entro al create player\n";
    std::cout<<"Estoy en el gameobject y este es el size del vector: "<<m_EntMan.getEntities().size()<<"\n";
    auto& e  = m_EntMan.createEntity("player");
    std::cout<<"entro al create player22\n";
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& dim = m_EntMan.addComponent<DimensionsComponent_t>(e);
    m_EntMan.addComponent<CollisionComponent_t>(e);
    m_EntMan.addComponent<InputComponent_t>(e);
    m_EntMan.addComponent<DirecComponent_t>(e);
    //auto& zone = m_EntMan.addComponent<ZoneComponent_t>(e);
    auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
    std::cout<<"he asignado todos los componentes al player\n";
    hp.life = 100;
    ph.vx = 0.25;
    ph.vz = 0.25;
    ph.x = ax; ph.y = ay; ph.z = az;
    dim.setHeight(5.0);
    dim.setWidth(5.0);
    dim.setLength(5.0);
    rn.loadFilesNames(rutamodel, rutatexture);
}

void GameOBjectFactory_t::createEnemy(float ax, float ay, float az, const std::string_view nombre, const std::string_view rutamodel, const std::string_view rutatexture) 
const{
    std::cout<<"entro al create enemy\n";
    auto& e = m_EntMan.createEntity(nombre);
    auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& ia = m_EntMan.addComponent<IAComponent_t>(e);
    ph.x = ax; ph.y = ay; ph.z = az;
    ph.initx = ax, ph.inity = ay; ph.initz = az;
    rn.loadFilesNames(rutamodel, rutatexture);
    //los tipos deIA que se contemplan son los siguientes: fuzzylogic,bhtree,stbehav,simple
    
}

void GameOBjectFactory_t::createCamera(){
    std::cout<<"entro al create camera\n";
    std::string name = "camera";
    auto& e = m_EntMan.createEntity(name);
    m_EntMan.addComponent<PhysicsComponent_t>(e);
    m_EntMan.addComponent<CameraComponent_t>(e);
}

void GameOBjectFactory_t::readLevel(EventInfo info) noexcept{
    //primero siempre abro el archivo json
    //std::cout<<"Estoy en el gameobject y la zona que me llega por parametro es: "<<info.zone<<"\n";
    std::cout<<"entro al readlevel\n";
    std::cout<<"Estoy en el gameobject y este es el size del vector: "<<m_EntMan.getEntities().size()<<"\n";
    std::string zona = "zone_";
    zona += std::to_string(info.zone);
    zona += ".json";
    //auto& zonevec = m_EntMan.getComponents<ZoneComponent_t>();
    //zona += std::to_string(zonevec[0].zone);
    std::ifstream archivo(zona);
    std::stringstream buff;
    buff << archivo.rdbuf();
    std::string jsonString = buff.str();
    json j = json::parse(jsonString);
    archivo.close();
    //xyz posiciones iniciales, rxryrz rotaciones iniciales
    float x,y,z,rx,ry,rz = 0;
    std::string nombre,modelpath, texturepath;  
    //saco la posicion del player
    x = j["PLAYER"]["x"].get<double>();
    y = j["PLAYER"]["y"].get<double>();
    z = j["PLAYER"]["z"].get<double>();
    //si esta vacio, creo el player y la camara, que seran siempre las 2 primeras entitys del array
    //if(m_EntMan.IsEmpty()){
        modelpath = j["PLAYER"]["MODEL"].get<std::string>();
        texturepath = j["PLAYER"]["TEXTURE"].get<std::string>();
        createPlayer(x,y,z,modelpath,texturepath);
        createCamera();
    //}
    //else{
        //si no esta vacio, borro el array de entitys excepto el player y la camara
        //ademas tengo que reasignar la posicion del player
        //std::cout<<"entro en el borrado de entitys\n";
        //m_EntMan.deleteEntities();
        //auto& e = m_EntMan.getEntities()[0];
        //if(e.template getComponent<PhysicsComponent_t>()){
        //    auto* phy = e.template getComponent<PhysicsComponent_t>();
        //    phy->x = x;
        //    phy->y = y;
        //    phy->z = z;
        //}
    //}
    
    //vacio o no, tengo que crear las cosas del entorno igualmente 
    //como static hay mas, recorro los que hay en el for y accedo a ellos con su ID
    //va leyendo uno a uno y hace la llamada para crearlos al final
    int itemCount = 0;
    if(j["STATIC"].size() > 0){
        itemCount = j["STATIC"].size();
        for(int i = 0; i < itemCount; i++){
            std::string id = std::to_string(i);
            auto staticActual = j["STATIC"][id];
            x = staticActual["x"].get<double>();
            y = staticActual["y"].get<double>();
            z = staticActual["z"].get<double>();
            rx = staticActual["x"].get<double>();
            ry = staticActual["y"].get<double>();
            rz = staticActual["z"].get<double>();
            nombre = staticActual["NAME"].get<std::string>();
            modelpath = staticActual["MODEL"].get<std::string>();
            texturepath = staticActual["TEXTURE"].get<std::string>(); 
            createStaticEntity(x,y,z,rx,ry,rz,nombre,modelpath,texturepath);
        }
    }
    //el mismo proceso que antes pero ahora para los enemigos
    //tengo que mirar que haya enemigos, porque no en todas las zonas habra
    if(j["ENEMY"].size() > 0){
        itemCount = j["ENEMY"].size();
        for(int i = 0; i < itemCount; i++){
            std::string id = std::to_string(i);
            auto enemyActual = j["ENEMY"][id];
            x = enemyActual["x"].get<double>();
            y = enemyActual["y"].get<double>();
            z = enemyActual["z"].get<double>();
            rx = enemyActual["x"].get<double>();
            ry = enemyActual["y"].get<double>();
            rz = enemyActual["z"].get<double>();
            std::cout<<x<<" "<<y<<" "<<z<<"\n";
            nombre = enemyActual["NAME"].get<std::string>();
            modelpath = enemyActual["MODEL"].get<std::string>();
            texturepath = enemyActual["TEXTURE"].get<std::string>();
            createEnemy(x,y,z,nombre,modelpath,texturepath);
        }
    }
    //una vez tenemos todas las entitys en el array, lanzamos el evento para que el motor grafico las cree
    //EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
    
}

void GameOBjectFactory_t::prueba(EventInfo info){
    std::cout<<"Estoy en prueba de game object y este es el size del vector: "<<m_EntMan.getEntities().size()<<"\n";
}

void GameOBjectFactory_t::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Change_Zone,std::bind(&GameOBjectFactory_t::readLevel, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Probando,std::bind(&GameOBjectFactory_t::prueba, this, std::placeholders::_1)));
}
