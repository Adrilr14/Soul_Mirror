#include "irrlichtGraphics.hpp"
#include "../game/cmp/PhysicsComponent.hpp"
#include "../game/cmp/InputComponent.hpp"
#include "../game/cmp/CameraComponent.hpp"
#include "../game/cmp/IAComponent.hpp"
#include "../game/cmp/DirecComponent.hpp"
#include "../game/cmp/StaticComponent.hpp"
#include "../game/cmp/RenderComponent.hpp"
#include "../game/cmp/ZoneComponent.hpp"
#include "../game/cmp/ShootComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include <string>
#include <iostream>


irrlichtGraphics::irrlichtGraphics(){
    std::cout<<"hola que tal como estamos\n";
    device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920,1080), 16, false, false, true, &input);
    if(device){
    	device->setWindowCaption(L"SoulMirror");
    	driver = device->getVideoDriver();
    	smgr = device->getSceneManager();
    	guienv = device->getGUIEnvironment();
        dbDraw = new DebugDraw(device);
        dbDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
        irr::scene::ILightSceneNode* light = smgr->addLightSceneNode( 0, irr::core::vector3df(-50.0f,10.0f,0.0f),irr::video::SColorf(1.0f,1.0f,1.0f,1.0f), 5000.0f );
    }
    addEventListeners();
}

irrlichtGraphics::~irrlichtGraphics(){
    
}

void irrlichtGraphics::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Render_Change_Zone,std::bind(&irrlichtGraphics::addEntities,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Delete_Entities_Render,std::bind(&irrlichtGraphics::removeEntities,this,std::placeholders::_1)));
}


void irrlichtGraphics::worldPhysics(std::shared_ptr<BulletEngine> w){
    if(w != nullptr){
        world = w;
        world->getWorld()->setDebugDrawer(dbDraw);
    }
}

void irrlichtGraphics::removeEntities(EventInfo info){
    smgr->clear();
}

void irrlichtGraphics::removeEntity(std::size_t id){
    auto* remove = smgr->getSceneNodeFromId(id);
    if(remove)
        remove->remove();
}

void irrlichtGraphics::createWindow(){
    //std::cout<<"entro al window\n";
    device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920,1080), 16, false, false, true, &input);
    if(device){
    	device->setWindowCaption(L"SoulMirror");
    	driver = device->getVideoDriver();
    	smgr = device->getSceneManager();
    	guienv = device->getGUIEnvironment();
    }
}

void irrlichtGraphics::addEntity(EventInfo info){
    //std::cout<<"entro a crear la bola\n";
    //esto se tiene que ampliar obviamente en un futuro, usando el modelo y la textura
    //de momento solo la uso para crear las balas o proyectiles de la seta, pero info ya tiene campos para leer el modelo y la textura
    auto* bala = smgr->addSphereSceneNode(0.8);
    bala->setID(info.id);
}

void irrlichtGraphics::removeEntity(EventInfo info){
    auto* remove = smgr->getSceneNodeFromId(info.id);
    if(remove)
        remove->remove();
}


void irrlichtGraphics::beginScene()  {
    driver->beginScene();
}


bool irrlichtGraphics::run() {
    return device->run();
}


