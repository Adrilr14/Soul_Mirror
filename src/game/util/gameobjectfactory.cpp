#include "gameobjectfactory.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../cmp/CollisionComponent.hpp"
#include "../cmp/DirecComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/StaticComponent.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/CameraComponent.hpp"
#include "../cmp/HPComponent.hpp"
#include "../cmp/IAComponent.hpp"
#include "../cmp/DimensionsComponent.hpp"
#include "../cmp/ShootComponent.hpp"
#include "../cmp/ZoneComponent.hpp"
#include "../cmp/ItemComponent.hpp"
#include "../cmp/EnemyComponent.hpp"
#include <include_json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using json = nlohmann::json;


//Funcion para crear Entidades de tipo Estáticas que solo tengan colision. Ejemplo vallas,casas,etc.
void GameObjectFactory_t::createStaticEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const{
    
    auto& e = m_EntMan.createEntity(nombre);
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    m_EntMan.addComponent<StaticComponent_t>(e);
    m_EntMan.addComponent<CollisionComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    rn.loadFilesNames(rutamodel, rutatexture);
    rn.loadDimensions(width,height,length);   

    phy.x = x;  phy.rx = rx; 
    phy.y = y;  phy.ry = ry; 
    phy.z = z;  phy.rz = rz; 
}

//Funcion para crear Entidades de tipo Estáticas que solo tengan colision. Ejemplo vallas,casas,etc.
void GameObjectFactory_t::createNonStaticEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const{
    
    auto& e = m_EntMan.createEntity(nombre);
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    rn.loadFilesNames(rutamodel, rutatexture);
    rn.loadDimensions(width,height,length);   

    phy.x = x;  phy.rx = rx; 
    phy.y = y;  phy.ry = ry; 
    phy.z = z;  phy.rz = rz; 
}

//Función para crear Entidades que son Estáticas colisionables pero que no se ven
void GameObjectFactory_t::createStaticEntityNonRender(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel) const{
    
    auto& e = m_EntMan.createEntity(nombre);
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& ren = m_EntMan.addComponent<RenderComponent_t>(e);
    m_EntMan.addComponent<StaticComponent_t>(e);
    m_EntMan.addComponent<CollisionComponent_t>(e);
    ren.loadDimensions(width,height,length);
    ren.isVisible = false;
    phy.x = x;  phy.rx = rx; 
    phy.y = y;  phy.ry = ry; 
    phy.z = z;  phy.rz = rz; 
}

void GameObjectFactory_t::createPlayer(float x,float y,float z,const std::string_view rutamodel, const std::string_view rutatexture)
const {
    //Primero checkeamos si hay ya un jugador creado
    //Como el personaje siempre se crea primero
    auto& entidades = m_EntMan.getEntities();
    if(entidades.size() == 0){
        auto& e = m_EntMan.createEntity("player");
        auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
        auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
        auto& items = m_EntMan.addComponent<ItemComponent_t>(e);    
        //auto& dim = m_EntMan.addComponent<DimensionsComponent_t>(e);
        m_EntMan.addComponent<CollisionComponent_t>(e);
        m_EntMan.addComponent<InputComponent_t>(e);
        m_EntMan.addComponent<DirecComponent_t>(e);
        //bulletEngine_t.get()->createObjects(x,y,z);
        //auto& zone = m_EntMan.addComponent<ZoneComponent_t>(e);
        auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
        hp.life = 100;
        ph.vx = 0.5;
        ph.vz = 0.5;
        ph.x = x;
        ph.y = y;
        ph.z = z;
       
        rn.loadDimensions(3.135,2.94,10.195);
        rn.loadFilesNames(rutamodel, rutatexture);
        //Sword_t newItem;
        //newItem.addManager(m_EntMan);
        //items.AddItem(newItem);
        Sword_t newSword;
        newSword.addManager(m_EntMan);
        items.AddSword(newSword);
        Shield_t newShield;
        newShield.addManager(m_EntMan);
        items.AddShield(newShield);
        createWeapons("Sword","media/obj/Bosque/espada.obj","media/Texturas/Bosque/espada/espada" );
        createWeapons("Escudo","media/obj/Bosque/Barril.obj","media/Texturas/Bosque/Player/Player" );
        //createWeapons("Arco","media/arco.obj");
        //createWeapons("Bomba","media/bomba.obj");
        //bulletEngine_t->createCharacter(x,y,z); //TODO: Quitar el acoplado
    }
}

