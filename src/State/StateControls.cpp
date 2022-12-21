#include "StateControls.hpp"
#include "../facade/ControllerMan.hpp"
#include "../EventManager/EventManager.hpp"

StateControls::StateControls(){
    renderengine = ControllerMan::p().controller();
}

void StateControls::getInput(){
    renderengine->getInputControls();
}

void StateControls::update(){
    EventManager::getInstancia().update();
}

void StateControls::draw(){
    //renderengine->beginScene();
    renderengine->drawControls();
}

void StateControls::endScene(){
    //renderengine->endScene();
}