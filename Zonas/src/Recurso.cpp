
#include "Recurso.hpp"

Recurso::Recurso (std::string c) : nombre(c) {}

Recurso::~Recurso () {
    //delete this;
}

std::string Recurso::getNombre () {
    return nombre;
}

void Recurso::setNombre (std::string c) {
    nombre = c;
}
