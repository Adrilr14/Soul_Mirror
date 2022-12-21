#include "RavenSound.hpp"
#include "../EventManager/EventManager.hpp"

RavenSound& RavenSound::getInstance(){
    static RavenSound instance;
    return instance;
}

void RavenSound::loadBanks(const std::string& bankName){
    sonido.loadBanks(bankName,FMOD_STUDIO_LOAD_BANK_NORMAL);
    addEventListeners();
}

void RavenSound::loadEvent(const std::string& eventName){
    sonido.loadEvent(eventName);
}

void RavenSound::playEvent(const std::string& eventName){
    sonido.playEvent(eventName);
}

void RavenSound::playEvent(const std::string& eventName,const std::string& eventParam,float changeParam){
    sonido.playEvent(eventName,eventParam,changeParam);
}

void RavenSound::stopEvent(const std::string& eventName){
    sonido.stopEvent(eventName,false);
}

void RavenSound::studioUpdate(){
    sonido.studioUpdate();
}

void RavenSound::audioClose(){
    sonido.audioClose();
}

void RavenSound::walking(EventInfo info){
    if(aux == 0)
        playEvent("event:/Efectos/caminar","Terreno",1.0);
    ++aux;    
}

void RavenSound::stopwalking(EventInfo){
    aux = 0;
    stopEvent("event:/Efectos/caminar");
}

void RavenSound::espada(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",0);
}

void RavenSound::escudo(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",3);
}

void RavenSound::bomba(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",2);
}

void RavenSound::arco(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",1);
}

void RavenSound::pocion(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",4);
}

void RavenSound::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_W,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_A,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_S,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_D,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WD,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WA,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SD,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SA,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Stop_Walking,std::bind(&RavenSound::stopwalking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_1,std::bind(&RavenSound::espada,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_2,std::bind(&RavenSound::escudo,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_3,std::bind(&RavenSound::arco,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_4,std::bind(&RavenSound::bomba,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_5,std::bind(&RavenSound::pocion,this,std::placeholders::_1)));
}