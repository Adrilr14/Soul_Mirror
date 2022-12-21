#include "StateGame.hpp"
#include "../ecs/man/entityManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../facade/ControllerMan.hpp"
#include "../facade/RavenSound.hpp"

StateGame::StateGame(){
    renderengine = ControllerMan::p().controller();
    RavenSound::getInstance().stopEvent("event:/Música/BandaSonora");
    //RavenSound::getInstance().loadBanks("media/FMODR/Master.bank");
    //soundSystem->loadBanks("media/FMODR/Master.strings.bank");
    //soundSystem->loadbanks();
    bullet_t = std::make_shared<BulletEngine>();
    bullet_t->createWolrdSystem();
    renderengine->worldPhysics(bullet_t);
    factory = std::make_unique<GameObjectFactory_t>(manager,bullet_t);
    physics = std::make_unique<PhysicsSystem_t>(manager,bullet_t);
    physics->addEventListeners();
    camera = std::make_unique<CameraSystem_t>(manager);
    collision = std::make_unique<CollisionSystem_t>(manager,bullet_t);
    collision->addEventListeners();
    shoot = std::make_unique<ShootSystem_t>(manager);
    ia = std::make_unique<IAPhySystem_t>(manager);
    factory->addEventListeners();
    EventInfo info;
    info.zone = 1;
    factory->readLevel(info);
    //meto las entidades iniciales del mapa
    renderengine->addManager(manager);
    renderengine->addEntities(info);
    addEventListeners();
    playEvent();
}

void StateGame::playEvent(){
    RavenSound::getInstance().playEvent("event:/Ambientes/Bosque");
    //soundSystem->playEvent("event:/Ambientes/Bosque");
}

void StateGame::addEventListeners(){
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Play_Music,std::bind(&StateGame::playSoundEvent,this,std::placeholders::_1)));
}

void StateGame::playSoundEvent(EventInfo info){
    //soundSystem->playEvent(info.soundname);
}

void StateGame::update(){
    camera->cameraUpdate();
    ia->update();
    shoot->update();
    shoot->updateToDestroy();
    collision->update();
    physics->physicsUpdate();
    //renderengine->checkColisions();
    bullet_t->updateCollisionEngine();
    RavenSound::getInstance().studioUpdate();
    EventManager::getInstancia().update();
    renderengine->updateEntities();
    renderengine->cameraUpdate();
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