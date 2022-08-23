
#pragma once

#include "Entidad.hpp"

//class RShader;
class RMalla;
class RTextura;

//assimp library
//#include "cimport.hpp"

class EModelo : public Entidad {
public:
    EModelo (RMalla *m, RTextura *t);
    ~EModelo ();

    void cargarModelo (const char* f);
    
    void dibujar (glm::mat4x4 mat, unsigned int shader) override;

    RMalla *getMalla () {return malla;}

    void setTextura (RTextura *t) {if(t) textura = t;}

private:
    RMalla *malla;
    RTextura* textura;
};
