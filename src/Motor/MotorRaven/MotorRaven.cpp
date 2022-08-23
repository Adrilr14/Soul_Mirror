
#include "MotorRaven.hpp"
#include <memory>
#include "Nodo.hpp"
#include "ECamara.hpp"
#include "ELuz.hpp"
#include "EModelo.hpp"
#include "GestorRecursos.hpp"
#include "Animacion.hpp"
#include "Billboard.hpp"
#include "Text2D.hpp"
#include "RShader.hpp"
#include "RFuente.hpp"
#include "RImagen.hpp"
#include "Skybox.hpp"

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
        //std::cout << "Failed to initialize GLEW" << std::endl; 
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_NOTEQUAL, 0.0);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT_AND_BACK);
    glFrontFace(GL_CCW);

    // Creamos el gestor de recursos
    // -----------------------------
    gestorRecursos = std::make_unique<GestorRecursos> ();
    //gestorRecursos = new GestorRecursos ();

    // build and compile shaders
    // -------------------------
    //auto resourceShader = gestorRecursos->getRShader("src/Shaders/", false);
    //shaderActivo = gestorRecursos->getRShader("src/Shaders/")->ID;
    //shaders.push_back(shaderActivo);

    // Creamos el nodo escena
    // -----------------------------
    smgr = new Nodo(-1, nullptr, nullptr);
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
        //std::cout << "Failed to create GLFW window" << std::endl;
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

bool MotorRaven::processClick(int key){
    bool pulsada = false;

    if (glfwGetMouseButton(window, key) == GLFW_PRESS)
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
    smgr = new Nodo(-1, nullptr, nullptr);
}

void MotorRaven::endScene() {
    // Borramos todos los hijos de la escena
    smgr->clear();
    // Borramos el nodo escena
    smgr->~Nodo();
    // Igualamos la escena a null
    smgr = nullptr;
    // Reestablecemos todos los vectores
    /*registroLuces.clear();
    lucesActivas.clear();
    registroBillboards.clear();
    billboardsActivos.clear();*/
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

// Añadimos el shader principal
// ----------------------------
void MotorRaven::addShader() {
    if(!shaderActivo)
    {
        auto resourceShader = gestorRecursos->getRShader("Shaders/", false);
        shaderActivo = resourceShader->ID;
        //shaders.push_back(shaderActivo);
    }
}

// Usar el shader que tenemos creado y guardado
// -----------------------------------------------
void MotorRaven::useShader(RShader *sh) {
    // don't forget to enable shader before setting uniforms
    sh->use();
}

// Creamos un billboard
// --------------------
Nodo *MotorRaven::addBillboard(unsigned int id, Nodo *padre, int x, int y, const char* file, bool vertically){
    if(!shaderBillboard){
        auto resourceShader = gestorRecursos->getRShader("Shaders/Billboard", false);
        shaderBillboard = resourceShader->ID;
        //shaders.push_back(shaderBillboard);
    }

    if(padre == nullptr){
        padre = smgr;
    }

    auto image = gestorRecursos->getRImagen(file);
    auto entity = new Billboard(image, x, y, image->getWidth(), image->getHeight());
    
    //auto node = new Nodo(id, entity, padre);
    auto node = std::make_unique<Nodo>(id, entity, padre);

    // Cambiamos la variable de tipo de entidad del nodo
    node->setTipoEntidad(2);

    setBillboardActivo(registrarBillboard(std::move(node)),true);

    return node.get();
}

// Creamos un texto
// --------------------
Nodo *MotorRaven::addTexto(unsigned int id, Nodo *padre, const char* texto, glm::vec4 color, int x, int y, int size, const char* file){
    if(!shaderTexto){
        auto resourceShader = gestorRecursos->getRShader("Shaders/Text2D", false);
        shaderTexto = resourceShader->ID;
        //shaders.push_back(shaderBillboard);
    }

    if(padre == nullptr){
        padre = smgr;
    }

    auto font = gestorRecursos->getRFuente(file);
    auto entity = new Text2D(texto, font, color, x, y, size, font->getWidth(), font->getHeight());
    //auto node = new Nodo(id, entity, padre);
    auto node = std::make_unique<Nodo>(id, entity, padre);

    // Cambiamos la variable de tipo de entidad del nodo
    node->setTipoEntidad(2);

    setTextoActivo(registrarTexto(std::move(node)),true);

    return node.get();
}

// Creamos el skybox
// -----------------
void MotorRaven::addSkybox(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back){
    if(!shaderSkybox)
    {
        auto resourceShader = gestorRecursos->getRShader("Shaders/Skybox", false);
        shaderSkybox = resourceShader->ID;
        //shaders.push_back(shaderSkybox);
    }

    if(skybox)
    {
        //std::cout << "Borro el viejo skybox" << std::endl;
        smgr->borrarHijo(skybox);
    }

    if(padre == nullptr){
        padre = smgr;
    }

    auto rmalla = gestorRecursos->getRMalla(f, nullptr);
    auto skyboxEnt = new Skybox(rmalla, right, left, top, bottom, front, back);
    skybox = new Nodo(id, skyboxEnt, padre);

    skybox->setTraslacion(trasl);
    skybox->setEscalado(esc);
    skybox->setRotacion(rot);

    // Cambiamos la variable de tipo de entidad del nodo
    skybox->setTipoEntidad(1);
}

// Creamos un shader
// -----------------
RShader *MotorRaven::crearShader(const char *path, bool geometry) {
    auto sh = gestorRecursos->getRShader(path, geometry);
    return sh;
}

// Creamos una textura
// -----------------
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
    //auto nodo = new Nodo(id, eLuz, padre);
    auto nodo = std::make_unique<Nodo>(id, eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(std::move(nodo)),true);

    //return nodo.get();
    return nodo.get();
}

