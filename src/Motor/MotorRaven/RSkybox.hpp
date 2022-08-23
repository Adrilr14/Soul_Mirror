/*#pragma once

#include "Recurso.hpp"
#include <iostream>
#include <vector>

// GLM library
#include "vec3.hpp" // glm::vec3

struct Vertex {
    // position
    glm::vec3 position;
};

class RSkybox : public Recurso
{
public:
    RSkybox(std::string path);
    ~RSkybox();

    void cargarFichero (const char* fichero) override; // Malla
    
    void dibujar (unsigned int shader);

    std::vector<Vertex> getVertices() {return vertex;}
    std::vector<unsigned int> getIndices() {return ind;}

private:
    std::vector<Vertex> vertex; // vertices
    std::vector<unsigned int> ind; // indices
};*/