void irrlichtGraphics::addEntities(EventInfo info){
    //TODO Revisar esto para los accesos mejor a los arrays. Physics va a tener casi todo, hay que echarle un ojo
    //esto de momento va asi porque no se las posiciones de las paredes y cosas del entorno, pero hay que mejorarlo
    //todas las entidades deben tener un position asociado, y al final deberian ser todos animatedmeshes porque seran objetos modelados
    auto& aux = manager->getEntities();
    for(auto& e : manager->getEntities()){
        if(e.getComponent<PhysicsComponent_t>()){
            //std::cout<<"hay fisica\n";
            auto* phy = e.getComponent<PhysicsComponent_t>();
            //if(e.getName().compare("player") == 0)//si es el player, si le asigno una posicion
              //  node->setPosition(irr::core::vector3df(phy->x,phy->y,phy->z));
            if(phy != nullptr && e.getComponent<RenderComponent_t>()){
                auto* rn = e.getComponent<RenderComponent_t>();
                if(rn != nullptr && rn->modelPath != ""){
                    mesh = smgr->getMesh(rn->modelPath.data());
                    //std::cout<<"Entidad: "<<e.getEntityID()<<"con nombre: "<<e.getName()<<"mi model es: "<<rn->modelPath.data()<<"y la textura es:"<<rn->texturePath.data()<<"\n";
                    node = smgr->addAnimatedMeshSceneNode( mesh );
                    node->setMaterialTexture(0, driver->getTexture(rn->texturePath.data()));
                    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                    node->setID(e.getEntityID());
                    node->setName(e.getName().data());
                    node->setPosition(irr::core::vector3df(phy->x,phy->y,phy->z));
                    //std::cout<<"X: "<<  node->getPosition().X << std::endl;
                    //std::cout<<"Y: "<<  node->getPosition().Y << std::endl;
                    //std::cout<<"Z: "<<  node->getPosition().Z << std::endl;
                    node->setRotation(irr::core::vector3df(phy->rx,phy->ry,phy->rz));
                    //node->setScale(irr::core::vector3df(0.5,0.5,0.5));
                   
                    if(e.getName().compare(0,4,"zone") == 0)
                        node->setVisible(false); 
                }
                //delete rn;
            //std::cout<<"Posicion de la pared:"<<node->getPosition().X<<" "<<node->getPosition().Z<<"\n";
            }
            //delete phy;
        }   
        //smgr->saveScene("zone_1.txt");
    }
    //despues de crear las entidades creo la camara en un sitio random
    Addcamera();
}

void irrlichtGraphics::probando(){
    if(!smgr->getSceneNodeFromName("player")){
        mesh = smgr->getMesh("media/obj/player.obj");
        node = smgr->addAnimatedMeshSceneNode( mesh );
        node->setMaterialTexture(0, driver->getTexture("media/color_player.jpg"));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setID(1);
        node->setName("player");
        node->setPosition(irr::core::vector3df(100,100,100));
    }
}

void irrlichtGraphics::Addcamera(){
    //for(auto& e : manager->getComponents<CameraComponent_t>()){
        camera = smgr->addCameraSceneNode(0, irr::core::vector3df(120,40,-86));
        if(smgr->getSceneNodeFromName("player") != nullptr){
            auto posBulletCh = world->getCharacter()->getGhostObject()->getWorldTransform().getOrigin();
            smgr->getActiveCamera()->setTarget(smgr->getSceneNodeFromName("player")->getPosition());
        }
    //}
}

void irrlichtGraphics::cameraUpdate() {
    auto& camcmp = manager->getComponents<CameraComponent_t>();
        auto* e = manager->getEntityByID(camcmp[0].getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->getComponent<PhysicsComponent_t>();
            if(phycmp){
                auto posBulletCh = world->getCharacter()->getGhostObject()->getWorldTransform().getOrigin();
                smgr->getActiveCamera()->setPosition(irr::core::vector3df(posBulletCh.getX(),phycmp->y,phycmp->z));
                if(smgr->getSceneNodeFromName("player")){
                    smgr->getActiveCamera()->setTarget(smgr->getSceneNodeFromName("player")->getPosition());
                }
            //std::cout<<"Camara X: "<<phycmp->x<<" Camara Y: "<<phycmp->y<<" Camara Z: "<<phycmp->z<<"\n";
            }
            //delete phycmp;
        }
        //delete e;
        
    //camaraPosition.X = x; camaraPosition.Y = y; camaraPosition.Z = z;
    //smgr->getActiveCamera()->setPosition(camaraPosition);
    
}

