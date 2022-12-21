#pragma once

#include <Motor/MotorAudio/sound_fmod.hpp>

struct RavenSound
{
    void loadBanks(const std::string& bankName);
    void loadEvent(const std::string& eventName);
    void playEvent(const std::string& eventName);
    void playEvent(const std::string& eventName,const std::string& eventParam,float changeParam);
    void stopEvent(const std::string& eventName);
    void studioUpdate();
    void audioClose();

private:
Sound_FMOD_t sonido;
}; //Fachada para FMOD
