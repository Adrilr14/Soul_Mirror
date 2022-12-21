
#include "MotorRaven.hpp"
#include <memory>
#include "Nodo.hpp"
#include "ECamara.hpp"
#include "ELuz.hpp"
#include "EModelo.hpp"
#include "GestorRecursos.hpp"
#include "RShader.hpp"

// GLEW library
#define GLEW_STATIC
#include <glew.h>

// GLFW library
#include <glfw3.h>
#define GLFW_INCLUDE_NONE

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
/*void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}*/

MotorRaven::MotorRaven(const unsigned int w, const unsigned int h, const char *name, bool fullScreen) : width(w), height(h) {

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    createWindow(width, height, name, fullScreen);
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions 
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers 
    if (GLEW_OK != glewInit()){ 
        std::cout << "Failed to initialize GLEW" << std::endl; 
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // Creamos el gestor de recursos
    // -----------------------------
    //gestorRecursos = std::make_unique<GestorRecursos> ();
    gestorRecursos = new GestorRecursos ();

    // build and compile shaders
    // -------------------------
    //shaders.push_back(gestorRecursos->getRShader("src/Shaders/"));
    //shaderActivo = 0;

    // Creamos el nodo escena
    // -----------------------------
    smgr = new Nodo(-1, nullptr, nullptr);;
}

MotorRaven::~MotorRaven() {

    glfwDestroyWindow(window);
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void MotorRaven::createWindow(const unsigned int w, const unsigned int h, const char *name, bool fullScreen) {
    
    // glfw window creation
    // --------------------
    if (fullScreen)
        window = glfwCreateWindow(1920, 1080, name, glfwGetPrimaryMonitor(), NULL);

    else
        window = glfwCreateWindow(w, h, name, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, NULL);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}

// Devuelve la ventana abierta de GLFW
// -----------------------------------
GLFWwindow *MotorRaven::getWindow() {
    return window;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
bool MotorRaven::processInput(int key) {
    bool pulsada = false;

    if (glfwGetKey(window, key) == GLFW_PRESS)
    {
        pulsada = true;
    }
    
    return pulsada;
}

// Actualiza el título de la ventana
// ---------------------------------
void MotorRaven::setTitle(std::string t) {
    glfwSetWindowTitle(window, t.c_str());
}

void MotorRaven::beginScene() {
    // Creamos el nodo escena
    // -----------------------------
    smgr = new Nodo(-1, nullptr, nullptr);;
}

void MotorRaven::endScene() {
    // Borramos todos los hijos de la escena
    smgr->clear();
    // Borramos el nodo escena
    smgr->~Nodo();
    // Igualamos la escena a null
    smgr = nullptr;
}

// Devuelve el tiempo de GLWF
// --------------------------
double MotorRaven::getTime() {
    return glfwGetTime();
}

// Actualizamos el tiempo y los FPS cada segundo
// ---------------------------------------------
void MotorRaven::updateFrames() {
    fps++;
    now = getTime();

    // Si pasa un segundo
    if (now - then >= 1.0) {
        lastFPS = fps;
        fps = 0;
        then = now;
    }
}

// Devuelve los FPS
//-----------------
int MotorRaven::getFPS() {
    return lastFPS;
}

RShader *MotorRaven::crearShader(const char *path) {
    auto sh = gestorRecursos->getRShader(path);
    return sh;
}
/*
// Actualizamos el vector shaders con los ficheros pasados
// -----------------------------------------------
void MotorRaven::addShader(const char *path) {
    shaders.push_back(gestorRecursos->getRShader(path));
    //std::cout << shader->ID << std::endl;
}

// Usar el shader que tenemos creado y guardado
// -----------------------------------------------
void MotorRaven::useShader(RShader *sh) {
    // don't forget to enable shader before setting uniforms
    sh->use();
}*/

RTextura *MotorRaven::crearTextura(const char *fichero) {
    //std::cout << fichero << std::endl;
    auto textura = gestorRecursos->getRTextura(fichero);
    return textura;
}

Nodo *MotorRaven::crearNodo(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto nodo = std::make_unique<Nodo>(id, nullptr, padre);
    auto nodo = new Nodo(id, nullptr, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::getSceneManager() {
    return smgr;
}

Nodo *MotorRaven::crearCamara(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
bool pers, float izq, float der, float inf, float sup, float cerc, float lej){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto eCam = std::make_unique<ECamara>(pers,izq, der, inf, sup, cerc, lej);
    auto eCam = new ECamara(pers,izq, der, inf, sup, cerc, lej);
    //auto nodo = std::make_unique<Nodo>(eCam.get(), padre);
    auto nodo = new Nodo(id, eCam, padre);

    //--------------
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    setCamaraActiva(registrarCamara(nodo));

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::crearLuzDireccional(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens, float aCte, float aLin, float aCuad){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto eLuz = std::make_unique<ELuz>(intens, aCte, aLin, aCuad);
    auto eLuz = new ELuz(intens, aCte, aLin, aCuad);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    auto nodo = new Nodo(id, eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(nodo),true);

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::crearLuzPuntual(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto eLuz = std::make_unique<ELuz>(intens);
    auto eLuz = new ELuz(intens);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    auto nodo = new Nodo(id, eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(nodo),true);

    //return nodo.get();
    return nodo;
}

Nodo *MotorRaven::crearLuzFocal(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens,float apert, float aAng, float aCte, float aLin, float aCuad){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto eLuz = std::make_unique<ELuz>(intens, apert, aAng, aCte, aLin, aCuad);
    auto eLuz = new ELuz(intens, apert, aAng, aCte, aLin, aCuad);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    auto nodo = new Nodo(id, eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(nodo),true);

    //return nodo.get();
    return nodo;
}


Nodo *MotorRaven::crearModelo(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, RTextura *t){
    
    if(padre == nullptr){
        padre = smgr;
    }
    
    //auto eMod = std::make_unique<EModelo>(gestorRecursos->getRMalla(f, c, h, m, n, r));
    auto eMod = new EModelo(gestorRecursos->getRMalla(f, t));
    //auto nodo = std::make_unique<Nodo>(eMod.get(), padre);
    auto nodo = new Nodo(id, eMod, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //return nodo.get();
    return nodo;
}


unsigned int MotorRaven::registrarCamara(Nodo *nodoCamara){
   registroCamaras.push_back(nodoCamara);
   return registroCamaras.size();
}

void MotorRaven::setCamaraActiva(unsigned int nCamara){
    camaraActiva=nCamara-1;
}

void MotorRaven::updateCamaraTarget(glm::vec3 pos){
    static_cast<ECamara*>(registroCamaras[camaraActiva]->getEntidad())->setCameraTarget(pos);
}

unsigned int MotorRaven::registrarLuz(Nodo *nodoLuz){
   registroLuces.push_back(nodoLuz);
   lucesActivas.push_back(true);
   return registroLuces.size();
}

void MotorRaven::setLuzActiva(unsigned int nLuz,bool activa){
    lucesActivas[nLuz-1]=activa;
}

// Actualizamos el viewport activo si se actualiza la ventana
//-----------------------------------------------------------
void MotorRaven::updateViewport() {
    // Obtenemos el width y el height de la ventana
    glfwGetFramebufferSize(window, &width, &height);

    // Cambiamos los valores del viewport activo y se lo pasamos a GL
    viewportActivo.xx = 0;
    viewportActivo.yy = 0;
    viewportActivo.anch = width;
    viewportActivo.alt = height;
    glViewport(viewportActivo.xx, viewportActivo.yy, viewportActivo.anch, viewportActivo.alt);
}

/*unsigned int MotorRaven::registrarViewport(unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto){
    Viewport viewport;
    viewport.xx = x;
    viewport.yy = y;
    viewport.anch = ancho;
    viewport.alt = alto;

    registroViewports.push_back(viewport);

    return registroViewports.size();
}

void MotorRaven::setViewportActivo(unsigned int nViewport){
    viewportActivo = nViewport - 1;
}*/

void MotorRaven::dibujarEscena (unsigned int sh) {
    // Use Shader
    // ----------
    //shaders[shaderActivo]->use();

    // Matrices de la camara
    auto camara = static_cast<ECamara*>(registroCamaras[camaraActiva]->getEntidad());
    auto matrizProyeccion = camara->getMatrizProyeccion();
    //auto matrizVista = glm::lookAt(registroCamaras[camaraActiva]->getTraslacionGlobal(), camara->getCameraTarget(), camara->getCameraUp());
    auto matrizVista = glm::inverse(registroCamaras[camaraActiva]->getMatrizTransf());
    // Posición de la cámara
    auto posCamara = registroCamaras[camaraActiva]->getTraslacionGlobal();

    // Variable para guardar el número de la variable uniform del shader (luces)
    std::string numUniformLuz = "";

    // Variables para guardar la intensidad y la posición de la luz
    glm::vec3 posLuz;
    glm::vec4 intensidad;

    // Varibles para contar el número de las distintas luces que hay
    int numLucesPuntuales        = 0;
    int numLucesDireccionales    = 0;
    int numLucesFocales          = 0;

    for(unsigned int i=0; i<lucesActivas.size();i++) // Recorro el array de luces activas para saber cuales están activas 
    {
        if(lucesActivas[i])
        {
            // TIPOS DE LUZ ---> 0 = DIRECCIONAL; 1 = PUNTUAL; 2 = FOCAL;

            if(static_cast<ELuz*>(registroLuces[i]->getEntidad())->getTipoLuz() == 1)
            {
                // GUARDAMOS EL NUMERO DE LA VARIABLE UNIFORM
                numUniformLuz = std::to_string(numLucesPuntuales);

                // GUARDAMOS LA POSICION Y LA INTENSIDAD DE LA LUZ
                posLuz = registroLuces[i]->getTraslacionGlobal();
                intensidad = static_cast<ELuz*>(registroLuces[i]->getEntidad())->getIntensidad();
                
                // PASAMOS A GL LA POSICION Y LA INTENSIDAD DE A LUZ
                glUniform3f(glGetUniformLocation(sh, ("LucesPuntuales[" + numUniformLuz + "].Position").c_str()), posLuz.x, posLuz.y, posLuz.z);
                //std::cout << "RGBA = " << intensidad.x << "; " << intensidad.y << "; " << intensidad.z << "; " << intensidad.w << ";" << std::endl;
                glUniform3f(glGetUniformLocation(sh, ("LucesPuntuales[" + numUniformLuz + "].Intensity").c_str()), intensidad.x, intensidad.y, intensidad.z);
                ///////////////////////////

                // AUMENTAMOS EL NUMERO DE LUCES PUNTUALES
                numLucesPuntuales++;
            }
        }
    }

    // PASAR A GL EL NUMERO DE LUCES DE CADA TIPO
    glUniform1i(glGetUniformLocation(sh, "numLucesPuntuales"), numLucesPuntuales);
    glUniform1i(glGetUniformLocation(sh, "numLucesDireccionales"), numLucesDireccionales);
    glUniform1i(glGetUniformLocation(sh, "numLucesFocales"), numLucesFocales);

    //PASAR A GL LA POSICION DE LA CAMARA
    glUniform3f(glGetUniformLocation(sh, "ViewPos"), posCamara.x, posCamara.y, posCamara.z);
    //////////////

    //PASAR A GL ESTA MATRIZ DE PROYECCIÓN
    glUniformMatrix4fv(glGetUniformLocation(sh, "projection"), 1, GL_FALSE, glm::value_ptr(matrizProyeccion));
    //////////////

    //PASAR A GL ESTA MATRIZ DE VISTA
    glUniformMatrix4fv(glGetUniformLocation(sh, "view"), 1, GL_FALSE, glm::value_ptr(matrizVista));
    //////////////
    
    //PASAR A GL EL VIEWPORT ACTIVO
    //if(registroViewports.size() > 0)
    //    glViewport(registroViewports[viewportActivo].xx, registroViewports[viewportActivo].yy, registroViewports[viewportActivo].anch, registroViewports[viewportActivo].alt);
    /////////////////////
    
    auto matriz = glm::mat4x4(1.0f);

    if(smgr)
        smgr->recorrer(matriz, sh, false);
}


