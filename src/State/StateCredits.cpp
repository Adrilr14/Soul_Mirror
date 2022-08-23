#include "StateCredits.hpp"
#include "../EventManager/EventManager.hpp"
#include "../facade/ControllerMan.hpp"

StateCredits::StateCredits(){
    renderengine = ControllerMan::p().controller();
}

void StateCredits::getInput(){
    renderengine->getInputCredits();
}

void StateCredits::update(){
    EventManager::getInstancia().update();
}

void StateCredits::draw(){
    //renderengine->beginScene();
    renderengine->drawCredits();
}

void StateCredits::endScene(){
    //renderengine->endScene();
}