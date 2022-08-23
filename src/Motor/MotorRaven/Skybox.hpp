#pragma once

#include "Entidad.hpp"
#include "RMalla.hpp"
#include "Malla.hpp"

class Skybox : public Entidad
{
public:
    Skybox();
    Skybox(RMalla *skybox_, const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back);
    ~Skybox();

    void dibujar(glm::mat4x4 mat, unsigned int shader);
    void DrawDepthMap(unsigned int shaderID);

private:
    RMalla *skybox {nullptr};
    unsigned int skyboxID {0}, skyboxVAO {0}, skyboxVBO {0}, skyboxEBO {0};
    std::vector<Vertex> vertex;
    std::vector<unsigned int> ind;

    /*float skyboxVertices[108] = {
        // positions          
        -200.0f,  200.0f, -200.0f,
        -200.0f, -200.0f, -200.0f,
        200.0f, -200.0f, -200.0f,
        200.0f, -200.0f, -200.0f,
        200.0f,  200.0f, -200.0f,
        -200.0f,  200.0f, -200.0f,

        -200.0f, -200.0f,  200.0f,
        -200.0f, -200.0f, -200.0f,
        -200.0f,  200.0f, -200.0f,
        -200.0f,  200.0f, -200.0f,
        -200.0f,  200.0f,  200.0f,
        -200.0f, -200.0f,  200.0f,

        200.0f, -200.0f, -200.0f,
        200.0f, -200.0f,  200.0f,
        200.0f,  200.0f,  200.0f,
        200.0f,  200.0f,  200.0f,
        200.0f,  200.0f, -200.0f,
        200.0f, -200.0f, -200.0f,

        -200.0f, -200.0f,  200.0f,
        -200.0f,  200.0f,  200.0f,
        200.0f,  200.0f,  200.0f,
        200.0f,  200.0f,  200.0f,
        200.0f, -200.0f,  200.0f,
        -200.0f, -200.0f,  200.0f,

        -200.0f,  200.0f, -200.0f,
        200.0f,  200.0f, -200.0f,
        200.0f,  200.0f,  200.0f,
        200.0f,  200.0f,  200.0f,
        -200.0f,  200.0f,  200.0f,
        -200.0f,  200.0f, -200.0f,

        -200.0f, -200.0f, -200.0f,
        -200.0f, -200.0f,  200.0f,
        200.0f, -200.0f, -200.0f,
        200.0f, -200.0f, -200.0f,
        -200.0f, -200.0f,  200.0f,
        200.0f, -200.0f,  200.0f
    };*/

};
