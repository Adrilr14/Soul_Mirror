
#pragma once

#include "Entidad.hpp"

//class RShader;
class RMalla;

//assimp library
//#include "cimport.hpp"

class EModelo : public Entidad {
public:
    EModelo (RMalla *m); 
    ~EModelo ();

    void cargarModelo (const char* f);
    
    void dibujar (glm::mat4x4 mat, unsigned int shader) override;

private:
    RMalla *malla;
};
