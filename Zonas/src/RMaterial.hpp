#pragma once

#include "Recurso.hpp"

// GLM library
#include "vec3.hpp" // glm::vec3

class RMaterial : public Recurso
{
public:
    RMaterial(std::string n);
    ~RMaterial();

    void cargarFichero (const char* fichero) override; // Material

private:
    glm::vec3 Ka, Kd, Ks;
    float Ns, d;
    //Imagen mapaKa, mapaKd, mapaKs;
};
