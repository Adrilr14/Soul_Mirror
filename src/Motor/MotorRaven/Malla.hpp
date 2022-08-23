#pragma once

#include <vector>

// GLM library
#include "vec2.hpp" // glm::vec2
#include "vec3.hpp" // glm::vec3

class RTextura;
//class RShader;

struct Vertex {
    // position
    glm::vec3 position;
    // normal
    glm::vec3 normal;
    // texCoords
    glm::vec2 texCoords;
};

class Malla
{
public:
    
    Malla(std::vector<Vertex> vertices, std::vector<unsigned int> ind, RTextura *t);
    ~Malla();

    /*std::string getNombre ();
    void setNombre (std::string c);*/

    void dibujar(unsigned int shader);

    void setTextura (RTextura *t) {textura = t;}

     
private:
    std::vector<Vertex> vertex;
    std::vector<unsigned int> indices;
    RTextura *textura;

    unsigned int VAO, VBO, EBO;
    void setupMalla();
};
