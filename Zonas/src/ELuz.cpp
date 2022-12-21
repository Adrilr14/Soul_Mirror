
#include "ELuz.hpp"
//#include "glm.hpp"

ELuz::ELuz (glm::vec4 intens, float aCte, float aLin, float aCuad)
: intensidad(intens), tipoLuz(direccional), atenCte(aCte), atenLineal(aLin), atenCuadrat(aCuad) {} // Constructor luz direccional

ELuz::ELuz (glm::vec4 intens) : intensidad(intens), tipoLuz(puntual) {} // Constructor luz puntual

ELuz::ELuz (glm::vec4 intens, float apert, float aAng, float aCte, float aLin, float aCuad)
: intensidad(intens), tipoLuz(focal), apertura(apert), atenAngular(aAng), atenCte(aCte), atenLineal(aLin), atenCuadrat(aCuad) {} // Constructor luz focal

ELuz::~ELuz () {}

void ELuz::setIntensidad (glm::vec4 intens) {
        intensidad = intens;
}

glm::vec4 ELuz::getIntensidad () {
        return intensidad;
}

void ELuz::setTipoLuz (TLuz t) {
        tipoLuz = t;
}

std::string ELuz::getTipoLuz () {
        std::string luz[3] = {"direccional", "puntual", "focal"};
        return luz[tipoLuz];
}

void ELuz::setApertura(float ap){
        apertura = ap;
}
float ELuz::getapertura(){
        return apertura;
}

void ELuz::setAtenAngular(float atA){
        atenAngular = atA;
}

float ELuz::getAtenAngular(){
        return atenAngular;
}

void ELuz::setAtenCte(float atCte){
        atenCte = atCte;
}
float ELuz::getAtenCte(){
        return atenCte;
}

void ELuz::setAtenLineal(float atLin){
        atenLineal = atLin;
}
float ELuz::getAtenLinea(){
        return atenLineal;
}

void ELuz::setAtenCuadrat(float atCua){
        atenCuadrat = atCua;
}

float ELuz::getAtenCuadrat(){
        return atenCuadrat;
}


void ELuz::dibujar (glm::mat4x4 mat, unsigned int shader) {}
