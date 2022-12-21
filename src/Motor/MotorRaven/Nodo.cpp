
#include "Nodo.hpp"
#include <iostream>

Nodo::Nodo (std::size_t n, Entidad *ent, Nodo *p) : id(n), matrizTransf(glm::mat4x4(1.0f)), entidad(ent), padre(p), escalado(glm::vec3(1.0f)), actualizarMatriz(true), renderizar(true) {
    if(padre)
        padre->añadirHijo(this);
}
Nodo::~Nodo () {
    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        if(hijos[i])
        {
            hijos[i]->clear();
        }
    }
    //std::cout << "Me borro" << std::endl;
}

void Nodo::añadirHijo (Nodo *h) {
    hijos.push_back(h);
}

void Nodo::borrarHijo (Nodo *h) {

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        if(hijos[i] == h){
            //hijos[i]->~Nodo();
            hijos.erase(hijos.begin() + i);
        }
    }
}

void Nodo::clear () {
    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        hijos[i]->~Nodo();
    }
    hijos.clear();
}

std::size_t Nodo::getID () {
    return id;
}

Nodo *Nodo::getNodoFromID (std::size_t n) {
    Nodo *nodo = nullptr;
    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        if(hijos[i]->getID() == n)
            nodo = hijos[i];
    }
    return nodo;
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

Nodo *Nodo::getHijo (Nodo *h) {
    Nodo *nodo = nullptr;
    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        if(hijos[i] == h)
            nodo = hijos[i];
    }
    return nodo;
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

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        hijos[i]->setActualizarMatriz(true);
    }
}

glm::vec3 Nodo::getTraslacion () {
    return traslacion;
}

void Nodo::setRotacion (glm::vec3 rot) {
    rotacion = rot;
    actualizarMatriz = true;

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        hijos[i]->setActualizarMatriz(true);
    }
}

glm::vec3 Nodo::getRotacion () {
    return rotacion;
}

void Nodo::setEscalado (glm::vec3 esc) {
    escalado = esc;
    actualizarMatriz = true;

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        hijos[i]->setActualizarMatriz(true);
    }
}

glm::vec3 Nodo::getEscalado () {
    return escalado;
}

glm::vec3 Nodo::getTraslacionGlobal() const{
    glm::vec3 tras = traslacion;
    auto fatherNode = padre;
    while(fatherNode){
        tras += fatherNode->getTraslacion();
        fatherNode = fatherNode->getPadre();
    }
    return tras;
}

glm::vec3 Nodo::getRotacionGlobal() const{
    glm::vec3 rot = rotacion;
    auto fatherNode = padre;
    while(fatherNode){
        rot += fatherNode->getRotacion();
        fatherNode = fatherNode->getPadre();
    }
    return rot;
}

glm::vec3 Nodo::getEscaladoGlobal() const{
    glm::vec3 esc = escalado;
    auto fatherNode = padre;
    while(fatherNode){
        esc += fatherNode->getEscalado();
        fatherNode = fatherNode->getPadre();
    }
    return esc;
}

void Nodo::trasladar (glm::vec3 tras) {
    traslacion += tras;
    actualizarMatriz = true;

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        hijos[i]->setActualizarMatriz(true);
    }
}

void Nodo::rotar (glm::vec3 rot) {
    rotacion += rot;
    actualizarMatriz = true;

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        hijos[i]->setActualizarMatriz(true);
    }
}

void Nodo::escalar (glm::vec3 esc) {
    escalado += esc;
    actualizarMatriz = true;

    for(unsigned int i  = 0; i < hijos.size(); i++)
    {
        hijos[i]->setActualizarMatriz(true);
        //std::vector<Nodo*> nietos = hijos[i]->getHijos();
    }
}

void Nodo::setActualizarMatriz (bool act) {
    actualizarMatriz = act;
}

bool Nodo::getVisibilidad () {
    return renderizar;
}

void Nodo::setVisibilidad (bool visibilidad) {
    renderizar = visibilidad;
}

void Nodo::recorrer (glm::mat4x4 matrizAcum, unsigned int shader, bool actualizar) {
    //std::cout << "adentro" << std::endl;
    bool aux = false; // Booleano auxiliar para actualizar las matrices de transformación recursivamente si es true
    if (actualizarMatriz || actualizar)
    {
        //std::cout << "adentro" << std::endl;
        //matrizTransf = matrizAcum * glm::translate(glm::mat4x4(), traslacion) * glm::rotate(glm::mat4x4(), rotacion) * glm::scale(glm::mat4x4(), escalado);
        matrizTransf = matrizAcum * glm::translate(matrizAcum, traslacion)
			* glm::rotate(matrizAcum, (float)glm::radians(rotacion.x), glm::vec3(1.0f, 0, 0))
			* glm::rotate(matrizAcum, (float)glm::radians(rotacion.y), glm::vec3(0, 1.0f, 0))
			* glm::rotate(matrizAcum, (float)glm::radians(rotacion.z), glm::vec3(0, 0, 1.0f))
			* glm::scale(matrizAcum, escalado);
        // No se si son los parámetros que hay que pasarle a rotate
        actualizarMatriz = false;
        // Ponemos a true aux para así actualizar las matrices de los hijos, nietos...
        aux = true;
        //std::cout << "actualizo matriz" << std::endl;
    }
    
    // Variable para comprobar si se renderiza (visibilidad) el padre de un nodo si tiene padre (en caso de no tener padre estará por defecto a true)
    bool renderizarPadre = true;
    if(padre) {renderizarPadre = false;}

    // Solo dibujamos si tiene una entidad, si se renderiza (visible) y si se renderiza su padre
    if(entidad && renderizar == true)
    {
        //std::cout << "dibujo" << std::endl;
        //std::cout << entidad << std::endl;
        entidad->dibujar(matrizTransf, shader);
    }

    for (unsigned int i = 0; i < hijos.size(); i++)
    {
        hijos[i]->recorrer(matrizTransf, shader, aux);
        //hijos[i]->recorrer(glm::mat4x4(1.0f));
    }
    
}