void irrlichtGraphics::updateEntities(){
    irr::core::vector3df newPosition;
    //std::cout<<"entro al update entities\n";
    //como habra muchos objetos estaticos es absurdo recorrer todas las entidades
    //actualizamos primero la IA
    for(auto& iacmp : manager->getComponents<IAComponent_t>()){
        auto* e = manager->getEntityByID(iacmp.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->template getComponent<PhysicsComponent_t>();
            if(phycmp){
                newPosition.X = phycmp->x;
                newPosition.Y = phycmp->y;
                newPosition.Z = phycmp->z;
                if(smgr->getSceneNodeFromId(e->getEntityID())){//hay que ver que el nodo existe, si no explota
                    //std::cout<<"La posicion del enemy es X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
                    smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);
                }
            }
            //delete phycmp;
        }
        //delete e;
    }
    //actualizo el player ahora
    for(auto& player : manager->getComponents<InputComponent_t>()){
        auto* e = manager->getEntityByID(player.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->template getComponent<PhysicsComponent_t>();
            if(phycmp){
                auto posBulletCh = world->getCharacter()->getGhostObject()->getWorldTransform().getOrigin();
                newPosition.X = posBulletCh.getX();
                newPosition.Y = posBulletCh.getY();
                newPosition.Z = posBulletCh.getZ();
                if(smgr->getSceneNodeFromId(e->getEntityID())){
                    smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);   
                    //world->walkingCharacter(newPosition.X,newPosition.Y,newPosition.Z);
                }//hay que ver que el nodo existe, si no explota{
                //std::cout<<"X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
            }
            //delete phycmp;
        }
        //delete e;
    }
     //por ultimo actualizo las balas de las setas
    for(auto& bala : manager->getComponents<ShootComponent_t>()){
        auto* e = manager->getEntityByID(bala.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->template getComponent<PhysicsComponent_t>();
            newPosition.X = phycmp->x;
            newPosition.Y = phycmp->y;
            newPosition.Z = phycmp->z;
            if(smgr->getSceneNodeFromId(e->getEntityID()))//hay que ver que el nodo existe, si no explota
                smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);
        }
    }
}

void irrlichtGraphics::checkColisions(){
    //este metodo es hiper cutre, pero con algo hay que tirar hasta que esten las colisiones en su sistema xd
    irr::core::aabbox3d<irr::f32> b1, b2, b3;
    irr::scene::ISceneNode* nodeplayer;
    irr::scene::ISceneNode* nodezone;
    
    nodeplayer = smgr->getSceneNodeFromName("player");//saco el nodo del player
    
    if(nodeplayer != nullptr){

        b1 = nodeplayer->getBoundingBox ();//saco el BB del player
        nodeplayer->getRelativeTransformation().transformBoxEx(b1);
    //ahora tengo que sacar todas las BB de las entidades con nombre = zone_X
        std::vector<int> zonas;
        std::vector<std::string> nombres_zonas;
        for(auto& e : manager->getEntities()){
            if(e.getName().compare(0,4,"zone") == 0){
                zonas.push_back(e.getEntityID());
                nombres_zonas.push_back(e.getName());
            }
        }
        for(int i = 0; i < zonas.size(); i++){
                nodezone = smgr->getSceneNodeFromId(zonas[i]);
                if(nodezone){//si el node no es nullptr
                    b2 = nodezone->getBoundingBox();
                    nodezone->getRelativeTransformation().transformBoxEx(b2);
                    if(b1.intersectsWithBox(b2)){
                        int direccion = irrlichtGraphics::getDirection();
                        std::string nombre = "";
                        auto delimiter = "_";
                        if(direccion == 3){
                            nombre = irrlichtGraphics::splitPattern(nombres_zonas[i],"_")[1];
                        }else if(direccion == 2){
                            nombre = irrlichtGraphics::splitPattern(nombres_zonas[i],"_")[1];
                        }else{
                            nombre = nombre = irrlichtGraphics::splitPattern(nombres_zonas[i],"_")[2];
                        }
                        if(nombre != ""){
                            EventInfo info;
                            info.zone = std::stoi(nombre);
                            EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
                            EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
                            EventManager::getInstancia().addEvent(Event{EventType::Change_Zone,info});//leo la nueva zona del json
                            EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
                        }
                        break;
                    }
                }   
        }
    }
    
}

