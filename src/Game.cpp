#include <Game.hpp>
//#include <game/sys/render.hpp>
//#include <game/sys/physics.hpp>
//#include <game/sys/camera.hpp>
//#include <game/sys/input.hpp>
//#include <game/sys/IAphysics.hpp>
#include <ecs/man/entityManager.hpp>
#include <facade/ControllerMan.hpp>
#include <game/util/gameobjectfactory.hpp>
#include <EventManager/EventManager.hpp>
#include <iostream>



Game* Game::game = 0;
Game* Game::GetInstance() {
    if (game == 0) {
        game = new Game();
    }
    return game;
}

void Game::InitGame(){
    
   //creo los sistemas y tamedia/obj/z1_z2_p2.objl
    physics = std::make_unique<PhysicsSystem_t>(manager);
    camera = std::make_unique<CameraSystem_t>(manager);
    ia = std::make_unique<IAPhySystem_t>(manager);
    collider = std::make_unique<CollisionSystem_t>(manager);
    GameOBjectFactory_t factory { manager };
    factory.readLevel("level1.json");
    //factory.createPlayer(10.0f,120,0,-86);
    //factory.createStaticEntity("pared_1","media/z1_p1.STL","media/color_pared.jpg");
    //factory.createStaticEntity("pared_2","media/z1_p2.STL","media/color_pared.jpg");
    //factory.createStaticEntity("pared_3","media/z1_p3.STL","media/color_pared.jpg");
    //factory.createStaticEntity("pared_4","media/z1_p4.STL","media/color_pared.jpg");
    //factory.createStaticEntity("pared_5","media/z1_p5.STL","media/color_pared.jpg");
    //factory.createStaticEntity("pared_6","media/z1_p6.STL","media/color_pared.jpg");
    //factory.createStaticEntity("pared_7","media/z1_p7.STL","media/color_pared.jpg");
    
    factory.createCamera();//int32_t ax, int32_t ay, int32_t az, std::string_view nombre, std::string_view ruta
    //factory.createEnemy(99,0,-67,"enemy","xd");
    
    
    //les paso el entity manager a todos
    //physics.addManager(manager);
    //input->addManager(manager);
    //camera.addManager(manager);
    //ia->addManager(manager);
        
    //meto las entidades iniciales del mapa
    //ControllerMan::p().controller().createWindow();
    ControllerMan::p().controller().addManager(manager);
    ControllerMan::p().controller().addEntities();
}

void Game::MainLoop(){
    std::cout<<"entro al mainloop\n";
    //el controllerman tiene las funciones del input y del render, no es un nombre demasiado intuitivo pero bueno
    ControllerMan::p().controller().createWindow(1920,1080);
    ControllerMan::p().controller().renderInit();
    ControllerMan::p().controller().physicsInit();
    while(ControllerMan::p().controller().run()){
        ControllerMan::p().controller().renderScene();
        //ControllerMan::p().controller().renderScene();
        //ControllerMan::p().controller().getInput();
        ////input.update();
        //physics->physicsUpdate();
        //camera->cameraUpdate();
        //ia->update();
        //collider->update();
        //ControllerMan::p().controller().updateEntities();
        //ControllerMan::p().controller().cameraUpdate();
        //ControllerMan::p().controller().endScene();
        //EventManager::getInstancia().update();
    }
}
