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
    
    void dibujar(glm::mat4x4 mat, unsigned int shader) override;
    
private:
    glm::mat4x4 matrizProyeccion;
    bool esPerspectiva;
    float izquierda, derecha, inferior, superior;
    float cercano, lejano;
};
