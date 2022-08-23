//#include "Game.hpp"
//#include "facade/RavenGraphics.hpp"
//#include "ecs/man/entityManager.hpp"
//#include "facade/ControllerMan.hpp"
//#include "EventManager/EventManager.hpp"
//#include "Motor/BulletEngine/BulletEngine.hpp"
//#include <iostream>
//#include <string_view>
//
//Game* Game::game = 0;
//Game* Game::GetInstance() {
//    if (game == 0) {
//        game = new Game();
//    }
//    return game;
//}
//
//void Game::InitGame(){
//   //creo los sistemas y tal
//    //BulletEngine::getInstancia().createWolrdSystem();
//    bullet_t = std::make_shared<BulletEngine>();
//    bullet_t->createWolrdSystem();
//    ControllerMan::p().controller().worldPhysics(bullet_t);
//    //bullet_t->createFloor();    
//    factory = std::make_unique<GameOBjectFactory_t>(manager,bullet_t); //TODO: Quitar el acoplado
//    physics = std::make_unique<PhysicsSystem_t>(manager,bullet_t);
//    physics->addEventListeners();
//    camera = std::make_unique<CameraSystem_t>(manager);
//    collision = std::make_unique<CollisionSystem_t>(manager,bullet_t);
//    shoot = std::make_unique<ShootSystem_t>(manager);
//    ia = std::make_unique<IAPhySystem_t>(manager);
//    //GameOBjectFactory_t factory { manager };
//    factory->addEventListeners();
//    //EventManager::getInstancia().addEvent(Event{EventType::Change_Zone});
//    EventInfo info;
//    info.zone = 1;
//    factory->readLevel(info);
//    //meto las entidades iniciales del mapa
//    ControllerMan::p().controller().addManager(manager);
//    ControllerMan::p().controller().addEntities(info);
//}
//
//void Game::MainLoop(){
//    std::cout<<"entro al mainloop\n";
//    
//    //el controllerman tiene las funciones del input y del render, no es un nombre demasiado intuitivo pero bueno
//    while(ControllerMan::p().controller().run()){
//        ControllerMan::p().controller().renderScene();
//        ControllerMan::p().controller().getInput();
//        //input.update();
//        physics->physicsUpdate();
//        camera->cameraUpdate();
//        ia->update();
//        shoot->update();
//        shoot->updateToDestroy();
//        collision->update();
//        bullet_t->updateCollisionEngine();
//        //ControllerMan::p().controller().checkColisions();
//        ControllerMan::p().controller().updateEntities();
//        ControllerMan::p().controller().cameraUpdate();
//        ControllerMan::p().controller().endScene();
//        EventManager::getInstancia().update();
//        //if(i == 0){
//            //std::cout<<"Al final del ciclo, el size del vector de entitys es: "<<manager.getEntities().size()<<"\n";
//            //++i;
//    }
//}
//








#include "Game.hpp"
#include "facade/RavenGraphics.hpp"
#include "ecs/man/entityManager.hpp"
#include "facade/ControllerMan.hpp"
#include "EventManager/EventManager.hpp"
#include <iostream>
#include <string_view>
#include "State/StateInit.hpp"
#include "State/StateCredits.hpp"
#include "State/StateGame.hpp"
#include "State/StateControls.hpp"


//Game* Game::GetInstance() {
//    if (game.get() == nullptr) {
//        game = std::make_unique<Game>();
//    }
//    return game.get();
//}

Game* Game::game = 0;
Game* Game::GetInstance() {
    if (game == 0) {
        game = new Game();
    }
    return game;
}

void Game::InitGame(){
    
   //creo los sistemas y tal
   //state = std::make_unique<State>(); 
    renderengine = ControllerMan::p().controller();

    //std::cout << "El renderengine  " << renderengine;
    //factory = std::make_unique<GameOBjectFactory_t>(manager);
    //physics = std::make_unique<PhysicsSystem_t>(manager);
    //physics->addEventListeners();
    //camera = std::make_unique<CameraSystem_t>(manager);
    //shoot = std::make_unique<ShootSystem_t>(manager);
    //ia = std::make_unique<IAPhySystem_t>(manager);
    //factory->addEventListeners();
    //EventManager::getInstancia().addEvent(Event{EventType::Change_Zone});
    //EventInfo info;
    //info.zone = 1;
    //factory->readLevel(info);
    //meto las entidades iniciales del mapa
    //renderengine->addManager(manager);
    //renderengine->addEntities(info);
    addEventListeners();
}

void Game::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::State_Change,std::bind(&Game::setStateChange,this,std::placeholders::_1)));
}

void Game::setState(State::State_Type statetype){
    switch(statetype){
        case State::State_Type::INIT:
            state = std::make_unique<StateInit>(); 
        break;
        case State::State_Type::CONTROLS:
            state = std::make_unique<StateControls>(); 
        break;
        case State::State_Type::GAME:
            state = std::make_unique<StateGame>(); 
        break;
        case State::State_Type::CREDITS:
            state = std::make_unique<StateCredits>(); 
        break;
    }

}

void Game::setStateChange(EventInfo info){
    switch(info.state_type){
        case 1:
            setState(State::State_Type::INIT);
        break;
        case 3:
            setState(State::State_Type::CONTROLS);
        break;
        case 4:
            setState(State::State_Type::GAME);
        break;
        case 5:
            setState(State::State_Type::CREDITS);
        break;
    }
}

void Game::pauseFalse(){
    if(gamePaused)
        gamePaused = false;
}

void Game::pauseTrue(){
    if(!gamePaused)
        gamePaused = true;
}

bool Game::isPlayerDead() const{
    return playerDead;
}

void Game::setPlayerDead(bool dead){
    playerDead = dead;
}

void Game::MainLoop(){
    //el controllerman tiene las funciones del input y del render, no es un nombre demasiado intuitivo pero bueno
    //ControllerMan::p().controller().run()
    renderengine->beginScene();
    while(renderengine->run()){
        if(!gamePaused){
            state->draw();
            state->getInput();
            state->update();
            state->endScene();
        }
        else{
            renderengine->drawPause();
            renderengine->getInputPause();
            renderengine->endScene();
        }
    }
    renderengine->endScene();
}

        /*renderengine->renderScene();
        renderengine->getInputGame();
        physics->physicsUpdate();
        camera->cameraUpdate();
        ia->update();
        shoot->update();
        shoot->updateToDestroy();
        renderengine->checkColisions();
        EventManager::getInstancia().update();
        renderengine->updateEntities();
        renderengine->cameraUpdate();
        manager.deleteMarkedEntities();
        renderengine->endScene();*/