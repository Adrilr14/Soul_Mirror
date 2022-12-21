#pragma once

#include "vector"
#include <iostream>

// GLM library
#include "vec3.hpp"
#include "vec4.hpp" // glm::vec4
#include "mat4x4.hpp" // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

#include "Skybox.hpp"

class Nodo;
class RTextura;
class RShader;
class GestorRecursos;
class GLFWwindow;

struct Viewport{
    unsigned int xx, yy, alt, anch;
};

class MotorRaven
{
public:

    MotorRaven(const unsigned int w, const unsigned int h, const char *name, bool fullScreen);
    ~MotorRaven();

    void createWindow (const unsigned int w, const unsigned int h, const char *name, bool fullScreen);
    GLFWwindow *getWindow();
    bool processInput(int key);
    void setTitle(std::string t);

    void beginScene();
    void endScene();
    double getTime();
    void updateFrames();
    int getFPS();

    void addShader();
    void useShader(RShader *sh);
    void addSkybox(const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back);
    Nodo *addBillboard(Nodo *padre, unsigned int id, const char* file, bool vertically, float width_, float height_);

    RShader *crearShader(const char* path, bool geometry);
    RTextura *crearTextura(const char *fichero);
    Nodo *crearNodo(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc);
    Nodo *getSceneManager();
    Nodo *crearCamara(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,bool pers, float izq, float der, float inf, float sup, float cerc, float lej);
    Nodo *crearLuzDireccional(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,glm::vec4 intens, float aCte, float aLin, float aCuad);
    Nodo *crearLuzPuntual(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, glm::vec4 intens);
    Nodo *crearLuzFocal(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, glm::vec4 intens, float apert, float aAng, float aCte, float aLin, float aCuad);
    Nodo *crearModelo(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, RTextura *t);

    void borrarNodo(Nodo *nodo);

    //void dibujarCubo(unsigned int sh);
    void drawSkybox();
    void drawBillboards();
    void dibujarEscena();

    unsigned int registrarCamara (Nodo *nodoCamara);
    void setCamaraActiva(unsigned int nCamara);
    void updateCamaraTarget(glm::vec3 pos);
    unsigned int registrarLuz(Nodo *nodoLuz);
    void setLuzActiva(unsigned int nLuz, bool activa);
    void updateViewport();
    //unsigned int registrarViewport(unsigned int x, unsigned int y, unsigned int ancho, unsigned int alta);
    //void setViewportActivo(unsigned int nViewport);

private:

    int width, height;
    Nodo *smgr {nullptr}; // Manager de la escena
    Nodo *bmgr {nullptr}; // Manager de los billboards
    GestorRecursos *gestorRecursos;
    GLFWwindow* window;

    //std::vector<RShader*> shaders;
    //unsigned int shaderActivo;

    std::vector<Nodo*> registroCamaras;
    std::vector<Nodo*> registroLuces;
    //std::vector<Viewport> registroViewports;
    Viewport viewportActivo;

    //unsigned int camaraActiva, viewportActivo;
    unsigned int camaraActiva;
    std::vector<bool> lucesActivas;

    // Control del tiempo
    // ------------------
    double then = getTime();
    double now = getTime();
    int lastFPS = 0;
    int fps = 0;

    //Skybox
    Skybox *skybox = new Skybox();
    
    //Shaders
    //std::vector<unsigned int> shaders;
    unsigned int shaderActivo = 0;
    unsigned int shaderSkybox = 0;
    unsigned int shaderBillboard = 0;

};

