#pragma once

#include "Recurso.hpp"

class RTextura : public Recurso
{
public:
    RTextura(std::string fichero);
    ~RTextura();

    unsigned int getId ();

    void setPath (const char *fichero);

    void cargarFichero (const char* fichero) override; // Textura

private:
    unsigned int id;
    int widthText, heightText;
};
