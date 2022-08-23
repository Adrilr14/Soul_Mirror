#pragma once

#include "Recurso.hpp"

class RTextura : public Recurso
{
public:
    RTextura(std::string fichero);
    ~RTextura();

    //unsigned int getId ();
    unsigned int getIdDiffuse ();
    unsigned int getIdHeight ();
    unsigned int getIdMetallic ();
    unsigned int getIdNormal ();
    unsigned int getIdRoughness ();

    //void setPath (const char *path);

    void cargarFichero (const char* path) override; // Textura
    std::string getPath() { return path; }; 
private:
    //unsigned int id;
    unsigned int idDiffuse, idHeight, idMetallic, idNormal, idRoughness;
    int widthText, heightText;
    std::string path;
};
