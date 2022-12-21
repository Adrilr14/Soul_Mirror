#pragma once

#include <iostream>
#include <vector>
//#include "Recurso.hpp"

//class Recurso;
class RMalla;
//class RMaterial;
class RTextura;
class RShader;

class GestorRecursos
{
public:
    GestorRecursos();
    ~GestorRecursos();

    RMalla *getRMalla (std::string name, RTextura *t);
    //RMaterial *getRMaterial (std::string name);
    RTextura *getRTextura (std::string name);
    RShader *getRShader (std::string name);

private:
    //std::vector<Recurso*> recursos;
    std::vector<RMalla*> rmallas;
    //std::vector<RMaterial*> rmateriales;
    std::vector<RTextura*> rtexturas;
    std::vector<RShader*> rshaders;
};
