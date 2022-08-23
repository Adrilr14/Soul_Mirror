#pragma once

#include <string>

struct RavenSound;


struct soundSystem_t 
{
    soundSystem_t(RavenSound& s);
    void cargarBancos(const std::string& b);
    void cargarEventos(const std::string& e);
    void ejecutarEvento(const std::string& e);
    void quitarEvento(const std::string& e);
    void actualizar();
    void cerrar();
private:
RavenSound& sound;
};
