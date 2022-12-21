#include <facade/RavenSound.hpp>

void RavenSound::loadBanks(const std::string& bankName){
    sonido.loadBanks(bankName,FMOD_STUDIO_LOAD_BANK_NORMAL);
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