#pragma once

#include "Recurso.hpp"

class RImagen : public Recurso
{
public:
    RImagen(std::string fichero);
    ~RImagen();

    unsigned int getId ();

    //void setPath (const char *path);

    int getWidth () {return widthImg;}
    int getHeight () {return heightImg;}

    void cargarFichero (const char* path) override; // Textura

private:
    unsigned int id;
    int widthImg, heightImg;
};
