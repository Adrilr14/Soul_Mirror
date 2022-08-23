#pragma once

#include <vector>
#include <memory>
#include <iostream>

// GLM library
#include "vec3.hpp"
#include "vec4.hpp" // glm::vec4
#include "mat4x4.hpp" // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

class Nodo;
class RTextura;
class RShader;
class GestorRecursos;
class GLFWwindow;
class Animacion;
class Entidad;

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
    bool processClick(int key);
    void setTitle(std::string t);

    void beginScene();
    void endScene();
    double getTime();
    void updateFrames();
    int getFPS();

    void addShader();
    void useShader(RShader *sh);
    void addSkybox(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back);
    Nodo *addBillboard(unsigned int id, Nodo *padre, int x, int y, const char* file, bool vertically);
    Nodo *addTexto(unsigned int id, Nodo *padre, const char* texto, glm::vec4 color, int x, int y, int size, const char* file);

    RShader *crearShader(const char* path, bool geometry);
    RTextura *crearTextura(const char *fichero);
    std::string getTextura(Nodo *n);
    Nodo *crearNodo(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc);
    Nodo *getSceneManager();
    Nodo *crearCamara(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,bool pers, float izq, float der, float inf, float sup, float cerc, float lej);
    Nodo *crearLuzDireccional(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,glm::vec4 intens, float aCte, float aLin, float aCuad);
    Nodo *crearLuzPuntual(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, glm::vec4 intens);
    Nodo *crearLuzFocal(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, glm::vec4 intens, float apert, float aAng, float aCte, float aLin, float aCuad);
    Nodo *crearModelo(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, RTextura *t);
    Nodo *crearModeloAnimado(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, int nAnimacion);

    void borrarNodo(Nodo *nodo);

    //void dibujarCubo(unsigned int sh);
    void drawSkybox();
    void drawBillboards();
    void drawTextos();
    void dibujarEscena();

    // Funciones Cámaras
    unsigned int registrarCamara (Nodo *nodoCamara);
    void setCamaraActiva(unsigned int nCamara);
    void updateCamaraTarget(glm::vec3 pos);

    // Funciones Luces
    unsigned int registrarLuz(std::unique_ptr<Nodo> nodoLuz);
    void setLuzActiva(unsigned int nLuz, bool activa);

    // Funciones Viewport
    void updateViewport();
    //unsigned int registrarViewport(unsigned int x, unsigned int y, unsigned int ancho, unsigned int alta);
    //void setViewportActivo(unsigned int nViewport);

    // Funciones Billboards
    unsigned int registrarBillboard(std::unique_ptr<Nodo> nodoBillboard);
    void setBillboardActivo(int nBillboard, bool activo);
    void setBillboardPos(int nBillboard, int x, int y);
    int getBillboardPosX(int nBillboard);
    int getBillboardPosY(int nBillboard);

    // Funciones Textos
    unsigned int registrarTexto(std::unique_ptr<Nodo> nodoTexto);
    void setTextoActivo(int nTexto, bool activo);
    void setTextoPos(int nTexto, int x, int y);
    int getTextoPosX(int nTexto);
    int getTextoPosY(int nTexto);


    
    // Funciones Animaciones
    int addAnimacion(const char* f, RTextura *t, int fps, int nFrames);
    Entidad *getAnimacion(int nAnimacion);

    // Funciones Skybox
    Nodo *getSkybox();

    void cambiarTextura(Nodo *n, const char *f);
    bool animationIsEnd(Nodo *n);
    void setAnimationEnd(Nodo *n, bool end);
    void setAnimationNumMalla(Nodo *n, int nMalla);

    void drawLoading();
    void desactivateLoading();
    int getFrameLoading();  

private:

    int width, height;
    Nodo *smgr {nullptr}; // Manager de la escena
    
    //Nodo *bmgr {nullptr}; // Manager de los billboards
    std::unique_ptr<GestorRecursos> gestorRecursos;
    //GestorRecursos *gestorRecursos;
    GLFWwindow* window;

    //std::vector<RShader*> shaders;
    //unsigned int shaderActivo;

    // Cámaras
    std::vector<Nodo*> registroCamaras;
    unsigned int camaraActiva;

    // Luces
    //std::vector<Nodo*> registroLuces;
    std::vector<std::unique_ptr<Nodo>> registroLuces;
    std::vector<bool> lucesActivas;

    // Viewport
    //std::vector<Viewport> registroViewports;
    Viewport viewportActivo;

    // Billboards
    //std::vector<Nodo*> registroBillboards;
    std::vector<std::unique_ptr<Nodo>> registroBillboards;
    std::vector<bool> billboardsActivos;

    // Textos
    //std::vector<Nodo*> registroTextos;
    std::vector<std::unique_ptr<Nodo>> registroTextos;
    std::vector<bool> textosActivos;

    //unsigned int camaraActiva, viewportActivo;

    // Control del tiempo
    // ------------------
    double then = getTime();
    double now = getTime();
    int lastFPS = 0;
    int fps = 0;

    //Skybox
    Nodo *skybox;
    
    //Shaders
    //std::vector<unsigned int> shaders;
    unsigned int shaderActivo = 0;
    unsigned int shaderSkybox = 0;
    unsigned int shaderBillboard = 0;
    unsigned int shaderTexto = 0;

    //Vector Animaciones
    //------------------
    std::vector<std::unique_ptr<Animacion>> animaciones;

    // Variables billboard loading
    int billboardLoading {43}; // Variable para conocer el número del primer frame del loading
    int billboardLoadingActivo {43}; // Variable para conocer el número de frame activo

};

