#pragma once

#include "fmod_studio.hpp"
#include "fmod.hpp"
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
FMOD::Studio::System* systemStudio;
FMOD::System* coreSystem = nullptr;
typedef std::map<std::string,FMOD::Studio::Bank*> BankMap;
typedef std::map<std::string,FMOD::Studio::EventInstance*> EventMap;
BankMap bancos;
EventMap eventos;
void *extraDriverData = nullptr;
};