void GameObjectFactory_t::createWeapons(const std::string_view name,const std::string_view ruta,const std::string_view texture) const{
    auto& e = m_EntMan.createEntity(name);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    ph.y = -250.0;
    rn.loadDimensions(0.615575,2.81326,7.18395); //Dimensiones armas  CAMBIARRRRRR
    rn.loadFilesNames(ruta, texture);
    
}

void GameObjectFactory_t::createEnemy(float ax, float ay, float az, const std::string_view nombre, const std::string_view rutamodel, const std::string_view rutatexture,int type) 
const{
    std::cout<<"entro al create enemy\n";
    //std::cout<<"entro al create enemy\n";
    auto& e = m_EntMan.createEntity(nombre);
    auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& ia = m_EntMan.addComponent<IAComponent_t>(e);
    m_EntMan.addComponent<EnemyComponent_t>(e);
    ph.x = ax; ph.y = ay; ph.z = az;
    ph.initx = ax, ph.inity = ay; ph.initz = az;
    rn.loadFilesNames(rutamodel, rutatexture);
    switch(type){
        case 0:
            ia.type = erizo;
            break;
        case 1:
            ia.type = seta;
            break;
        case 2:
            ia.type = spider;
            break;
    }
    //los tipos deIA que se contemplan son los siguientes: fuzzylogic,bhtree,stbehav,simple
}


void GameObjectFactory_t::createShot(EventInfo info){
    //std::cout<<"entro a createShot\n";
    auto& e = m_EntMan.createEntity("bala");
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& shot = m_EntMan.addComponent<ShootComponent_t>(e);
    phy.x= info.posX;   phy.initx = info.posX;  
    phy.z = info.posZ;  phy.initz = info.posZ;
    phy.vx = 0.35;      phy.vz = 0.35;
    shot.angle = info.angle;
    shot.right = info.shotdir;
    //shot.angle = 0;
    info.id = e.getEntityID();
    std::cout << "A ver no se donde cojones aparece " << phy.x << " " << phy.z << std::endl;
    //std::cout<<"ID de la bala creada: "<<info.id<<"\n";
    EventManager::getInstancia().addEvent(Event{EventType::Create_Shot_MG,info});
    //Añadir un evento que cree una bala en el RavenGraphics para que se pueda renderizar
    
}


void GameObjectFactory_t::createCamera(){
    std::cout<<"entro al create camera\n";
    std::string name = "camera";
    auto& e = m_EntMan.createEntity(name);
    m_EntMan.addComponent<PhysicsComponent_t>(e);
    m_EntMan.addComponent<CameraComponent_t>(e);
}

