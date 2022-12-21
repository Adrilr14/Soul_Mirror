#include <game/sys/sound.hpp>
#include <facade/RavenSound.hpp>

soundSystem_t::soundSystem_t(RavenSound& s) : sound{s}{}


void soundSystem_t::cargarBancos(const std::string& b){
    sound.loadBanks(b);
}

void soundSystem_t::cargarEventos(const std::string& e){
    sound.loadEvent(e);
}

void soundSystem_t::ejecutarEvento(const std::string& e){
    sound.playEvent(e);
}

void soundSystem_t::quitarEvento(const std::string& e){
    sound.stopEvent(e);
}

void soundSystem_t::actualizar(){
    sound.studioUpdate();
}

void soundSystem_t::cerrar(){
    sound.audioClose();
}