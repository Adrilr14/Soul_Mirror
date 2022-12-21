#include <facade/irrlichtGraphics.hpp>


irrlichtGraphics::~irrlichtGraphics(){
    
}
void irrlichtGraphics::createWindow(uint32_t w, uint32_t h)  {
    irr.createWindow(w,h);
}
void irrlichtGraphics::beginScene()  {

}

bool irrlichtGraphics::run()  {
    return irr.getDeviceRun();
}
void irrlichtGraphics::endScene()  {

}
void irrlichtGraphics::renderInit()  {
    irr.renderInit();
}
void irrlichtGraphics::physicsInit()  {
    irr.physicsInit();
}

void irrlichtGraphics::cameraUpdate()  {

}

void irrlichtGraphics::renderScene()  {
    irr.run();
}


/*#include <facade/irrlichtGraphics.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/CameraComponent.hpp>
#include <game/cmp/IAComponent.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/StaticComponent.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <EventManager/EventManager.hpp>
#include <iostream>



irrlichtGraphics::irrlichtGraphics(){
    device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920,1080), 16, false, false, true, &input);
    if(device){
    	device->setWindowCaption(L"SoulMirror");
    	driver = device->getVideoDriver();
    	smgr = device->getSceneManager();
    	guienv = device->getGUIEnvironment();
    }
}

irrlichtGraphics::~irrlichtGraphics(){
    
}

void irrlichtGraphics::createWindow(){
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
        if(e && e->template getComponent<DirecComponent_t>()){
            auto* dircmp = e->getComponent<DirecComponent_t>();
            if(input.IsKeyDown(irr::KEY_KEY_D)){
                EventManager::getInstancia().onEvent(Event{EventType::Input_D});
                dircmp->dir = 1;//derecha
            }
            if(input.IsKeyDown(irr::KEY_KEY_A))
                dircmp->dir = 2;//izquierda    
            if(input.IsKeyDown(irr::KEY_KEY_W))
                dircmp->dir = 3;//arriba
            if(input.IsKeyDown(irr::KEY_KEY_S))
                dircmp->dir = 4;//abajo
            if(input.IsKeyDown(irr::KEY_KEY_D) && input.IsKeyDown(irr::KEY_KEY_W))
                dircmp->dir = 5; // Dirección hacia derecha-arriba
            else if(input.IsKeyDown(irr::KEY_KEY_A) && input.IsKeyDown(irr::KEY_KEY_W))
                dircmp->dir = 6; // Dirección hacia izquierda-arriba
            else if(input.IsKeyDown(irr::KEY_KEY_D) && input.IsKeyDown(irr::KEY_KEY_S))
                dircmp->dir = 7; // Dirección hacia derecha-abajo
            else if(input.IsKeyDown(irr::KEY_KEY_A) && input.IsKeyDown(irr::KEY_KEY_S))
                dircmp->dir = 8; //Dirección hacia izquierda-abajo
        }
    
}

void irrlichtGraphics::addEntities(){
    //TODO Revisar esto para los accesos mejor a los arrays. Physics va a tener casi todo, hay que echarle un ojo
    //esto de momento va asi porque no se las posiciones de las paredes y cosas del entorno, pero hay que mejorarlo
    //todas las entidades deben tener un position asociado, y al final deberian ser todos animatedmeshes porque seran objetos modelados
    //std::cout<<"entro al add\n";
    for(auto& e : manager->getEntities()){
        if(e.template getComponent<PhysicsComponent_t>()){
            auto* phy = e.template getComponent<PhysicsComponent_t>();
            if(e.template getComponent<StaticComponent_t>() && e.template getComponent<RenderComponent_t>()){
            //std::string path = ;
            mesh = smgr->getMesh(e.template getComponent<RenderComponent_t>()->modelPath.data());
            node = smgr->addAnimatedMeshSceneNode( mesh );irr::core::vector3d<irr::f32>* edges = new irr::core::vector3d<irr::f32>[8];
                irr::core::aabbox3d<irr::f32> boundingbox = node->getTransformedBoundingBox();
                boundingbox.getEdges(edges);
                irr::f32 height = edges[1].Y - edges[0].Y; //OK
                std::cout<<"height: "<<height<<std::endl;

                irr::f32 width = edges[5].X - edges[1].X;
                std::cout<<"width: "<<width<<std::endl;

                irr::f32 depth = edges[2].Z - edges[0].Z;
                std::cout<<"depth: "<<depth<<std::endl;

            node->setMaterialTexture(0, driver->getTexture(e.template getComponent<RenderComponent_t>()->texturePath.data()));
            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            node->setID(e.getEntityID());
            //node->setPosition(irr::core::vector3df(50,0,50));
            //std::cout<<"Posicion de la pared:"<<node->getPosition().X<<" "<<node->getPosition().Z<<"\n";
            }
            else if(e.template getComponent<InputComponent_t>()){
                std::cout<<"hay input\n";
                object = smgr->addCubeSceneNode(4);
                
                object->setID(e.getEntityID());
                object->setMaterialTexture(0, driver->getTexture(e.template getComponent<RenderComponent_t>()->texturePath.data()));
                object->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                //auto* phy = e.template getComponent<PhysicsComponent_t>();
                object->setPosition(irr::core::vector3df(phy->x,phy->y,phy->z));
            }
            else if(e.template getComponent<IAComponent_t>()){
                std::cout<<"Hay enemys\n";
                object = smgr->addCubeSceneNode(4);
                object->setID(e.getEntityID());
                //auto* phy = e.template getComponent<PhysicsComponent_t>();
                object->setPosition(irr::core::vector3df(phy->x,phy->y,phy->z));
            }
        }   
    }
    //despues de crear las entidades creo la camara en un sitio random
    Addcamera();
}

void irrlichtGraphics::probando(){
    if(smgr->getSceneNodeFromId(1)){
        std::cout<<"Posicion XYX: "<<smgr->getSceneNodeFromId(1)->getPosition().X<<" "<<smgr->getSceneNodeFromId(1)->getPosition().Y 
        <<" "<<smgr->getSceneNodeFromId(1)->getPosition().Z<<"\n";
    }
}

void irrlichtGraphics::Addcamera(){
    //std::cout<<"entro al addcamera\n";
    for(auto& e : manager->getComponents<CameraComponent_t>()){
        camera = smgr->addCameraSceneNode(0, irr::core::vector3df(120,40,-86));
        smgr->getActiveCamera()->setTarget(smgr->getSceneNodeFromId(1)->getPosition());
    }
}

void irrlichtGraphics::cameraUpdate() {
    //std::cout<<"entro al camera upate\n";
    //irr::core::vector3df camaraPosition;
    //float x,y,z = 0;
    auto& camcmp = manager->getComponents<CameraComponent_t>();
        auto* e = manager->getEntityByID(camcmp[0].getEntityID());
        if(e)
            //std::cout<<"la camara existe\n";
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->getComponent<PhysicsComponent_t>();
            if(phycmp){
                //x = phycmp->x;
                //y = phycmp->y;
                //z = phycmp->z;
                smgr->getActiveCamera()->setPosition(irr::core::vector3df(phycmp->x,phycmp->y,phycmp->z));
                smgr->getActiveCamera()->setTarget(smgr->getSceneNodeFromId(1)->getPosition());
            //std::cout<<"Camara X: "<<phycmp->x<<" Camara Y: "<<phycmp->y<<" Camara Z: "<<phycmp->z<<"\n";
            }
        }
    
    //camaraPosition.X = x; camaraPosition.Y = y; camaraPosition.Z = z;
    //smgr->getActiveCamera()->setPosition(camaraPosition);
    
}

void irrlichtGraphics::updateEntities(){
    irr::core::vector3df newPosition;
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
                //node = smgr->getSceneNodeFromId(e->getEntityID());
                //node = smgr->getSceneNodeFromName(e->getName().data());
                smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);
            }
        }
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
                smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);
                //std::cout<<"X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
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
*/