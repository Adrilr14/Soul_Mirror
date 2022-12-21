#pragma once

// ASSIMP library
//#include <Importer.hpp>
//#include <assimp/scene.h>
//#include <postprocess.h>

#include "Recurso.hpp"
#include <iostream>
#include <vector>

// GLM library
#include "vec2.hpp" // glm::vec2
#include "vec3.hpp" // glm::vec3

//class RShader;
class Malla;
class RTextura;

class RMalla : public Recurso
{
public:
    RMalla(std::string path, RTextura *t);
    ~RMalla();

    void cargarFichero (const char* fichero) override; // Malla
    
    void dibujar (unsigned int shader);

private:
    std::vector<Malla> mallas;
    RTextura *textura;
    
    // -- vertices, normales, coordtex
};
