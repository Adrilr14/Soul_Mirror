#pragma once

#include "vec3.hpp"
#include "vec4.hpp" // glm::vec4
#include "mat4x4.hpp" // glm::mat4
#include "vector"
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

class Nodo;
class RTextura;
class RShader;
class GestorRecursos;
struct Viewport{
    unsigned int xx, yy, alt, anch;
};
class MotorRaven
{
public:

    MotorRaven();
    ~MotorRaven();

    RShader *crearShader(const char* path);
    RTextura *crearTextura(const char* fichero);

    Nodo *crearNodo(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc);
    Nodo *crearCamara(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,bool pers, float izq, float der, float inf, float sup, float cerc, float lej);
    Nodo *crearLuzDireccional(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,glm::vec4 intens, float aCte, float aLin, float aCuad);
    Nodo *crearLuzPuntual(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, glm::vec4 intens);
    Nodo *crearLuzFocal(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, glm::vec4 intens, float apert, float aAng, float aCte, float aLin, float aCuad);
    Nodo *crearModelo(Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, RTextura *c, RTextura *h, RTextura *m, RTextura *n, RTextura *r);

    void dibujarEscena(unsigned int shader);

    unsigned int registrarCamara (Nodo *nodoCamara);
    void setCamaraActiva(unsigned int nCamara);
    unsigned int registrarLuz(Nodo *nodoLuz);
    void setLuzActiva(unsigned int nLuz, bool activa);
    unsigned int registrarViewport(unsigned int x, unsigned int y, unsigned int alto, unsigned int Ancho);
    void setViewportActivo(unsigned int nViewport);

    // Borrar después
    glm::mat4x4 getProjection ();

private:
    Nodo *raiz;
    GestorRecursos *gestorRecursos;

    std::vector<Nodo*> registroCamaras;
    std::vector<Nodo*> registroLuces;
    std::vector<Viewport> registroViewports;

    unsigned int camaraActiva, viewportActivo;
    std::vector<bool> lucesActivas;

    // Borrar después
    glm::mat4x4 projection;

};

