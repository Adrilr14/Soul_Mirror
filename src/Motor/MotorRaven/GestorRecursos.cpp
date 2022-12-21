
#include "GestorRecursos.hpp"
//#include "Recurso.hpp"
#include "RMalla.hpp"
//#include "RMaterial.hpp"
#include "RTextura.hpp"
#include "RShader.hpp"
#include <memory>

GestorRecursos::GestorRecursos () {}

GestorRecursos::~GestorRecursos () {}

RMalla *GestorRecursos::getRMalla (std::string name, RTextura *t)
{
    //std::unique_ptr<RMalla> miRecurso;
    RMalla *miRecurso;
    bool entra = false;
    for (unsigned int i = 0; i < rmallas.size(); i++)
    {
        if(name.compare(rmallas[i]->getNombre()) == 0)
        {
            //miRecurso.reset(rmallas[i]);
            miRecurso = rmallas[i];
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        //miRecurso = std::make_unique<RMalla>(name, c, h, m, n, r);
        miRecurso = new RMalla(name, t);
        miRecurso->cargarFichero(name.c_str());
        //rmallas.push_back(miRecurso.get());
        rmallas.push_back(miRecurso);
        
    }
    //return miRecurso.get();
    return miRecurso;
}

/*RMaterial *GestorRecursos::getRMaterial (std::string name) 
{
    //std::unique_ptr<RMaterial> miRecurso;
    RMaterial *miRecurso;
    bool entra = false;
    for (unsigned int i = 0; i < rmateriales.size(); i++)
    {
        if(name.compare(rmateriales[i]->getNombre()) == 0)
        {
            //miRecurso.reset(rmateriales[i]);std::make_unique<
            miRecurso = rmateriales[i];
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        //miRecurso = std::make_unique<RMaterial>(name);
        miRecurso = new RMaterial(name);
        miRecurso->cargarFichero(name.c_str());
        //rmateriales.push_back(miRecurso.get());
        rmateriales.push_back(miRecurso);
    }
    //return miRecurso.get();
    return miRecurso;
}*/

RTextura *GestorRecursos::getRTextura (std::string name) 
{
    //std::unique_ptr<RTextura> miRecurso;
    RTextura *miRecurso;
    //std::cout << name << std::endl;
    bool entra = false;
    for (unsigned int i = 0; i < rtexturas.size(); i++)
    {
        //std::cout << name.compare(rtexturas[i]->getNombre()) << std::endl;
        if(name.compare(rtexturas[i]->getNombre()) == 0)
        {
            //miRecurso.reset(rtexturas[i]);
            miRecurso = rtexturas[i];
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        //miRecurso = std::make_unique<RTextura>(name);
        miRecurso = new RTextura(name);
        miRecurso->cargarFichero(name.c_str());
        //rtexturas.push_back(miRecurso.get());
        rtexturas.push_back(miRecurso);
    }
    //return miRecurso.get();
    return miRecurso;
}

RShader *GestorRecursos::getRShader (std::string name) 
{
    //std::unique_ptr<RShader> miRecurso;
    RShader *miRecurso;
    bool entra = false;
    for (unsigned int i = 0; i < rshaders.size(); i++)
    {
        if(name.compare(rshaders[i]->getNombre()) == 0)
        {
            //miRecurso.reset(rshaders[i]);
            miRecurso = rshaders[i];
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        //miRecurso = std::make_unique<RShader>(name);
        miRecurso = new RShader(name);
        miRecurso->cargarFichero(name.c_str());
        //rshaders.push_back(miRecurso.get());
        rshaders.push_back(miRecurso);
    }
    //return miRecurso.get();
    return miRecurso;
}
