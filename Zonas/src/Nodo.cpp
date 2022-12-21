
#include "Nodo.hpp"
#include <iostream>

Nodo::Nodo (Entidad *ent, Nodo *p) : matrizTransf (glm::mat4x4(1.0f)), entidad(ent), padre(p), escalado(glm::vec3(1.0f)), actualizarMatriz(true) {
    if(padre)
        padre->añadirHijo(this);
}

Nodo::~Nodo () {
    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        if(hijos[i])
        {
            hijos[i]->setPadre(padre);
            hijos[i]->setMatrizTransf(glm::mat4x4(1.0f)); // inicializamos la matriz de transformación para que no se acumule
            hijos[i]->setActualizarMatriz(true); // Como cambian de padre habrá que actualizar su matriz
            padre->añadirHijo(hijos[i]);
        }
    }
    if(padre)
        padre->borrarHijo(this);
    //delete this;
    std::cout << "Me borro" << std::endl;

}

void Nodo::añadirHijo (Nodo *h) {
    hijos.push_back(h);
}

void Nodo::borrarHijo (Nodo *h) {

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        if(hijos[i] == h){
            hijos.erase(hijos.begin() + i);
        }
    }
}

void Nodo::setMatrizTransf (glm::mat4x4 mat) {
    matrizTransf = mat;
}

glm::mat4x4 Nodo::getMatrizTransf () {
    return matrizTransf;
}

void Nodo::setEntidad (Entidad *ent) {
    entidad = ent;
}

Entidad *Nodo::getEntidad () {
    return entidad;
}

std::vector<Nodo*> Nodo::getHijos () {
    return hijos;
}

void Nodo::setPadre (Nodo *p) {
    padre = p;
}

Nodo *Nodo::getPadre () {
    return padre;
}

void Nodo::setTraslacion (glm::vec3 tras) {
    traslacion = tras;
    actualizarMatriz = true;
}

glm::vec3 Nodo::getTraslacion () {
    return traslacion;
}

void Nodo::setRotacion (glm::vec3 rot) {
    rotacion = rot;
    actualizarMatriz = true;
}

glm::vec3 Nodo::getRotacion () {
    return rotacion;
}

void Nodo::setEscalado (glm::vec3 esc) {
    escalado = esc;
    actualizarMatriz = true;
}

glm::vec3 Nodo::getEscalado () {
    return escalado;
}

void Nodo::trasladar (glm::vec3 tras) {
    traslacion += tras;
    actualizarMatriz = true;
}

void Nodo::rotar (glm::vec3 rot) {
    rotacion += rot;
    actualizarMatriz = true;
}

void Nodo::escalar (glm::vec3 esc) {
    escalado += esc;
    actualizarMatriz = true;
}

void Nodo::recorrer (glm::mat4x4 matrizAcum, unsigned int shader) {
    
    if (actualizarMatriz)
    {
        //matrizTransf = matrizAcum * glm::translate(glm::mat4x4(), traslacion) * glm::rotate(glm::mat4x4(), rotacion) * glm::scale(glm::mat4x4(), escalado);
        matrizTransf = matrizAcum * glm::translate(matrizTransf, traslacion)
			* glm::rotate(matrizTransf, (float)glm::radians(rotacion.x), glm::vec3(1.0f, 0, 0))
			* glm::rotate(matrizTransf, (float)glm::radians(rotacion.y), glm::vec3(0, 1.0f, 0))
			* glm::rotate(matrizTransf, (float)glm::radians(rotacion.z), glm::vec3(0, 0, 1.0f))
			* glm::scale(matrizTransf, escalado);
        // No se si son los parámetros que hay que pasarle a rotate
        actualizarMatriz = false;
    }
    
    if(entidad)
        entidad->dibujar(matrizTransf, shader);

    for (unsigned int i = 0; i < hijos.size(); i++)
    {
        hijos[i]->recorrer(matrizTransf, shader);
        //hijos[i]->recorrer(glm::mat4x4(1.0f));
    }
    
}

void Nodo::setActualizarMatriz (bool act) {
    actualizarMatriz = true;
}
