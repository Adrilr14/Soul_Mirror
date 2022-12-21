#pragma once

extern "C" {
    #include "fmod_studio.h"
    #include "fmod.h"
}

#include <string>
#include <map>

struct Sound_FMOD_t
{
    Sound_FMOD_t();
    ~Sound_FMOD_t();
    void loadBanks(const std::string& bankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
    void loadEvent(const std::string& eventName);
    void playEvent(const std::string& eventName);
    void playEvent(const std::string& eventName,const std::string& eventParam,float value);
    void stopEvent(const std::string& eventName, bool action = false);
    void getEventParameter(const std::string& eventName,const std::string& eventP, float *parametro);
    void setEventParameter(const std::string& eventName,const std::string& eventP, float  parametro);
    void studioUpdate();
    void audioClose();
    void sleep();
    bool ourErrorCheck(FMOD_RESULT result);

private:
    FMOD_STUDIO_SYSTEM* systemStudio;
    FMOD_SYSTEM* coreSystem = nullptr;
    typedef std::map<std::string,FMOD_STUDIO_BANK*> BankMap;
    typedef std::map<std::string,FMOD_STUDIO_EVENTINSTANCE*> EventMap;
    BankMap bancos;
    EventMap eventos;
    void *extraDriverData = nullptr;
};
