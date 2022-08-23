#pragma once

#include "Recurso.hpp"

class RFuente : public Recurso
{
public:
    RFuente(std::string fichero);
    ~RFuente();

    unsigned int getId ();

    //void setPath (const char *path);

    int getWidth () {return widthImg;}
    int getHeight () {return heightImg;}

    void cargarFichero (const char* path) override; // Textura

private:
    unsigned int id;
    int widthImg, heightImg;
};
