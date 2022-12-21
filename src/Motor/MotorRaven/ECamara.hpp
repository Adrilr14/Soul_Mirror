#pragma once

#include "Entidad.hpp"

//class RShader;

class ECamara : public Entidad {
public:
    ECamara (bool perspectiva ,float izq, float der, float inf, float sup, float cerc, float lej); 
    ~ECamara ();

    void setPerspectiva(float izq, float der, float inf, float sup, float cerc, float lej);

    void setParalela(float izq, float der, float inf, float sup, float cerc, float lej);

    glm::mat4x4 getMatrizProyeccion ();

    bool getPerspectiva ();

    void setIzquierda (float izq);
    float getIzquierda ();

    void setDerecha (float der);
    float getDerecha ();

    void setInferior (float inf);
    float getInferior ();

    void setSuperior (float sup);
    float getSuperior ();

    void setCercano (float cerc);
    float getCercano ();

    void setLejano (float lej);
    float getLejano ();

    // Asigna el target de la camara
    void setCameraTarget(glm::vec3 pos);
    void setCameraUp(glm::vec3 pos);

    glm::vec3 getCameraTarget();
    glm::vec3 getCameraUp();

    void dibujar(glm::mat4x4 mat, unsigned int shader) override;
    
private:
    glm::mat4x4 matrizProyeccion;
    bool esPerspectiva;
    float izquierda, derecha, inferior, superior;
    float cercano, lejano;

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
};