void GameObjectFactory_t::readLevel(EventInfo info) noexcept{
    //primero siempre abro el archivo json
    //std::cout<<"Estoy en el gameobject y la zona que me llega por parametro es: "<<info.zone<<"\n";
    std::cout<<"entro al readlevel\n";
    std::cout<<"Estoy en el gameobject y este es el size del vector: "<<m_EntMan.getEntities().size()<<"\n";
    std::string zona = "Zonas/zone_";
    auto numberZone = std::to_string(info.zone);
    std::cout << "La zona " << numberZone << " " << std::endl;
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
    float x,y,z,rx,ry,rz,sx,sy,sz = 0;
    std::string nombre,modelpath,texturepath;  
    ////saco la posicion del player
    x = 0;
    y = 0;
    z = 0;
    ////si esta vacio, creo el player y la camara, que seran siempre las 2 primeras entitys del array
    ////if(m_EntMan.IsEmpty()){
    //    modelpath = j["PLAYER"]["MODEL"].get<std::string>();
    //    texturepath = j["PLAYER"]["TEXTURE"].get<std::string>();
    ////}
    ////else{
    //    //si no esta vacio, borro el array de entitys excepto el player y la camara
    //    //ademas tengo que reasignar la posicion del player
    //    //std::cout<<"entro en el borrado de entitys\n";
    //    //m_EntMan.deleteEntities();
    //    //auto& e = m_EntMan.getEntities()[0];
    //    //if(e.template getComponent<PhysicsComponent_t>()){
    //    //    auto* phy = e.template getComponent<PhysicsComponent_t>();
    //    //    phy->x = x;
    //    //    phy->y = y;
    //    //    phy->z = z;
    //    //}
    ////}
    //
    ////vacio o no, tengo que crear las cosas del entorno igualmente 
    ////como static hay mas, recorro los que hay en el for y accedo a ellos con su ID
    ////va leyendo uno a uno y hace la llamada para crearlos al final
    for(unsigned int i = 0; i < j["hierachy"]["nodes"].size();i++){
        std::cout << "entra" << std::endl;
        auto selector = j["hierachy"]["nodes"][i];
        nombre = selector["name"].get<std::string>();
        auto pos = selector["pos"];
        x = pos[0].get<double>();
        y = pos[1].get<double>();
        z = pos[2].get<double>();

        auto rotation = selector["rot"];
        rx = rotation[0].get<double>();
        ry = rotation[2].get<double>();
        rz = rotation[1].get<double>();

        auto width = selector["Width"].get<double>();
        auto height = selector["Length"].get<double>();
        auto length = selector["Height"].get<double>();
        
        //Crear una funcion especifica para crear el suelo
        modelpath = selector["model"].get<std::string>();        
        texturepath = selector["texture"].get<std::string>();                           
        if(nombre != "Player"){
            if(nombre.compare(0,5,"Pared") == 0 
            || nombre.compare(0,7,"bbarbol") == 0
            || nombre.compare(0,4,"zone") == 0){
                createStaticEntityNonRender(x,y,z,rx,ry,rz,width,height,length,nombre,modelpath);    
            }
            else if(nombre.compare(0,5,"Enemy") == 0){
                std::cout<<"el modelpath es: "<<modelpath<<"\n";
                createEnemy(x,y,z,nombre,modelpath,texturepath,1);
            }
            else{
                std::cout << "El texture path :  " << texturepath << std::endl;
                if(selector["Static"] == true){
                    createStaticEntity(x,y,z,rx,ry,rz,width,height,length,nombre,modelpath,texturepath);
                }else{
                    createNonStaticEntity(x,y,z,rx,ry,rz,width,height,length,nombre,modelpath,texturepath);
                }
            }
            if(selector["Collisionable"] == true){
                auto objstatic = selector["Static"];
                //bulletEngine_t->createObjects(x,y,z,width,height,length,objstatic,nombre);
            }
               
        }else{
            GameObjectFactory_t::createPlayer(x,y,z,modelpath,texturepath);
            //BulletEngine::getInstancia().createCharacter(x,y,z);
        }

        
        //texturepath = selector["texture"].get<std::string>(); 
        //if(selector["name"] != "SceneRoot"){
        //    auto pos = selector["pos"];
        //    x = (-1)*pos[0].get<double>();
        //    y = 0.0;
        //    z = pos[2].get<double>();
//
        //    //auto rotacion = selector["rot"];
        //    //rx = (rotacion[0].get<double>()*PI*180)/PI;
        //    //ry = (rotacion[1].get<double>()*PI*180)/PI;
        //    //rz = (rotacion[2].get<double>()*PI*180)/PI;
        //    //std::cout << rx << " " << ry << " " << rz << std::endl;
        //    //auto escala = selector["scl"];
        //    //sx = escala[0].get<double>();
        //    //sy = escala[1].get<double>();
        //    //sz = escala[2].get<double>();
        //    if(selector["name"] != ""){
        //        auto name = selector["name"].get<std::string>();
        //        std::cout << name << " " << " X Y Z: " << x << " " << y << " " << z << " " << std::endl;
        //        auto delimiter = "_";
        //        auto token = name.substr(0,name.find(delimiter));
        //        std::cout << token << std::endl;
        //        auto model = "media/obj/Zona_" + numberZone + "/" + name + ".obj";     
        //        if(token == "Arbol" || token == "Farolillo" || token == "roca" || token == "Casa" || token == "Valla"){
        //            model = "media/obj/Zona_" + numberZone + "/" + token + ".obj"; 
        //        }
//
        //        //if(token == "Suelo"){
        //        //    texturepath = "media/texturas/color_suelo.jpg";
        //        //}else if(token == "Arbol"){
        //        //    texturepath = "media/texturas/tree.jpg";
        //        //}
        //        createStaticEntity(x,y,z,rx,ry,rz,sx,sy,sz,name,model,texturepath);
        //    }
        //}
    }
    //createEnemy(-19.0,4.0,-260.0,"s","media/obj/Bosque/Player.obj","media/color_potion.jpg",1);
    GameObjectFactory_t::createCamera();
    //int itemCount = 0;
    //if(j["STATIC"].size() > 0){
    //    itemCount = j["STATIC"].size();
    //    for(int i = 0; i < itemCount; i++){
    //        std::string id = std::to_string(i);
    //        auto staticActual = j["STATIC"][id];
    //        x = staticActual["x"].get<double>();
    //        y = staticActual["y"].get<double>();
    //        z = staticActual["z"].get<double>();
    //        rx = staticActual["x"].get<double>();
    //        ry = staticActual["y"].get<double>();
    //        rz = staticActual["z"].get<double>();
    //        nombre = staticActual["NAME"].get<std::string>();
    //        modelpath = staticActual["MODEL"].get<std::string>();
    //        texturepath = staticActual["TEXTURE"].get<std::string>(); 
    //        createStaticEntity(x,y,z,rx,ry,rz,nombre,modelpath,texturepath);
    //    }
    //}
    ////el mismo proceso que antes pero ahora para los enemigos
    ////tengo que mirar que haya enemigos, porque no en todas las zonas habra
    //if(j["ENEMY"].size() > 0){
    //    itemCount = j["ENEMY"].size();
    //    for(int i = 0; i < itemCount; i++){
    //        std::string id = std::to_string(i);
    //        auto enemyActual = j["ENEMY"][id];
    //        x = enemyActual["x"].get<double>();
    //        y = enemyActual["y"].get<double>();
    //        z = enemyActual["z"].get<double>();
    //        rx = enemyActual["x"].get<double>();
    //        ry = enemyActual["y"].get<double>();
    //        rz = enemyActual["z"].get<double>();
    //        std::cout<<x<<" "<<y<<" "<<z<<"\n";
    //        nombre = enemyActual["NAME"].get<std::string>();
    //        modelpath = enemyActual["MODEL"].get<std::string>();
    //        texturepath = enemyActual["TEXTURE"].get<std::string>();
    //        createEnemy(x,y,z,nombre,modelpath,texturepath);
    //    }
    //}
    ////una vez tenemos todas las entitys en el array, lanzamos el evento para que el motor grafico las cree
    ////EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
    
}

void GameObjectFactory_t::prueba(EventInfo info){
    std::cout<<"Estoy en prueba de game object y este es el size del vector: "<<m_EntMan.getEntities().size()<<"\n";
}

void GameObjectFactory_t::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Change_Zone,std::bind(&GameObjectFactory_t::readLevel, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Create_Shot,std::bind(&GameObjectFactory_t::createShot, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Probando,std::bind(&GameObjectFactory_t::prueba, this, std::placeholders::_1)));
}
