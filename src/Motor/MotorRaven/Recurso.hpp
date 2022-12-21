#pragma once

#include <iostream>

class Recurso
{
public:
    Recurso (std::string c);
    ~Recurso ();

    std::string getNombre ();
    void setNombre (std::string c);

    virtual void cargarFichero (const char* fichero) = 0;
     
private:
    std::string nombre;
};
