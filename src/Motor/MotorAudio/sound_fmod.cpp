//CAMBIAR ESTO A C Q ESTA EN C++ Q LOS SONIDOS NO SUENAN BIEN EA

#include "sound_fmod.hpp"
#include <thread>        
#include <chrono>        

Sound_FMOD_t::Sound_FMOD_t(){
    void *extraDriverData = nullptr;

    systemStudio = nullptr;
    ourErrorCheck( FMOD::Studio::System::create(&systemStudio));
    ourErrorCheck( systemStudio->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData) );

    coreSystem = nullptr;
    ourErrorCheck( systemStudio->getCoreSystem(&coreSystem) );
}

Sound_FMOD_t::~Sound_FMOD_t(){
    ourErrorCheck( systemStudio->unloadAll() );
    ourErrorCheck( systemStudio->release() );
}

void Sound_FMOD_t::loadBanks(const std::string& bankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags){
   auto tFoundit = bancos.find(bankName);
   if(tFoundit != bancos.end()){
       return;
   }
	FMOD::Studio::Bank* pBank;
	ourErrorCheck(systemStudio->loadBankFile(bankName.c_str(), flags, &pBank));
	if (pBank) {
        bancos[bankName] = pBank;
	}
}

void Sound_FMOD_t::loadEvent(const std::string& eventName){
    auto tFoundIt = eventos.find(eventName);
    if(tFoundIt != eventos.end()){return;}
    FMOD::Studio::EventDescription* pDescripcion = nullptr;
    ourErrorCheck(systemStudio->getEvent(eventName.c_str(),&pDescripcion));
    if(pDescripcion){
        FMOD::Studio::EventInstance* pInstancia = nullptr;
        ourErrorCheck(pDescripcion->createInstance(&pInstancia));
        if(pInstancia){
            eventos[eventName] = pInstancia;
        }
    }

}

void Sound_FMOD_t::playEvent(const std::string& eventName){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit == eventos.end()){
        Sound_FMOD_t::loadEvent(eventName);
        tFoundit = eventos.find(eventName);
        if(tFoundit == eventos.end()){return;}
    }
    ourErrorCheck(tFoundit->second->start());
    //Sound_FMOD_t::sleep();
}

void Sound_FMOD_t::playEvent(const std::string& eventName,const std::string& eventParam,float value){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit == eventos.end()){
        Sound_FMOD_t::loadEvent(eventName);
        tFoundit = eventos.find(eventName);
        if(tFoundit == eventos.end()){return;}
    }
    //si lo ha encontrado hacemos un setParameter
    Sound_FMOD_t::setEventParameter(eventName,eventParam,value);
    ourErrorCheck(tFoundit->second->start());
    //Sound_FMOD_t::sleep(); 
}

void Sound_FMOD_t::stopEvent(const std::string& eventName,bool action){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit ==  eventos.end()){return;}
    FMOD_STUDIO_STOP_MODE eMode;
	eMode = action ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
	ourErrorCheck(tFoundit->second->stop(eMode));
}

void Sound_FMOD_t::getEventParameter(const std::string& eventName,const std::string& eventP,float *p){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit == eventos.end()){return;}
    ourErrorCheck(tFoundit->second->getParameterByName(eventP.c_str(),p));
}

void Sound_FMOD_t::setEventParameter(const std::string& eventName,const std::string& eventP,float p){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit == eventos.end()){return;}
    FMOD::Studio::EventDescription* eventDescription = nullptr;
    ourErrorCheck(systemStudio->getEvent(eventName.c_str(),&eventDescription));
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramDesc;
    ourErrorCheck(eventDescription->getParameterDescriptionByName(eventP.c_str(),&paramDesc));
    std::string name = paramDesc.name;
    ourErrorCheck(tFoundit->second->setParameterByName(name.c_str(),p));
}


void Sound_FMOD_t::studioUpdate(){
    ourErrorCheck(systemStudio->update());
}

    
void Sound_FMOD_t::audioClose(){

    Sound_FMOD_t::~Sound_FMOD_t();
}

void Sound_FMOD_t::sleep(){
    std::this_thread::sleep_for (std::chrono::seconds(1));
}

bool Sound_FMOD_t::ourErrorCheck(FMOD_RESULT result){
    if(result == FMOD_OK)
        return true;
    return false;
}
