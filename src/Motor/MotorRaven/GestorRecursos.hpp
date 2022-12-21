#pragma once

#include <iostream>
#include <vector>
#include <memory>

//#include "Recurso.hpp"

//class Recurso;
class RMalla;
class RMaterial;
class RTextura;
class RShader;
class RImagen;


class GestorRecursos
{
public:
    GestorRecursos();
    ~GestorRecursos();

    RMalla* getRMalla (std::string name, RTextura *t);
    RMaterial *getRMaterial (std::string name);
    RTextura *getRTextura (std::string name);
    RShader *getRShader (std::string name, bool geometry);
    RImagen *getRImagen (std::string name);

private:
    //std::vector<Recurso*> recursos;
    std::vector<std::unique_ptr<RMalla>> rmallas;

    std::vector<std::unique_ptr<RMaterial>> rmateriales;
    
    std::vector<std::unique_ptr<RTextura>> rtexturas;

    std::vector<std::unique_ptr<RShader>> rshaders;

    std::vector<std::unique_ptr<RImagen>> rimagenes;

};
