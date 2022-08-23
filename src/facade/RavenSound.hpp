#pragma once

#include "../Motor/MotorAudio/sound_fmod.hpp"

struct EventInfo;

struct RavenSound
{
    static RavenSound& getInstance();
    void loadBanks(const std::string& bankName);
    void loadEvent(const std::string& eventName);
    void playEvent(const std::string& eventName);
    void playEvent(const std::string& eventName,const std::string& eventParam,float changeParam);
    void stopEvent(const std::string& eventName);
    void walking(EventInfo);
    void stopwalking(EventInfo);
    void espada(EventInfo);
    void escudo(EventInfo);
    void arco(EventInfo);
    void bomba(EventInfo);
    void pocion(EventInfo);
    void correr(EventInfo);
    void beber(EventInfo);
    void cortar(EventInfo);
    void colisionEscudo(EventInfo);
    void nocolisionEspada(EventInfo);
    void explosion(EventInfo);
    void fuego(EventInfo);
    void colisionesHerida(EventInfo);
    void AmbienteIndustrial(EventInfo);
    void AmbienteBosque(EventInfo);
    void AmbienteNieve(EventInfo);
    void soltarFlecha(EventInfo);
    void soltarObjeto(EventInfo);
    void muerte(EventInfo);
    void flecha(EventInfo);
    void objeto(EventInfo);
    void abrirPuerta(EventInfo);
    void arrastrar(EventInfo);
    void mecanismo(EventInfo);
    void coger(EventInfo);
    void stopMusic(EventInfo info);
    void menuBack(EventInfo);
    void menuSelect(EventInfo);
    void menuCambio(EventInfo);
    void studioUpdate();
    void audioClose();
    void addEventListeners();

private:
    static RavenSound* ravensound;
    bool IsWalking{false};
    int aux{0};
    Sound_FMOD_t sonido;
}; //Fachada para FMOD
