#include <facade/irrlichtGraphics.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/CameraComponent.hpp>
#include <game/cmp/IAComponent.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/StaticComponent.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <game/cmp/ZoneComponent.hpp>
#include <EventManager/EventManager.hpp>
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
    }
    addEventListeners();
}

irrlichtGraphics::~irrlichtGraphics(){
    
}

void irrlichtGraphics::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Render_Change_Zone,std::bind(&irrlichtGraphics::addEntities,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Delete_Entities_Render,std::bind(&irrlichtGraphics::removeEntities,this,std::placeholders::_1)));
}

void irrlichtGraphics::removeEntities(EventInfo info){
    //std::cout<<"entro al remove ";
    if(!manager->IsEmpty()){ 
      //  std::cout<<"entro al if del remove\n";
        for(int i = 0; i < manager->getEntities().size(); i++){
        auto* object3 = smgr->getSceneNodeFromId(i);
        if(object3)
            object3->remove();
        }
    }
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


void irrlichtGraphics::beginScene()  {

}


bool irrlichtGraphics::run() {
    return device->run();
}

void irrlichtGraphics::renderInit()  {
    //irr.renderInit();
}

void irrlichtGraphics::physicsInit()  {
    //irr.physicsInit();
}

void irrlichtGraphics::getInput(){
    //std::cout<<"entro al input\n";
        auto& inpcmp = manager->getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
        auto* e = manager->getEntityByID(inpcmp[0].getEntityID());
        EventInfo info;
        if(e && e->template getComponent<DirecComponent_t>()){
            //auto* dircmp = e->getComponent<DirecComponent_t>();
            if(input.IsKeyDown(irr::KEY_SHIFT)){//correr

            }

            //*************CAMBIOS DE ARMA**********
            if(input.IsKeyDown(irr::KEY_KEY_1)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
            }

            if(input.IsKeyDown(irr::KEY_KEY_2)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
            }

            if(input.IsKeyDown(irr::KEY_KEY_3)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
            }

            if(input.IsKeyDown(irr::KEY_KEY_4)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
            }

            if(input.IsKeyDown(irr::KEY_KEY_5)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
            }

            //*************MOVIMIENTO*********
            if(input.IsKeyDown(irr::KEY_KEY_D)){   
                info.direction = 1;
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
                //derecha
            }
            if(input.IsKeyDown(irr::KEY_KEY_A)){
                info.direction = 2;
                EventManager::getInstancia().addEvent(Event{EventType::Input_A, info});
                //izquierda   
            } 
            if(input.IsKeyDown(irr::KEY_KEY_W)){
                info.direction = 3;
                EventManager::getInstancia().addEvent(Event{EventType::Input_W, info});
                //arriba
            }
            if(input.IsKeyDown(irr::KEY_KEY_S)){
                info.direction = 4;
                EventManager::getInstancia().addEvent(Event{EventType::Input_S, info});
                //abajo
            }
            if(input.IsKeyDown(irr::KEY_KEY_D) && input.IsKeyDown(irr::KEY_KEY_W)){
                info.direction = 5;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WD, info});
                // Dirección hacia derecha-arriba
            }
            else if(input.IsKeyDown(irr::KEY_KEY_A) && input.IsKeyDown(irr::KEY_KEY_W)){
                info.direction = 6;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WA, info});
                // Dirección hacia izquierda-arriba
            }
            else if(input.IsKeyDown(irr::KEY_KEY_D) && input.IsKeyDown(irr::KEY_KEY_S)){
                info.direction = 7;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SD, info});
                // Dirección hacia derecha-abajo
            }
            else if(input.IsKeyDown(irr::KEY_KEY_A) && input.IsKeyDown(irr::KEY_KEY_S)){
                info.direction = 8;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SA, info});
                //Dirección hacia izquierda-abajo
            }
        }

    if(input.IsKeyDown(irr::KEY_KEY_C)){
        std::cout<<"pulso C\n";
        //std::cout<<"Tamanyo del vector tras borrar: "<<manager->getEntities().size()<<"\n";
        //std::cout<<"Capacidad del vector tras borrar: "<<manager->getEntities().capacity()<<"\n";
        EventInfo info;
        info.zone = 2;
        //PRIMERO SE BORRA EL RENDER, ESTE ORDEN ES SOLO PARA PROBAR ALGO
        EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
        EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
        
        
        //std::cout<<"Despues de disparar los eventos en el graphics: Tamanyo del vector tras borrar: "<<manager->getEntities().size()<<"\n";
        //std::cout<<"Despues de disparar los eventos en el graphics: Capacidad del vector tras borrar: "<<manager->getEntities().capacity()<<"\n";
        EventManager::getInstancia().addEvent(Event{EventType::Change_Zone,info});//leo la nueva zona del json
        EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});//despues de leer, renderizo
        //info.zone = 2;
        //EventManager::getInstancia().addEvent(Event{EventType::Change_Zone, info});
    }
}

