
#include "sound_fmod.hpp"
#include <thread>        
#include <chrono>        

Sound_FMOD_t::Sound_FMOD_t(){
    void *extraDriverData = nullptr;

    systemStudio = nullptr;
    ourErrorCheck( FMOD_Studio_System_Create(&systemStudio,FMOD_VERSION));
    ourErrorCheck( FMOD_Studio_System_Initialize(systemStudio,1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData) );

    coreSystem = nullptr;
    ourErrorCheck( FMOD_Studio_System_GetCoreSystem(systemStudio,&coreSystem) );
}

Sound_FMOD_t::~Sound_FMOD_t(){
    ourErrorCheck(FMOD_Studio_System_UnloadAll(systemStudio) );
    ourErrorCheck( FMOD_Studio_System_Release(systemStudio) );
}

void Sound_FMOD_t::loadBanks(const std::string& bankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags){
   auto tFoundit = bancos.find(bankName);
   if(tFoundit != bancos.end()){
       return;
   }
    
	FMOD_STUDIO_BANK* pBank;
	ourErrorCheck(FMOD_Studio_System_LoadBankFile(systemStudio, bankName.c_str(), flags, &pBank));
	if (pBank) {
        bancos[bankName] = pBank;
	}
}

void Sound_FMOD_t::loadEvent(const std::string& eventName){
    auto tFoundIt = eventos.find(eventName);
    if(tFoundIt != eventos.end()){return;}
    FMOD_STUDIO_EVENTDESCRIPTION* pDescripcion = nullptr;
    ourErrorCheck(FMOD_Studio_System_GetEvent(systemStudio, eventName.c_str(),&pDescripcion));
    if(pDescripcion){
        FMOD_STUDIO_EVENTINSTANCE* pInstancia = nullptr;
        ourErrorCheck(FMOD_Studio_EventDescription_CreateInstance(pDescripcion, &pInstancia));
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
    
    ourErrorCheck(FMOD_Studio_EventInstance_Start(tFoundit->second));
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
    ourErrorCheck(FMOD_Studio_EventInstance_Start(tFoundit->second));
    //Sound_FMOD_t::sleep(); 
}

void Sound_FMOD_t::stopEvent(const std::string& eventName,bool action){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit ==  eventos.end()){return;}
    FMOD_STUDIO_STOP_MODE eMode;
	eMode = action ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
	ourErrorCheck(FMOD_Studio_EventInstance_Stop(tFoundit->second,eMode));
}

void Sound_FMOD_t::getEventParameter(const std::string& eventName,const std::string& eventP,float *p){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit == eventos.end()){return;}
    ourErrorCheck(FMOD_Studio_System_GetParameterByName(systemStudio,eventP.c_str(),p,nullptr));
}

void Sound_FMOD_t::setEventParameter(const std::string& eventName,const std::string& eventP,float p){
    auto tFoundit = eventos.find(eventName);
    if(tFoundit == eventos.end()){return;}
    FMOD_STUDIO_EVENTDESCRIPTION* eventDescription = nullptr;
    ourErrorCheck( FMOD_Studio_System_GetEvent(systemStudio,eventName.c_str(),&eventDescription));
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramDesc;
    ourErrorCheck( FMOD_Studio_EventDescription_GetParameterDescriptionByName(eventDescription,eventP.c_str(),&paramDesc));
    std::string name = paramDesc.name;
    ourErrorCheck(FMOD_Studio_System_SetParameterByName(systemStudio,name.c_str(),p,false));
}


void Sound_FMOD_t::studioUpdate(){
    ourErrorCheck(FMOD_Studio_System_Update(systemStudio));
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
