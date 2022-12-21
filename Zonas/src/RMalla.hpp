#pragma once

// ASSIMP library
#include <Importer.hpp>
#include <assimp/scene.h>
#include <postprocess.h>

#include "Recurso.hpp"
#include <iostream>
#include <vector>

//class RShader;
class Malla;
class RTextura;

class RMalla : public Recurso
{
public:
    RMalla(std::string path, RTextura *c, RTextura *h, RTextura *m, RTextura *n, RTextura *r);
    ~RMalla();

    void cargarFichero (const char* fichero) override; // Malla
    
    void dibujar (unsigned int shader);

private:
    std::vector<Malla> mallas;
    RTextura *diffuse;
    RTextura *height;
    RTextura *metalness;
    RTextura *normal;
    RTextura *roughness;

    Malla procesarMalla (aiMesh *mesh, const aiScene *scene);
    void procesarNodo(aiNode *node, const aiScene *scene);
    
    // -- vertices, normales, coordtex
};
