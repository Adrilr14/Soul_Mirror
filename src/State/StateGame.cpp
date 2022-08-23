#include "StateGame.hpp"
#include "../ecs/man/entityManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../facade/ControllerMan.hpp"
#include "../facade/RavenSound.hpp"
#include "../Game.hpp"

StateGame::StateGame(){
    renderengine = ControllerMan::p().controller();
    RavenSound::getInstance().stopEvent("event:/Música/BandaSonora");
    //RavenSound::getInstance().loadBanks("media/FMODR/Master.bank");
    //soundSystem->loadBanks("media/FMODR/Master.strings.bank");
    //soundSystem->loadbanks();

    factory = std::make_unique<GameObjectFactory_t>(manager, "Zonas/Bosque/", "zone_1");
    physics = std::make_unique<PhysicsSystem_t>(manager);
    physics->addEventListeners();
    camera = std::make_unique<CameraSystem_t>(manager);
    collision = std::make_unique<CollisionSystem_t>(manager);
    collision->addEventListeners();
    shoot = std::make_unique<ShootSystem_t>(manager);
    ia = std::make_unique<IAPhySystem_t>(manager);
    health = std::make_unique<HealthSystem_t>(manager);
    factory->addEventListeners();
    EventInfo info;
    info.zone = 1;
    factory->readLevel(info);
    //meto las entidades iniciales del mapa
    renderengine->addAnimations();
    renderengine->addManager(manager);
    renderengine->addEntities(info);
    addEventListeners();
    playEvent();
}

void StateGame::playEvent(){
    RavenSound::getInstance().playEvent("event:/Ambientes/industrial");
    //soundSystem->playEvent("event:/Ambientes/Bosque");
}

void StateGame::addEventListeners(){
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Play_Music,std::bind(&StateGame::playSoundEvent,this,std::placeholders::_1)));
}

void StateGame::playSoundEvent(EventInfo info){
    //soundSystem->playEvent(info.soundname);
}

void StateGame::update(){
    if(Game::GetInstance()->isPlayerDead() == false){
        camera->cameraUpdate();
        ia->update();
        shoot->update();
        collision->update();
        physics->physicsUpdate();
        renderengine->updateEntities();
        renderengine->cameraUpdate();
        health->Update();
    }
    EventManager::getInstancia().update();
    RavenSound::getInstance().studioUpdate();
    manager.updateEntitiesToBeDestroyed();
}

void StateGame::getInput(){
    renderengine->getInputGame();
}

void StateGame::draw(){
    //renderengine->beginScene();
    renderengine->drawGame();
}

void StateGame::endScene(){
    //renderengine->endScene();
}