
#include "MotorRaven.hpp"
#include <memory>
#include "Nodo.hpp"
#include "ECamara.hpp"
#include "ELuz.hpp"
#include "EModelo.hpp"
#include "GestorRecursos.hpp"


MotorRaven::MotorRaven() {
    //auto gr = std::make_unique<GestorRecursos> ();
    gestorRecursos = new GestorRecursos ();
}

MotorRaven::~MotorRaven() {}

RShader *MotorRaven::crearShader(const char *path) {
    auto shader = gestorRecursos->getRShader(path);
    return shader;
}

RTextura *MotorRaven::crearTextura(const char *fichero) {
    auto textura = gestorRecursos->getRTextura(fichero);
    return textura;
}

Nodo *MotorRaven::crearNodo(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc){
    
    if(padre == nullptr){
        padre = raiz;
    }

    //auto nodo = std::make_unique<Nodo>(nullptr, padre);
    auto nodo = new Nodo(nullptr, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::crearCamara(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
bool pers, float izq, float der, float inf, float sup, float cerc, float lej){
    
    if(padre == nullptr){
        padre = raiz;
    }

    //auto eCam = std::make_unique<ECamara>(pers,izq, der, inf, sup, cerc, lej);
    auto eCam = new ECamara(pers,izq, der, inf, sup, cerc, lej);
    //auto nodo = std::make_unique<Nodo>(eCam.get(), padre);
    auto nodo = new Nodo(eCam, padre);

    // Borrar después
    projection = eCam->getMatrizProyeccion();
    //--------------
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    setCamaraActiva(registrarCamara(nodo));

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::crearLuzDireccional(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens, float aCte, float aLin, float aCuad){
    
    if(padre == nullptr){
        padre = raiz;
    }

    //auto eLuz = std::make_unique<ELuz>(intens, aCte, aLin, aCuad);
    auto eLuz = new ELuz(intens, aCte, aLin, aCuad);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    auto nodo = new Nodo(eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(nodo),true);

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::crearLuzPuntual(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens){
    
    if(padre == nullptr){
        padre = raiz;
    }

    //auto eLuz = std::make_unique<ELuz>(intens);
    auto eLuz = new ELuz(intens);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    auto nodo = new Nodo(eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(nodo),true);

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::crearLuzFocal(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens,float apert, float aAng, float aCte, float aLin, float aCuad){
    
    if(padre == nullptr){
        padre = raiz;
    }

    //auto eLuz = std::make_unique<ELuz>(intens, apert, aAng, aCte, aLin, aCuad);
    auto eLuz = new ELuz(intens, apert, aAng, aCte, aLin, aCuad);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    auto nodo = new Nodo(eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(nodo),true);

    //return nodo.get();
    return nodo;
}


Nodo *MotorRaven::crearModelo(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, RTextura *c, RTextura *h, RTextura *m, RTextura *n, RTextura *r){
    
    if(padre == nullptr){
        padre = raiz;
    }
    
    //auto eMod = std::make_unique<EModelo>(gestorRecursos->getRMalla(f, c, h, m, n, r));
    auto eMod = new EModelo(gestorRecursos->getRMalla(f, c, h, m, n, r));
    //auto nodo = std::make_unique<Nodo>(eMod.get(), padre);
    auto nodo = new Nodo(eMod, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //return nodo.get();
    return nodo;
}


unsigned int MotorRaven::registrarCamara(Nodo *nodoCamara){
   registroCamaras.push_back(nodoCamara);
   return registroCamaras.size()-1;
}

void MotorRaven::setCamaraActiva(unsigned int nCamara){
    camaraActiva=nCamara;
}

unsigned int MotorRaven::registrarLuz(Nodo *nodoLuz){
   registroLuces.push_back(nodoLuz);
   lucesActivas.push_back(true);
   return registroLuces.size()-1;
}
void MotorRaven::setLuzActiva(unsigned int nLuz,bool activa){
    lucesActivas[nLuz]=activa;
}



unsigned int MotorRaven::registrarViewport(unsigned int x, unsigned int y, unsigned int alto, unsigned int ancho){
    Viewport viewport;
    viewport.xx=x;
    viewport.yy=y;
    viewport.alt=alto;
    viewport.anch=ancho;

    registroViewports.push_back(viewport);

    return registroViewports.size()-1;
}

void MotorRaven::setViewportActivo(unsigned int nViewport){
    viewportActivo=nViewport;
}



void MotorRaven::dibujarEscena (unsigned int shader){
    auto matriz = glm::mat4x4(1.0f);
    for(unsigned int i=0; i<lucesActivas.size();i++){ //recorro el array de luces activas para saber cuales están activas
        if(lucesActivas[i]==true){
            //PASAR A GL ESTA MATRIZ DE LUZ
           // registroLuces[i]->getMatrizTransf(); 
           ///////////////////////////
        }
    }
    //PASAR A GL ESTA MATRIZ DE VISTA
    //glm::inverse(registroCamaras[camaraActiva]->getMatrizTransf());
    //////////////
    //PASAR A GL EL VIEWPORT ACTIVO
    //registrarViewport[viewportActivo]
    /////////////////////
    
    raiz->recorrer(matriz, shader);
}

// Borrar después
glm::mat4x4 MotorRaven::getProjection() {
    return projection;
}

