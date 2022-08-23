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
#include "../cmp/PlayerComponent.hpp"
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
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    rn.loadFilesNames(rutamodel, rutatexture);
    rn.loadDimensions(width,height,length);   

    phy.x = x;  phy.rx = rx; 
    phy.y = y;  phy.ry = ry; 
    phy.z = z;  phy.rz = rz; 
}

void GameObjectFactory_t::createColliderEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
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

void GameObjectFactory_t::createColliderNonEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const{
    
    auto& e = m_EntMan.createEntity(nombre);
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    m_EntMan.addComponent<StaticComponent_t>(e);
    m_EntMan.addComponent<CollisionComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    rn.loadFilesNames(rutamodel, rutatexture);
    rn.loadDimensions(width,height,length);   
    rn.isVisible = false;

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

void GameObjectFactory_t::createPlayer(float x,float y,float z,float w,float h,float l,const std::string_view rutamodel, const std::string_view rutatexture)
const {
    //Primero checkeamos si hay ya un jugador creado
    //Como el personaje siempre se crea primero
    auto& entidades = m_EntMan.getEntities();
    if(entidades.size() == 0){
        auto& e = m_EntMan.createEntity("player");
        auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
        auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
        auto& items = m_EntMan.addComponent<ItemComponent_t>(e);
        auto& childs = m_EntMan.addComponent<PlayerComponent_t>(e);    
        auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
        //auto& dim = m_EntMan.addComponent<DimensionsComponent_t>(e);
        m_EntMan.addComponent<InputComponent_t>(e);
        m_EntMan.addComponent<DirecComponent_t>(e);
        //bulletEngine_t.get()->createObjects(x,y,z);
        //auto& zone = m_EntMan.addComponent<ZoneComponent_t>(e);
        hp.life = 100;
        ph.vx = 0.45;
        ph.vz = 0.45;
        ph.x = x; ph.zonex = x;
        ph.y = y; ph.zoney = y;
        ph.z = z; ph.zonez = z;
       
       
        rn.loadDimensions(w,h,l);
        rn.loadFilesNames(rutamodel, rutatexture);
        Sword_t newSword;
        newSword.addManager(m_EntMan);
        items.AddSword(newSword);
        Shield_t newShield;
        newShield.addManager(m_EntMan);
        items.AddShield(newShield);
        Arco_t arc;
        arc.addManager(m_EntMan);
        items.AddArc(arc);
        Pocion_t p;
        p.addManager(m_EntMan);
        items.AddPotion(p);
      
        auto cubeID = createWeapons("CubeBB");
        //childs.addChildsPermanent(cubeID);
    }else{
        auto& playerCmp = m_EntMan.getComponents<PlayerComponent_t>();
        auto* entidadPlayer = m_EntMan.getEntityByID(playerCmp[0].getEntityID());
        if(entidadPlayer){
            auto* physics = entidadPlayer->getComponent<PhysicsComponent_t>();
            physics->x = x;
            physics->y = y;
            physics->z = z;  
        }
    }
}

std::size_t GameObjectFactory_t::createWeapons(const std::string_view name) const{
    auto& e = m_EntMan.createEntity(name);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    rn.loadDimensions(10.0f,10.0f,10.0f);
    rn.isVisible = false;
    return e.getEntityID();
}

void GameObjectFactory_t::createEnemy(float x, float y, float z, float rx, float ry, float rz, float width,float height,float length , const std::string_view nombre, const std::string_view rutamodel, const std::string_view rutatexture,int type,int typerizo) 
const{
    //std::cout<<"entro al create enemy\n";
    //std::cout<<"entro al create enemy\n";
    auto& e = m_EntMan.createEntity(nombre);

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& rn = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& ene = m_EntMan.addComponent<EnemyComponent_t>(e);
    //m_EntMan.addComponent<StaticComponent_t>(e);
    ph.x = x; ph.y = y; ph.z = z;
    ph.rx = rx; ph.ry = ry; ph.rz = rz;
    ph.initx = x, ph.inity = y; ph.initz = z;
    rn.loadFilesNames(rutamodel, rutatexture);
    rn.loadDimensions(width,height,length);
    ene.damage = 5.0;
    switch(type){
        case 0:{
            auto& ia = m_EntMan.addComponent<IAComponent_t>(e);
            ia.type = erizo;
            ene.damage = 20;
            ia.erizotype = typerizo;
        }
            break;
        case 1:{
            auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
            auto& ia = m_EntMan.addComponent<IAComponent_t>(e);
            ia.type = seta;
            ene.damage = 10;
            hp.life = 10;
        }
            break;
        case 2:{
            auto& ia = m_EntMan.addComponent<IAComponent_t>(e);
            auto& hp = m_EntMan.addComponent<HPComponent_t>(e);
            ia.type = spider;
            ene.damage = 10;
            hp.life = 20;
        }
            break;
        case 3:{
            ene.damage = 10;
        }
            break;
        case 4:{
            ene.damage = 20;
        }
            break;
        case 5:{
            ene.damage = 100;
        }
            break;
    }
}

void GameObjectFactory_t::createShot(EventInfo info){
    //std::cout<<"entro a createShot\n";
    auto& e = m_EntMan.createEntity("bala");
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& ren = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& shot = m_EntMan.addComponent<ShootComponent_t>(e);
    phy.x = info.posX;   phy.initx = info.posX;
    phy.y = info.posY;   phy.inity = info.posY;  
    phy.z = info.posZ;  phy.initz = info.posZ;
    phy.rx = info.rotX; phy.ry = info.rotY; phy.rx = info.rotZ; 
    phy.vx = 1.2;      phy.vz = 1.2;
    ren.loadFilesNames("media/obj/Bosque/flecha.obj","media/Texturas/Bosque/flecha/flecha");
    ren.loadDimensions(4.597,0.21,0.443);
    shot.angle = info.angle;
    shot.right = info.shotdir;
    if(info.playerShoot == true){
        shot.type = Balatype::playershot;
        info.ruta = "media/Texturas/Bosque/flecha/flecha";
        info.zona = "media/obj/Bosque/flecha.obj";
    }else{
        shot.type = Balatype::enemyshot;
        info.ruta = "media/Texturas/Personaje/Damage/Damage";
        info.zona = "media/obj/Bosque/Disparo_seta.obj";
    }
    info.id = e.getEntityID();
    //std::cout << "A ver no se donde cojones aparece " << phy.x << " " << phy.z << std::endl;
    //std::cout<<"ID de la bala creada: "<<info.id<<"\n";
    EventManager::getInstancia().addEvent(Event{EventType::Create_Shot_MG,info});
    //Añadir un evento que cree una bala en el RavenGraphics para que se pueda renderizar
    
}


void GameObjectFactory_t::createCamera(){
    //std::cout<<"entro al create camera\n";
    std::string name = "camera";
    auto& e = m_EntMan.createEntity(name);
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    phy.rx = 45.f; phy.ry = 180.f;  
    m_EntMan.addComponent<CameraComponent_t>(e);
}

void GameObjectFactory_t::createObjectsGeneric(float x, float y, float z,float rx, float ry, float rz, float width,float height,float length , const std::string_view nombre, const std::string_view rutamodel, 
const std::string_view rutatexture,bool staticValue, bool collisionableValue, bool renderizableValue) const {
    //Creamos la entidad
    auto& e = m_EntMan.createEntity(nombre);
    //Miramos si tienen componente de render
    auto& render = m_EntMan.addComponent<RenderComponent_t>(e);
    render.loadDimensions(width,height,length);
    render.loadFilesNames(rutamodel,rutatexture);
    if(!renderizableValue){
        render.isVisible = false;
    }
    auto& physics = m_EntMan.addComponent<PhysicsComponent_t>(e);
    physics.x = x; physics.initx = x; physics.rx = rx;
    physics.y = y; physics.inity = y; physics.ry = ry;
    physics.z = z; physics.initz = z; physics.rz = rz;

    if(staticValue){
        m_EntMan.addComponent<StaticComponent_t>(e);
    }
    if(collisionableValue){
        m_EntMan.addComponent<CollisionComponent_t>(e);
    }
}
void GameObjectFactory_t::setRuta(EventInfo info) noexcept {
    ruta = info.ruta;
}

void GameObjectFactory_t::setZona(EventInfo info) noexcept {
    zona = info.zona;
}

void GameObjectFactory_t::readLevel(EventInfo info) noexcept{
    //primero siempre abro el archivo json
    //std::cout<<"Estoy en el gameobject y la zona que me llega por parametro es: "<<info.zone<<"\n";
    //std::cout<<"entro al readlevel\n";
    //std::cout << "Ruta : " + ruta  << " zona: " << zona << std::endl;
    auto newRoute = ruta + zona + ".json";
    //auto& zonevec = m_EntMan.getComponents<ZoneComponent_t>();
    //zona += std::to_string(zonevec[0].zone);
    std::ifstream archivo(newRoute);
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
        //std::cout << "entra" << std::endl;
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
        auto staticValue = selector["Static"];
        auto renderValue = selector["Render"];
        auto collisionableValue = selector["Collisionable"];
        bool catched = false;

        if(nombre != "Player"){
            auto enemyType = selector["TypeEnemy"].get<int>();
            auto& player = m_EntMan.getComponents<PlayerComponent_t>()[0];
            auto* entidadPlayer = m_EntMan.getEntityByID(player.getEntityID());
            for( const std::pair<std::string, std::string>& n : entidadPlayer->getComponent<PlayerComponent_t>()->lista ) {
                if(nombre == n.first && zona.compare(n.second) == 0){
                    catched = true;
                    break;
                }
            }
            if(catched == false){
                if(enemyType != -1){
                    if(selector["ErizoID"].size() > 0){
                        auto erizoid = selector["ErizoID"].get<int>();
                        GameObjectFactory_t::createEnemy(x,y,z,rx,ry,rz,width,height,length,nombre,modelpath,texturepath,enemyType,erizoid);
                    }else{
                        GameObjectFactory_t::createEnemy(x,y,z,rx,ry,rz,width,height,length,nombre,modelpath,texturepath,enemyType,-1);
                    }
                }else{
                    GameObjectFactory_t::createObjectsGeneric(x,y,z,rx,ry,rz,width,height,length,nombre,modelpath,texturepath,staticValue,collisionableValue,renderValue);
                }
            }
        }else{
            GameObjectFactory_t::createPlayer(x,y,z,width,height,length,modelpath,texturepath);
            //BulletEngine::getInstancia().createCharacter(x,y,z);
        }
        auto& inpPl = m_EntMan.getComponents<InputComponent_t>()[0];
        auto entidadPl = m_EntMan.getEntityByID(inpPl.getEntityID());
        entidadPl->getComponent<PlayerComponent_t>()->removeTemporal();
        entidadPl->getComponent<PlayerComponent_t>()->zona_player = zona ;
        entidadPl->getComponent<PlayerComponent_t>()->ruta_player = ruta ;
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

void GameObjectFactory_t::createEspejo(EventInfo info){
    auto& playercmp = m_EntMan.getComponents<PlayerComponent_t>();
    auto* player = m_EntMan.getEntityByID(playercmp[0].getEntityID());
    if(player)
        playercmp[0].endgame = true;
    std::string name = "end_mirror";
    auto& e = m_EntMan.createEntity(name);
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& ren = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& col = m_EntMan.addComponent<CollisionComponent_t>(e);
    m_EntMan.addComponent<StaticComponent_t>(e);
    //-267.912 , 9.02017 , 708.905 posicion del espejo real en la zona9

    phy.x = -267.912 ; phy.y = 9.02017; phy.z = 708.905  ;
    ren.loadFilesNames("media/obj/Bosque/end_mirror.obj","media/Texturas/Bosque/end_mirror/end_mirror");
    ren.loadDimensions(12.8497 ,21.8566,22.4977);
    info.id = e.getEntityID();
    info.posX = phy.x; info.posZ = phy.z;
    info.ruta = "media/Texturas/Bosque/end_mirror/end_mirror";
    info.zona = "media/obj/Bosque/end_mirror.obj";
    EventManager::getInstancia().addEvent(Event{EventType::Create_Shot_MG,info});
}

void GameObjectFactory_t::createDeku(EventInfo info){
    std::string name = "deku";
    auto& e = m_EntMan.createEntity(name);
    auto& phy = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& ren = m_EntMan.addComponent<RenderComponent_t>(e);
    phy.x = 5; phy.y = 5; phy.z = 920.5 ;
    ren.loadFilesNames("media/obj/Bosque/chico.obj","media/Texturas/Bosque/chico/chico");
    ren.loadDimensions(8.08306,2.9505,10.2167);
    info.id = e.getEntityID();
    info.posX = phy.x; info.posZ = phy.z;
    info.ruta = "media/Texturas/Bosque/chico/chico";
    info.zona = "media/obj/Bosque/chico.obj";
    EventManager::getInstancia().addEvent(Event{EventType::Create_Shot_MG,info});
}

void GameObjectFactory_t::prueba(EventInfo info){
    //std::cout<<"Estoy en prueba de game object y este es el size del vector: "<<m_EntMan.getEntities().size()<<"\n";
}

void GameObjectFactory_t::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Read_Level,std::bind(&GameObjectFactory_t::readLevel, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Change_ruta,std::bind(&GameObjectFactory_t::setRuta, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Change_zona,std::bind(&GameObjectFactory_t::setZona, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Create_Shot,std::bind(&GameObjectFactory_t::createShot, this, std::placeholders::_1)));
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Probando,std::bind(&GameObjectFactory_t::prueba, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::create_Espejo,std::bind(&GameObjectFactory_t::createEspejo, this, std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::create_Deku,std::bind(&GameObjectFactory_t::createDeku, this, std::placeholders::_1)));
}
