#pragma once

#include "Entidad.hpp"
#include <iostream>
//#include <tuple>

//class RShader;

class ELuz : public Entidad {

public:

    enum TLuz {
        direccional,
        puntual,
        focal
    };

    //ELuz (glm::vec4 intens, TLuz t, std::tuple<float, float, float> atenuacion);
    ELuz (glm::vec4 intens, float aCte, float aLin, float aCuad); // Constructor luz direccional
    ELuz (glm::vec4 intens); // Constructor luz puntual
    ELuz (glm::vec4 intens, float apert, float aAng, float aCte, float aLin, float aCuad); // Constructor luz focal
    ~ELuz ();

    void setIntensidad(glm::vec4 intens);
    glm::vec4 getIntensidad();

    void setTipoLuz (TLuz t);
    int getTipoLuz ();

    void setApertura(float ap);
    float getapertura();

    void setAtenAngular(float atA);
    float getAtenAngular();

    void setAtenCte(float atCte);
    float getAtenCte();

    void setAtenLineal(float atLin);
    float getAtenLinea();

    void setAtenCuadrat(float atCua);
    float getAtenCuadrat();
    
    void dibujar(glm::mat4x4 mat, unsigned int shader) override;
    

private:
    glm::vec4 intensidad; // r g b alpha (color de la luz y potencia)
    TLuz tipoLuz;
    float apertura, atenAngular;
    float atenCte, atenLineal, atenCuadrat;
};
