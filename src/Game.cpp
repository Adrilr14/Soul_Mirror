#include <Game.hpp>
#include <facade/RavenGraphics.hpp>
#include <ecs/man/entityManager.hpp>
#include <facade/ControllerMan.hpp>
#include <EventManager/EventManager.hpp>
#include <iostream>
#include <string_view>


Game* Game::game = 0;
Game* Game::GetInstance() {
    if (game == 0) {
        game = new Game();
    }
    return game;
}

void Game::InitGame(){
    
   //creo los sistemas y tal
    factory = std::make_unique<GameOBjectFactory_t>(manager);
    physics = std::make_unique<PhysicsSystem_t>(manager);
    physics->addEventListeners();
    camera = std::make_unique<CameraSystem_t>(manager);
    collision = std::make_unique<CollisionSystem_t>(manager);
    ia = std::make_unique<IAPhySystem_t>(manager);
    //GameOBjectFactory_t factory { manager };
    factory->addEventListeners();
    //EventManager::getInstancia().addEvent(Event{EventType::Change_Zone});
    EventInfo info;
    info.zone = 1;
    factory->readLevel(info);
    //meto las entidades iniciales del mapa
    ControllerMan::p().controller().addManager(manager);
    ControllerMan::p().controller().addEntities(info);
}

void Game::MainLoop(){
    std::cout<<"entro al mainloop\n";
    
    //el controllerman tiene las funciones del input y del render, no es un nombre demasiado intuitivo pero bueno
    while(ControllerMan::p().controller().run()){
        ControllerMan::p().controller().renderScene();
        ControllerMan::p().controller().getInput();
        //input.update();
        physics->physicsUpdate();
        camera->cameraUpdate();
        ia->update();
        collision->update();
        ControllerMan::p().controller().checkColisions();
        EventManager::getInstancia().update();
        ControllerMan::p().controller().updateEntities();
        ControllerMan::p().controller().cameraUpdate();
        ControllerMan::p().controller().endScene();
        //if(i == 0){
            //std::cout<<"Al final del ciclo, el size del vector de entitys es: "<<manager.getEntities().size()<<"\n";
            //++i;
    }
}
