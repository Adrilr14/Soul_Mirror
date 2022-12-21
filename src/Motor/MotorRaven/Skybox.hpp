#pragma once

#include "Entidad.hpp"

class Skybox : public Entidad
{
public:
    Skybox();
    Skybox(const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back);
    ~Skybox();

    void dibujar(glm::mat4x4 mat, unsigned int shader);
    void DrawDepthMap(unsigned int shaderID);

private:
    unsigned int skyboxID, skyboxVAO, skyboxVBO;
    float skyboxVertices[108] = {
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
    };
};