void irrlichtGraphics::addEntities(EventInfo info){
    //TODO Revisar esto para los accesos mejor a los arrays. Physics va a tener casi todo, hay que echarle un ojo
    //esto de momento va asi porque no se las posiciones de las paredes y cosas del entorno, pero hay que mejorarlo
    //todas las entidades deben tener un position asociado, y al final deberian ser todos animatedmeshes porque seran objetos modelados
    std::cout<<"entro al add\n";
    for(auto& e : manager->getEntities()){
        if(e.template getComponent<PhysicsComponent_t>()){
            //std::cout<<"hay fisica\n";
            auto* phy = e.template getComponent<PhysicsComponent_t>();
            //if(e.getName().compare("player") == 0)//si es el player, si le asigno una posicion
              //  node->setPosition(irr::core::vector3df(phy->x,phy->y,phy->z));
            if(e.template getComponent<RenderComponent_t>()){
                auto* rn = e.template getComponent<RenderComponent_t>();
                mesh = smgr->getMesh(rn->modelPath.data());
                //std::cout<<"Entidad: "<<e.getEntityID()<<"con nombre: "<<e.getName()<<"mi model es: "<<rn->modelPath.data()<<"y la textura es:"<<rn->texturePath.data()<<"\n";
                node = smgr->addAnimatedMeshSceneNode( mesh );
                node->setMaterialTexture(0, driver->getTexture(rn->texturePath.data()));
                node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                node->setID(e.getEntityID());
                node->setName(e.getName().data());
                node->setPosition(irr::core::vector3df(phy->x,phy->y,phy->z));
                std::cout<<"X: "<<  node->getPosition().X << std::endl;
                std::cout<<"Y: "<<  node->getPosition().Y << std::endl;
                std::cout<<"Z: "<<  node->getPosition().Z << std::endl;

                irr::core::vector3d<irr::f32> * edges = new irr::core::vector3d<irr::f32>[8];
                irr::core::aabbox3d<irr::f32> boundingbox = mesh->getBoundingBox();
                boundingbox.getEdges(edges);

                irr::f32 height = edges[1].Y - edges[0].Y; //OK
                std::cout<<"height: "<<height<<std::endl;

                irr::f32 width = edges[5].X - edges[1].X;
                std::cout<<"width: "<<width<<std::endl;

                irr::f32 depth = edges[2].Z - edges[0].Z;
                std::cout<<"depth: "<<depth<<std::endl;
                if(e.getName().compare(0,4,"zone") == 0)
                    node->setVisible(false); 
                //delete rn;
            //std::cout<<"Posicion de la pared:"<<node->getPosition().X<<" "<<node->getPosition().Z<<"\n";
            }
            //delete phy;
        }   
        //smgr->saveScene("zone_1.txt");
    }
    std::cout<<"He terminado el add entities y el size del vector es: "<<manager->getEntities().size()<<"\n";
    //despues de crear las entidades creo la camara en un sitio random
    Addcamera();
}

void irrlichtGraphics::probando(){
    if(!smgr->getSceneNodeFromName("player")){
        std::cout<<"El player no esta creado xd\n";
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
    std::cout<<"entro al addcamera\n";
    //for(auto& e : manager->getComponents<CameraComponent_t>()){
        camera = smgr->addCameraSceneNode(0, irr::core::vector3df(120,40,-86));
        smgr->getActiveCamera()->setTarget(smgr->getSceneNodeFromName("player")->getPosition());
    //}
}

void irrlichtGraphics::cameraUpdate() {
    //std::cout<<"entro al camera upate\n";
    auto& camcmp = manager->getComponents<CameraComponent_t>();
        auto* e = manager->getEntityByID(camcmp[0].getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->getComponent<PhysicsComponent_t>();
            if(phycmp){
                smgr->getActiveCamera()->setPosition(irr::core::vector3df(phycmp->x,phycmp->y,phycmp->z));
                if(smgr->getSceneNodeFromName("player"))
                    smgr->getActiveCamera()->setTarget(smgr->getSceneNodeFromName("player")->getPosition());
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
                newPosition.X = phycmp->x;
                newPosition.Y = phycmp->y;
                newPosition.Z = phycmp->z;
                if(smgr->getSceneNodeFromId(e->getEntityID()))//hay que ver que el nodo existe, si no explota
                    smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);
                //std::cout<<"X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
            }
            //delete phycmp;
        }
        //delete e;
    }
    
    
}

void irrlichtGraphics::checkColisions(){
    //este metodo es hiper cutre, pero con algo hay que tirar hasta que esten las colisiones en su sistema xd
    irr::core::aabbox3d<irr::f32> b1, b2, b3;
    irr::scene::ISceneNode* nodeplayer;
    irr::scene::ISceneNode* nodezone;
    nodeplayer = smgr->getSceneNodeFromName("player");//saco el nodo del player
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
                std::string nombre = nombres_zonas[i].substr(5,2);
                EventInfo info;
                info.zone = std::stoi(nombre);
                EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
                EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
                EventManager::getInstancia().addEvent(Event{EventType::Change_Zone,info});//leo la nueva zona del json
                EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
                break;
            }
        }   
   }
}

void irrlichtGraphics::renderScene()  {
    driver->beginScene(true, true, irr::video::SColor(100,20,101,140));
    smgr->drawAll();   
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