int irrlichtGraphics::getDirection(){
    auto& inpcmp = manager->getComponents<InputComponent_t>();
        auto* e = manager->getEntityByID(inpcmp[0].getEntityID());
        if(e){
            auto direc = e->getComponent<DirecComponent_t>();
            if(direc){
                return direc->dirPrevia;
            }
        }
    return -1;
}


std::vector<std::string> irrlichtGraphics::splitPattern(const std::string_view s,const char* delimiter){
    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> resultados;

    while(posFound >= 0){
        posFound = s.find(delimiter, posInit);
        splitted = s.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        resultados.push_back(splitted);
    }

    return resultados;
}

void irrlichtGraphics::renderScene()  {
    driver->beginScene(true, true, irr::video::SColor(100,20,101,140));
    smgr->drawAll();   
    irr::video::SMaterial debugMat;
    debugMat.Lighting = false;
    driver->setMaterial(debugMat);
    driver->setTransform(irr::video::E_TRANSFORMATION_STATE::ETS_WORLD, irr::core::IdentityMatrix);
    world->getWorld()->debugDrawWorld();

    //probando();
}

void irrlichtGraphics::endScene(){
    driver->endScene();
}

void irrlichtGraphics::shutEngine(){
    device->drop();
}

void irrlichtGraphics::addManager(EntityManager_t& man){
    manager = &man;
}


//Funciones INPUT
Input::Input(){
	for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    LeftClickDown = false;
}

bool Input::OnEvent(const irr::SEvent& event){
    bool press = false;
	// Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    // Remember the mouse state
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
        /*switch(event.MouseInput.Event)
        {
            case EMIE_LMOUSE_PRESSED_DOWN:
                press = true;
                //std::cout<<"Entro en el click" <<std::endl;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                press = false;
                break;

            default:
				// We won't use the wheel
				break;
        }*/
        LeftClickDown = event.MouseInput.isLeftPressed();
    }

    return press;
}

// This is used to check whether a key is being held down
bool Input::IsKeyDown(irr::EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
}

// This is used to check the left clck (mouse)
bool Input::IsLeftClickDown() const{
    return LeftClickDown;
}

void irrlichtGraphics::getInputInit(){
    if(input.IsKeyDown(irr::KEY_KEY_V)){
        EventInfo info;
        info.state_type = 4;
        std::cout<<"hola que tal\n";
        EventManager::getInstancia().addEvent(Event{EventType::State_Change,info});
    }
}

void irrlichtGraphics::getInputCredits(){
    if(input.IsKeyDown(irr::KEY_KEY_V))
        EventManager::getInstancia().addEvent(Event{EventType::Input_V});
}

