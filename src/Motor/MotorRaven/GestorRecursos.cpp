
#include "GestorRecursos.hpp"
//#include "Recurso.hpp"
#include "RMalla.hpp"
#include "RMaterial.hpp"
#include "RTextura.hpp"
#include "RShader.hpp"
#include "RImagen.hpp"

GestorRecursos::GestorRecursos () {}

GestorRecursos::~GestorRecursos () {}

RMalla* GestorRecursos::getRMalla (std::string name, RTextura *t)
{
    std::unique_ptr<RMalla> miRecurso;
    auto aux { miRecurso.get() };
    bool entra = false;

    for (unsigned int i = 0; i < rmallas.size(); i++)
    {
        if(name.compare(rmallas[i]->getNombre()) == 0)
        {
            //miRecurso.reset(rmallas[i]);
            aux = rmallas[i].get();
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        miRecurso = std::make_unique<RMalla>(name, t);
    
        miRecurso->cargarFichero(name.c_str());

        aux = miRecurso.get();
        
        rmallas.push_back(std::move(miRecurso));
    }
    
    return aux;
    
}

RMaterial *GestorRecursos::getRMaterial (std::string name) 
{
    std::unique_ptr<RMaterial> miRecurso;
    auto aux { miRecurso.get() };
    bool entra = false;

    for (unsigned int i = 0; i < rmateriales.size(); i++)
    {
        //std::cout << name.compare(rmateriales[i]->getNombre()) << std::endl;
        if(name.compare(rmateriales[i]->getNombre()) == 0)
        {
            //miRecurso.reset(rmateriales[i]);
            aux = rmateriales[i].get();
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        miRecurso = std::make_unique<RMaterial>(name);
    
        miRecurso->cargarFichero(name.c_str());

        aux = miRecurso.get();
        
        rmateriales.push_back(std::move(miRecurso));
    }
    
    return aux;
}

RTextura *GestorRecursos::getRTextura (std::string name) 
{
    std::unique_ptr<RTextura> miRecurso;
    auto aux { miRecurso.get() };
    bool entra = false;

    for (unsigned int i = 0; i < rtexturas.size(); i++)
    {
        //std::cout << name.compare(rtexturas[i]->getNombre()) << std::endl;
        if(name.compare(rtexturas[i]->getNombre()) == 0)
        {
            //miRecurso.reset(rtexturas[i]);
            aux = rtexturas[i].get();
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        miRecurso = std::make_unique<RTextura>(name);
    
        miRecurso->cargarFichero(name.c_str());

        aux = miRecurso.get();
        
        rtexturas.push_back(std::move(miRecurso));
    }
    
    return aux;
}

RShader *GestorRecursos::getRShader (std::string name, bool geometry) 
{
    std::unique_ptr<RShader> miRecurso;
    auto aux { miRecurso.get() };
    bool entra = false;

    for (unsigned int i = 0; i < rshaders.size(); i++)
    {
        if(name.compare(rshaders[i]->getNombre()) == 0)
        {
            aux = rshaders[i].get();
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        miRecurso = std::make_unique<RShader>(name, geometry);
    
        miRecurso->cargarFichero(name.c_str());
        
        aux = miRecurso.get();
        
        rshaders.push_back(std::move(miRecurso));
    }
   
    return aux;
}

RImagen *GestorRecursos::getRImagen (std::string name) 
{
    std::unique_ptr<RImagen> miRecurso;
    auto aux { miRecurso.get() };
    bool entra = false;

    for (unsigned int i = 0; i < rimagenes.size(); i++)
    {
        if(name.compare(rimagenes[i]->getNombre()) == 0)
        {
            aux = rimagenes[i].get();
            entra = true;
            break;
        }
    }

    if (!entra)
    {
        miRecurso = std::make_unique<RImagen>(name);
    
        miRecurso->cargarFichero(name.c_str());
        
        aux = miRecurso.get();
        
        rimagenes.push_back(std::move(miRecurso));
    }

    return aux;
}