Nodo *MotorRaven::crearLuzPuntual(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto eLuz = std::make_unique<ELuz>(intens);
    auto eLuz = new ELuz(intens);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    //auto nodo = new Nodo(id, eLuz, padre);
    auto nodo = std::make_unique<Nodo>(id, eLuz, padre);

    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(std::move(nodo)),true);

    //return nodo.get();
    return nodo.get();
}

Nodo *MotorRaven::crearLuzFocal(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc,
glm::vec4 intens,float apert, float aAng, float aCte, float aLin, float aCuad){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto eLuz = std::make_unique<ELuz>(intens, apert, aAng, aCte, aLin, aCuad);
    auto eLuz = new ELuz(intens, apert, aAng, aCte, aLin, aCuad);
    //auto nodo = std::make_unique<Nodo>(eLuz.get(), padre);
    //auto nodo = new Nodo(id, eLuz, padre);
    auto nodo = std::make_unique<Nodo>(id, eLuz, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //setLuzActiva(registrarLuz(nodo.get()),true);
    setLuzActiva(registrarLuz(std::move(nodo)),true);

    return nodo.get();
    //return nodo;
}


Nodo *MotorRaven::crearModelo(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, const char* f, RTextura *t){
    
    if(padre == nullptr){
        padre = smgr;
    }
    
    //auto eMod = std::make_unique<EModelo>(gestorRecursos->getRMalla(f, c, h, m, n, r));
    auto eMod = new EModelo(gestorRecursos->getRMalla(f, t), t);
    //auto nodo = std::make_unique<Nodo>(eMod.get(), padre);
    auto nodo = new Nodo(id, eMod, padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //return nodo.get();
    return nodo;
}

// Función para crear un nodo con animación
// ----------------------------------------
Nodo *MotorRaven::crearModeloAnimado(std::size_t id, Nodo *padre, glm::vec3 trasl, glm::vec3 rot, glm::vec3 esc, int nAnimacion){
    
    if(padre == nullptr){
        padre = smgr;
    }

    //auto nodo = std::make_unique<Nodo>(eMod.get(), padre);
    auto nodo = new Nodo(id, animaciones[nAnimacion-1].get(), padre);
    
    nodo->setTraslacion(trasl);
    nodo->setEscalado(esc);
    nodo->setRotacion(rot);

    //return nodo.get();
    return nodo;
}

// Función para borrar un nodo
// ---------------------------
void MotorRaven::borrarNodo (Nodo *nodo) {
    nodo->~Nodo();
    //registroBillboards.clear();
    //billboardsActivos.clear();
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

unsigned int MotorRaven::registrarLuz(std::unique_ptr<Nodo> nodoLuz){
   registroLuces.push_back(std::move(nodoLuz));
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

unsigned int MotorRaven::registrarBillboard(std::unique_ptr<Nodo> nodoBillboard){
   registroBillboards.push_back(std::move(nodoBillboard));
   billboardsActivos.push_back(true);
   return registroBillboards.size();
}

void MotorRaven::setBillboardActivo(int nBillboard, bool activo){
    if(nBillboard > 0) billboardsActivos[nBillboard-1] = activo;
}

// Cogemos el billboard del registro de billboards en la posición del vector que se pasa y actualizamos su posición en pantalla
// ----------------------------------------------------------------------------------------------------------------------------
void MotorRaven::setBillboardPos(int nBillboard, int x, int y){
    // Guardamos en una variable el billboard que queremos
    auto billboard = static_cast<Billboard*>(registroBillboards[nBillboard-1]->getEntidad());

    // Actualizamos la posicón en pantalla del billboard si la posición no es negativa
    if(x >= 0) billboard->setPosX(x);
    if(y >= 0) billboard->setPosY(y);
}

// Devolvemos la posición X del billboard que se encuentra en la posición del vector que se pasa
// ---------------------------------------------------------------------------------------------
int MotorRaven::getBillboardPosX(int nBillboard){
    // Guardamos en una variable el billboard que queremos
    auto billboard = static_cast<Billboard*>(registroBillboards[nBillboard-1]->getEntidad());

    // Devolvemos la posición en pantalla
    return billboard->getposX();
}

// Devolvemos la posición Y del billboard que se encuentra en la posición del vector que se pasa
// ---------------------------------------------------------------------------------------------
int MotorRaven::getBillboardPosY(int nBillboard){
    // Guardamos en una variable el billboard que queremos
    auto billboard = static_cast<Billboard*>(registroBillboards[nBillboard-1]->getEntidad());

    // Devolvemos la posición en pantalla
    return billboard->getposY();
}

// FUNCIONES DE TEXTOS 2D
// ----------------------
unsigned int MotorRaven::registrarTexto(std::unique_ptr<Nodo> nodoTexto){
   registroTextos.push_back(std::move(nodoTexto));
   textosActivos.push_back(true);
   return registroTextos.size();
}

void MotorRaven::setTextoActivo(int nTexto, bool activo){
    textosActivos[nTexto-1] = activo;
}

// Cogemos el texto del registro de textos en la posición del vector que se pasa y actualizamos su posición en pantalla
// ----------------------------------------------------------------------------------------------------------------------------
void MotorRaven::setTextoPos(int nTexto, int x, int y){
    // Guardamos en una variable el billboard que queremos
    auto texto = static_cast<Text2D*>(registroTextos[nTexto-1]->getEntidad());

    // Actualizamos la posicón en pantalla del texto si la posición no es negativa
    if(x >= 0) texto->setPosX(x);
    if(y >= 0) texto->setPosY(y);
}

// Devolvemos la posición X del texto que se encuentra en la posición del vector que se pasa
// ---------------------------------------------------------------------------------------------
int MotorRaven::getTextoPosX(int nTexto){
    // Guardamos en una variable el texto que queremos
    auto texto = static_cast<Text2D*>(registroTextos[nTexto-1]->getEntidad());

    // Devolvemos la posición en pantalla
    return texto->getposX();
}

// Devolvemos la posición Y del texto que se encuentra en la posición del vector que se pasa
// ---------------------------------------------------------------------------------------------
int MotorRaven::getTextoPosY(int nTexto){
    // Guardamos en una variable el texto que queremos
    auto texto = static_cast<Text2D*>(registroTextos[nTexto-1]->getEntidad());

    // Devolvemos la posición en pantalla
    return texto->getposY();
}

// FUNCIONES DE ANIMACIONES
// ------------------------
int MotorRaven::addAnimacion(const char* f, RTextura *t, int fps, int nFrames){
    
    std::vector<RMalla*> mallas; // Vector de mallas para pasarle a la Entidad de tipo Animacion
    int n; // Variable para añadir al nombre
    int frames = 0; // Auxiliar para calcular el número de cifras
    int cifras = 0; // Número de cifras del número de frames
    std::string name = ""; // Nombre del archivo de cada frame

    
    
    for (unsigned int i = 0; i < nFrames; i++)
    {
        drawLoading();

        cifras = 0;
        n = i + 1;
        name = f;
        name = name.substr(0, name.find("."));

        // Calculamos el número de cifras del número de frames
        frames = n;
        while (frames > 0)
        {
            frames = frames/10;
            cifras++;
        }

        //drawLoading();

        if(cifras == 1) name = name + "_00000" + std::to_string(n) + ".obj";
        else if(cifras == 2) name = name + "_0000" + std::to_string(n) + ".obj";
        else if(cifras == 3) name = name + "_000" + std::to_string(n) + ".obj";
        else if(cifras == 4) name = name + "_00" + std::to_string(n) + ".obj";
        else if(cifras == 5) name = name + "_0" + std::to_string(n) + ".obj";
        else if(cifras == 6) name = name + "_" + std::to_string(n) + ".obj";

        auto malla = gestorRecursos->getRMalla(name.c_str(), t);
        mallas.push_back(malla);

        //drawLoading();
        //std::cout << "Cifras = " << cifras << std::endl;
        //std::cout << "Nombre malla = " << name << std::endl;

    }
    
    
    //auto eMod = std::make_unique<EModelo>(gestorRecursos->getRMalla(f, c, h, m, n, r));
    //auto eModAnim = new Animacion(mallas, fps);
    auto eModAnim = std::make_unique<Animacion>(mallas, fps, t);
    animaciones.push_back(std::move(eModAnim));

    //return nodo.get();
    return animaciones.size();
}

Entidad *MotorRaven::getAnimacion(int nAnimacion){
    return static_cast<Entidad*>(animaciones[nAnimacion-1].get());
}

// FUNCIONES DE SKYBOX
// -------------------

// Devuelve el skybox activo
// -------------------------
Nodo *MotorRaven::getSkybox() {
    if(skybox)
        return skybox;
}

// OTROS METODOS
// -------------

// Cambiar la textura de un nodo
// -----------------------------
void MotorRaven::cambiarTextura(Nodo *n, const char *f){
    // Cogemos la textura del gestor del recurso
    auto textura = crearTextura(f);
    // Le cambiamos la textura al nodo
    static_cast<EModelo*>(n->getEntidad())->setTextura(textura);
}

std::string MotorRaven::getTextura(Nodo *n){
    return static_cast<EModelo*>(n->getEntidad())->getMalla()->getTextura();
}

// Comprobar si la animación de un nodo ha acabado
// -----------------------------------------------
bool MotorRaven::animationIsEnd(Nodo *n){
    return static_cast<Animacion*>(n->getEntidad())->isEnd();
}

// Actualizar si una animación ha acabado o no
// -------------------------------------------
void MotorRaven::setAnimationEnd(Nodo *n, bool end){
    static_cast<Animacion*>(n->getEntidad())->setEnd(end);
}

// Actualizar el número de malla de una animación
// ----------------------------------------------
void MotorRaven::setAnimationNumMalla(Nodo *n, int nMalla){
    static_cast<Animacion*>(n->getEntidad())->setNumMalla(nMalla);
}

// Dibuja la pantalla de carga
// ---------------------------
void MotorRaven::drawLoading(){
    // Vamos actualizando la pantalla de carga
    now = getTime();
    double time = 1/15;

    // Si pasa un segundo
    if (now - then >= time) {
        setBillboardActivo(billboardLoadingActivo, false);
        billboardLoadingActivo++;
        if(billboardLoadingActivo >= 63) billboardLoadingActivo = 43;
        setBillboardActivo(billboardLoadingActivo, true);
        then = now;
    }

    drawBillboards();
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}

// Desactiva el frame actual de la pantalla de carga
// ---------------------------------------------
void MotorRaven::desactivateLoading(){
    
    setBillboardActivo(billboardLoadingActivo, false);
    
}

// Devuelve el frame de la pantalla de carga activo
// ------------------------------------------------
int MotorRaven::getFrameLoading(){
    return billboardLoadingActivo;
}

// METODOS PARA EL DIBUJADO DE NODOS
// ---------------------------------

// Dibujar el skybox en la escena
// ------------------------------
void MotorRaven::drawSkybox(){
    if(skybox)
    {
        // Draw skybox as last
        // -------------------
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

        // Matrices de la camara
        auto camara = static_cast<ECamara*>(registroCamaras[camaraActiva]->getEntidad());
        auto matrizProyeccion = camara->getMatrizProyeccion();
        auto matrizVista = glm::inverse(registroCamaras[camaraActiva]->getMatrizTransf());

        glDepthMask(GL_FALSE);

        //CAMBIAMOS EL SHADER USADO POR GL
        glUseProgram(shaderSkybox);

        //PASAR A GL ESTA MATRIZ DE VISTA
        glUniformMatrix4fv(glGetUniformLocation(shaderSkybox, "view"), 1, GL_FALSE, glm::value_ptr(matrizVista));
        ///////////

        //PASAR A GL ESTA MATRIZ DE PROYECCIÓN
        glUniformMatrix4fv(glGetUniformLocation(shaderSkybox, "projection"), 1, GL_FALSE, glm::value_ptr(matrizProyeccion));
        ///////////

        //auto mt = skybox->getMatrizTransf();
        //std::cout << mt[0][0] << ", " << mt[0][1] << ", " << mt[0][2] << ", "  << mt[0][3] << std::endl;
        //std::cout << mt[1][0] << ", " << mt[1][1] << ", " << mt[1][2] << ", "  << mt[1][3] << std::endl;
        //std::cout << mt[2][0] << ", " << mt[2][1] << ", " << mt[2][2] << ", "  << mt[2][3] << std::endl;
        //std::cout << mt[3][0] << ", " << mt[3][1] << ", " << mt[3][2] << ", "  << mt[3][3] << std::endl;
        //std::cout << std::endl;
        
        //LLAMAMOS AL DIBUJAR DEL SKYBOX
        skybox->getEntidad()->dibujar(skybox->getMatrizTransf(), shaderSkybox);

        // Draw skybox as last
        // -------------------
        //glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    }
}

// Dibujar los billboards
// ----------------------
void MotorRaven::drawBillboards(){
    // Comprobamos que exista algún billboard
    if (registroBillboards.size() > 0)
    {
        // Dibujamos los billboards delante de todo
        // -------------------
        glDepthFunc(GL_ALWAYS);

        //CAMBIAMOS EL SHADER USADO POR GL
        glUseProgram(shaderBillboard);
        //std::cout << "drawBillboards billboard: " << shaderBillboard << std::endl;
        //std::cout << "Size registroBillboards: " << registroBillboards.size() << std::endl;

        for(unsigned int i=0; i<billboardsActivos.size(); i++) // Recorro el array de billboards activos para saber cuales están activos 
        {
            if(billboardsActivos[i])
            {
                //LLAMAMOS AL DIBUJAR DE LOS BILLBOARDS ACTIVOS
                registroBillboards[i]->getEntidad()->dibujar(registroBillboards[i]->getMatrizTransf(), shaderBillboard);
            }
        }
    }  
}

// Dibujar los Textos
// ----------------------
void MotorRaven::drawTextos(){
    // Comprobamos que exista algún texto
    if (registroTextos.size() > 0)
    {
        // Dibujamos los textos delante de todo
        // -------------------
        glDepthFunc(GL_ALWAYS);

        //CAMBIAMOS EL SHADER USADO POR GL
        glUseProgram(shaderTexto);

        for(unsigned int i=0; i<textosActivos.size(); i++) // Recorro el array de textos activos para saber cuales están activos 
        {
            if(textosActivos[i])
            {
                //LLAMAMOS AL DIBUJAR DE LOS TEXTOS ACTIVOS
                registroTextos[i]->getEntidad()->dibujar(registroTextos[i]->getMatrizTransf(), shaderTexto);
            }
        }
    }  
}

// Renderizar la escena
// ------------------------------
void MotorRaven::dibujarEscena () {
    // Reestablecemos a default la depth function
    // -------------------
    glDepthFunc(GL_LESS);  // change depth function so depth test passes when values are equal to depth buffer's content

    // Use Shader
    // ----------
    glUseProgram(shaderActivo);

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
                glUniform3f(glGetUniformLocation(shaderActivo, ("LucesPuntuales[" + numUniformLuz + "].Position").c_str()), posLuz.x, posLuz.y, posLuz.z);
                //std::cout << "RGBA = " << intensidad.x << "; " << intensidad.y << "; " << intensidad.z << "; " << intensidad.w << ";" << std::endl;
                glUniform3f(glGetUniformLocation(shaderActivo, ("LucesPuntuales[" + numUniformLuz + "].Intensity").c_str()), intensidad.x, intensidad.y, intensidad.z);
                ///////////////////////////

                // AUMENTAMOS EL NUMERO DE LUCES PUNTUALES
                numLucesPuntuales++;
            }
        }
    }

    // PASAR A GL EL NUMERO DE LUCES DE CADA TIPO
    glUniform1i(glGetUniformLocation(shaderActivo, "numLucesPuntuales"), numLucesPuntuales);
    glUniform1i(glGetUniformLocation(shaderActivo, "numLucesDireccionales"), numLucesDireccionales);
    glUniform1i(glGetUniformLocation(shaderActivo, "numLucesFocales"), numLucesFocales);

    //PASAR A GL LA POSICION DE LA CAMARA
    glUniform3f(glGetUniformLocation(shaderActivo, "ViewPos"), posCamara.x, posCamara.y, posCamara.z);
    //////////////

    //PASAR A GL ESTA MATRIZ DE PROYECCIÓN
    glUniformMatrix4fv(glGetUniformLocation(shaderActivo, "projection"), 1, GL_FALSE, glm::value_ptr(matrizProyeccion));
    //////////////

    //PASAR A GL ESTA MATRIZ DE VISTA
    glUniformMatrix4fv(glGetUniformLocation(shaderActivo, "view"), 1, GL_FALSE, glm::value_ptr(matrizVista));
    //////////////
    
    //PASAR A GL EL VIEWPORT ACTIVO
    //if(registroViewports.size() > 0)
    //    glViewport(registroViewports[viewportActivo].xx, registroViewports[viewportActivo].yy, registroViewports[viewportActivo].anch, registroViewports[viewportActivo].alt);
    /////////////////////
    
    auto matriz = glm::mat4x4(1.0f);

    if(smgr)
        smgr->recorrer(matriz, shaderActivo, false);

    // Dibujamos los billboards delante de todo
    // -------------------
    //glDepthFunc(GL_ALWAYS);

    //LLAMAMOS A DRAWBILLBOARDS PARA DIBUJAR LOS BILLBOARDS EN LA ESCENA
    drawBillboards();

    // Dibujamos los billboards delante de todo
    // -------------------
    //glDepthFunc(GL_ALWAYS);

    //LLAMAMOS A DRAWTEXTOS PARA DIBUJAR LOS TEXTOS EN LA ESCENA
    drawTextos();

    // Draw skybox as last
    // -------------------
    //glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

    //  LLAMAMOS A DRAWSKYBOX PARA DIBUJAR EL SKYBOX EN LA ESCENA
    drawSkybox();
}