void irrlichtGraphics::getInputGame(){
    //std::cout<<"entro al input\n";
        auto& inpcmp = manager->getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
        auto* e = manager->getEntityByID(inpcmp[0].getEntityID());
        EventInfo info;
        auto direc = e->template getComponent<DirecComponent_t>();
        if(e && direc){
            //auto* dircmp = e->getComponent<DirecComponent_t>();
            if(input.IsKeyDown(irr::KEY_KEY_P)){
                //EventInfo info;
                //info.soundname = "event:/Efectos/ataque/soltar_objeto";
                EventManager::getInstancia().addEvent(Event{EventType::Play_Music});
            }
            if(input.IsKeyDown(irr::KEY_SHIFT)){//correr

            }

            if(input.IsKeyDown(irr::KEY_KEY_C)){
                //std::cout<<"Tamanyo del vector ahora: "<<manager->getEntities().size();
            }

            //*************PAUSAR JUEGO*********
            if(input.IsKeyDown(irr::KEY_ESCAPE)){
                EventManager::getInstancia().addEvent(Event{EventType::Pause});
            }

            //*************CAMBIOS DE ARMA**********
            if(input.IsKeyDown(irr::KEY_KEY_1)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_1});
            }

            if(input.IsKeyDown(irr::KEY_KEY_2)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_2});
            }

            if(input.IsKeyDown(irr::KEY_KEY_3)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_3});
            }

            if(input.IsKeyDown(irr::KEY_KEY_4)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_4});
            }

            if(input.IsKeyDown(irr::KEY_KEY_5)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_5});
            }

            //*************MOVIMIENTO*********
            if(input.IsKeyDown(irr::KEY_KEY_D)){
                //std::cout<<"me estoy moviendo\n";   
                info.direction = 1;
                direc->dirPrevia = 1;
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
                //derecha
            }
            if(input.IsKeyDown(irr::KEY_KEY_A)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 2;
                direc->dirPrevia = 2;
                EventManager::getInstancia().addEvent(Event{EventType::Input_A, info});
                //izquierda   
            } 
            if(input.IsKeyDown(irr::KEY_KEY_W)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 3;
                direc->dirPrevia = 3;
                EventManager::getInstancia().addEvent(Event{EventType::Input_W, info});
                if(smgr->getSceneNodeFromName("player")){
                    smgr->getSceneNodeFromName("player")->setRotation(irr::core::vector3df(0,0,0));
                }
                //arriba
            }
            if(input.IsKeyDown(irr::KEY_KEY_S)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 4;
                direc->dirPrevia = 4;
                EventManager::getInstancia().addEvent(Event{EventType::Input_S, info});
                //abajo
            }
            if(input.IsKeyDown(irr::KEY_KEY_D) && input.IsKeyDown(irr::KEY_KEY_W)){
                info.direction = 5;
                direc->dirPrevia = 5;
                info.rotation = 30;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WD, info});
                // Dirección hacia derecha-arriba
            }
            else if(input.IsKeyDown(irr::KEY_KEY_A) && input.IsKeyDown(irr::KEY_KEY_W)){
                info.direction = 6;
                direc->dirPrevia = 7;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WA, info});
                // Dirección hacia izquierda-arriba
            }
            else if(input.IsKeyDown(irr::KEY_KEY_D) && input.IsKeyDown(irr::KEY_KEY_S)){
                info.direction = 7;
                direc->dirPrevia = 7;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SD, info});
                // Dirección hacia derecha-abajo
            }
            else if(input.IsKeyDown(irr::KEY_KEY_A) && input.IsKeyDown(irr::KEY_KEY_S)){
                info.direction = 8;
                direc->dirPrevia = 8;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SA, info});
                //Dirección hacia izquierda-abajo
            }
        }

    /*if(input.IsKeyDown(irr::KEY_KEY_Z)){
        //input de prueba para hacer cosas
        }
    }*/
}

void irrlichtGraphics::getInputControls(){

}

void irrlichtGraphics::getInputPause(){
    //std::cout<<"entro al inputpase\n";
    if(input.IsKeyDown(irr::KEY_F1))
        EventManager::getInstancia().addEvent(Event{EventType::Pause});
}

void irrlichtGraphics::drawInit(){
    //hace las cosas de dibujo del init state
}

void irrlichtGraphics::drawCredits(){
    //hace las cosas de dibujo del credits state
}

void irrlichtGraphics::drawGame(){
    //hace las cosas del game state
    smgr->drawAll();
}

void irrlichtGraphics::drawControls(){
    //hace las cosas del dibujo de controls state
}

void irrlichtGraphics::drawPause(){

}