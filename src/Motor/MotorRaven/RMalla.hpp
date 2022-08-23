#pragma once

// ASSIMP library
//#include <Importer.hpp>
//#include <assimp/scene.h>
//#include <postprocess.h>

#include "Recurso.hpp"
#include "Malla.hpp"
#include "RTextura.hpp"
#include <iostream>
#include <vector>

// GLM library
#include "vec2.hpp" // glm::vec2
#include "vec3.hpp" // glm::vec3

//class RShader;
//class Malla;
class RTextura;

/*struct VertexSkybox {
    // position
    glm::vec3 position;
};*/

class RMalla : public Recurso
{
public:
    RMalla(std::string path, RTextura *t);
    ~RMalla();

    void cargarFichero (const char* fichero) override; // Malla

    void cargarSkybox (const char* fichero);
    std::vector<Vertex> getVertexSkybox () {return vertexSkybox;}
    std::vector<unsigned int> getIndicesSkybox () {return indSkybox;}
    
    void dibujar (unsigned int shader);
    void setTextura (RTextura *t) {
        if(t)
        {
            textura = t;
            for(unsigned int i = 0; i < mallas.size(); i++)
            {
                mallas[i].setTextura(t);
            }
        }     
    }

    std::string getTextura(){
        return textura->getPath();
    }
private:
    std::vector<Malla> mallas;
    RTextura *textura;
    
    // -- vertices, normales, coordtex

    std::vector<Vertex> vertexSkybox; // vertices
    std::vector<unsigned int> indSkybox; // indices
};
