#pragma once

#include "Entidad.hpp"
#include <vector>
#include <memory>

class RMalla;
class RTextura;

class Animacion : public Entidad {
public:
    Animacion (std::vector<RMalla*> mallas_, int fps_, RTextura *t); 
    ~Animacion ();

    //void cargarModelo (const char* f);
    
    void dibujar (glm::mat4x4 mat, unsigned int shader) override;

    bool isEnd () { return end; }
    void setEnd (bool end_) { end = end_; }
    void setNumMalla (int nMalla_) { nMalla = nMalla_; }

private:
    //std::vector<std::unique_ptr<RMalla>> mallas;
    std::vector<RMalla*> mallas;
    int nMalla; // Número de malla a dibujar
    RTextura *textura; // Textura de la animacion
    
    // Variables de tiempo
    double before;
    int fps;

    // Variable para saber si ha terminado la animación
    bool end;
};
