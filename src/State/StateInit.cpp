#include "StateInit.hpp"
#include "../facade/ControllerMan.hpp"
#include "../facade/RavenSound.hpp"
#include "../EventManager/EventManager.hpp"
#include <iostream>

StateInit::StateInit(){
    renderengine = ControllerMan::p().controller();
    RavenSound::getInstance().loadBanks("media/FMODR/Master.bank");
    RavenSound::getInstance().loadBanks("media/FMODR/Master.strings.bank");
    //soundSystem = RavenSound::getInstance();
    //soundSystem->loadBanks("media/FMODR/Master.bank");
    //soundSystem->loadBanks("media/FMODR/Master.strings.bank");
    playSoundEvent();
    addEventListeners();
}

void StateInit::addEventListeners(){
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Play_Music,std::bind(&StateInit::playSoundEvent,this,std::placeholders::_1)));
}

void StateInit::playSoundEvent(){
    RavenSound::getInstance().playEvent("event:/Música/BandaSonora");
    //soundSystem->playEvent("event:/Música/BandaSonora");
}

void StateInit::update(){
    //std::cout<<"estoy en el update del state init\n";
    //soundSystem->studioUpdate();
    RavenSound::getInstance().studioUpdate();
    EventManager::getInstancia().update();
}

void StateInit::getInput(){
    renderengine->getInputInit();
}

void StateInit::draw(){
    //std::cout<<"entro al draw del init\n";
    //renderengine->beginScene();
    renderengine->drawInit();
}

void StateInit::endScene(){
    //renderengine->endScene();
    //soundSystem->audioClose();
}