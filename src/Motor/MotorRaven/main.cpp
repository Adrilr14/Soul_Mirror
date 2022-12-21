
#include "Nodo.hpp"
#include "Entidad.hpp"
#include "ECamara.hpp"
#include "ELuz.hpp"
#include "EModelo.hpp"
#include "RShader.hpp"
#include "RTextura.hpp"
#include "RMalla.hpp"
#include "GestorRecursos.hpp"
#include "MotorRaven.hpp"

// Glad library
//#include <glad/glad.h>

// GLEW library
#define GLEW_STATIC
#include <glew.h>

// GLFW library
#include <glfw3.h>
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <memory>

const GLint WIDTH = 1920, HEIGHT = 1080;
const GLclampf red = 0.52157f, green = 0.79608f, blue = 0.84314f, alpha = 1.0f;

// Creamos el device
// -----------------
auto device = std::make_unique<MotorRaven> (WIDTH, HEIGHT, "Soul Mirror", false);

// Función para mover el modelo pasado
// -----------------------------------
bool moveModel(MotorRaven *dev, Nodo* object, float fdt, float speed) {
    bool move = false;
    
    float movementX = 0.f;
    float movementZ = 0.f;

    if (dev->processInput(GLFW_KEY_W))
    {
        //movementZ = -(speed * fdt);
        movementZ = -(speed * fdt) * 2;
        object->trasladar(glm::vec3(0.f, 0.f, movementZ));
        move = true;
    }
    else if (dev->processInput(GLFW_KEY_S))
    {
        //movementZ = (speed * fdt);
        movementZ = (speed * fdt) * 2;
        object->trasladar(glm::vec3(0.f, 0.f, movementZ));
        move = true;
    }

    if (dev->processInput(GLFW_KEY_A))
    {
        movementX = -(speed * fdt);
        object->trasladar(glm::vec3(movementX, 0.f, 0.f));
        move = true;
    }
    else if (dev->processInput(GLFW_KEY_D))
    {
        movementX = (speed * fdt);
        object->trasladar(glm::vec3(movementX, 0.f, 0.f));
        move = true;
    }
    
    return move;
}

int main()
{
    // build and compile shaders
    // -------------------------
    auto ourShader = device->crearShader("src/Shaders/");

    // load textures
    // -----------
    auto texturaSpider = device->crearTextura("media/texturas/spider/spider");
    auto texturaCubo = device->crearTextura("media/texturas/cubo/cubo");
    auto texturaErizo = device->crearTextura("media/texturas/erizo/erizo_text_1001");
    auto texturaCofre = device->crearTextura("media/texturas/cofre/cofre_1001");
    auto texturaArbol = device->crearTextura("media/texturas/arbol/arbol");
    auto texturaSuelo = device->crearTextura("media/texturas/suelo_bosque/suelo_bosque");

    // Create viewport
    // ---------------
    //device->registrarViewport(0, 0, 1920, 1080);

    // Nodo luz
    // --------
    auto ourLuz = device->crearLuzPuntual(0, nullptr, glm::vec3(0.f, 1000.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
    //auto ourLuz2 = device->crearLuzPuntual(0, nullptr, glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f));
    //auto ourLuz3 = device->crearLuzPuntual(0, nullptr, glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec4(0.f, 1.f, 0.f, 1.f));

    // Nodo vacío para almacenar la cámara y el modelo
    // -----------------------------------------------
    //auto nodopadre = device->crearNodo(5, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
    auto nodoModelCamara = device->crearNodo(1, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));

    // load models
    // -----------
    auto ourModel = device->crearModelo(2, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), "media/player.obj", texturaCubo);
    auto ourModel2 = device->crearModelo(3, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), "media/erizo.obj", texturaErizo);
    auto ourModel3 = device->crearModelo(4, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 180.f, 0.f), glm::vec3(1.f, 1.f, 1.f), "media/cofre.obj", texturaCofre);
    auto ourModel4 = device->crearModelo(5, nullptr, glm::vec3(20.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), "media/tree.obj", texturaArbol);
    auto ourModel5 = device->crearModelo(6, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), "media/suelo.obj", texturaSuelo);

    // create camera
    // -----------
    auto ourCamera = device->crearCamara(50, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(-60.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), false, -50.0, 50.0, -37.5, 37.5, -1000.0, 1000.0);
    //device->updateCamaraTarget(ourModel->getTranslacionGlobal()); 

    // Control del tiempo
    // ------------------
    double then = device->getTime();
    double now = device->getTime();
    int lastFPS = 0;
    int fps = 0;
    float frameDeltaTime;
    bool primerDibujado = false;
    
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(device->getWindow()))
    {
        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // Medición de tiempo
        // ------------------
        now = device->getTime();
        frameDeltaTime = (now - then) / 1000.f;
        then = now;

        // Actualización del viewport
        // --------------------------
        device->updateViewport();

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Mover modelo
        // ------------
        bool move = moveModel(device.get(), ourModel3, frameDeltaTime, 10000.f);
        
        // render the scene
        // ----------------
        device->dibujarEscena(ourShader->ID);

        ourCamera->setTraslacion(glm::vec3(ourModel3->getTraslacionGlobal().x , 0.f, ourModel3->getTraslacionGlobal().z));

        /*if(!primerDibujado){
            std::cout << "------------------ Posición modelo --------------------" << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
            std::cout << "Matriz transformación ourModel (dibujar) =  "     << ourModel->getMatrizTransf()[0][0] << "  " << ourModel->getMatrizTransf()[0][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[0][2] << "  " << ourModel->getMatrizTransf()[0][3] << std::endl;
            std::cout << "                                            "     << ourModel->getMatrizTransf()[1][0] << "  " << ourModel->getMatrizTransf()[1][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[1][2] << "  " << ourModel->getMatrizTransf()[1][3] << std::endl;
            std::cout << "                                            "     << ourModel->getMatrizTransf()[2][0] << "  " << ourModel->getMatrizTransf()[2][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[2][2] << "  " << ourModel->getMatrizTransf()[2][3] << std::endl;
            std::cout << "                                            "     << ourModel->getMatrizTransf()[3][0] << "  " << ourModel->getMatrizTransf()[3][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[3][2] << "  " << ourModel->getMatrizTransf()[3][3] << std::endl;
            std::cout << std::endl;

            std::cout << "------------------ Posición cámara --------------------" << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
            std::cout << "Matriz transformación ourCamara (dibujar) =  "    << ourCamera->getMatrizTransf()[0][0] << "  " << ourCamera->getMatrizTransf()[0][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[0][2] << "  " << ourCamera->getMatrizTransf()[0][3] << std::endl;
            std::cout << "                                             "    << ourCamera->getMatrizTransf()[1][0] << "  " << ourCamera->getMatrizTransf()[1][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[1][2] << "  " << ourCamera->getMatrizTransf()[1][3] << std::endl;
            std::cout << "                                             "    << ourCamera->getMatrizTransf()[2][0] << "  " << ourCamera->getMatrizTransf()[2][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[2][2] << "  " << ourCamera->getMatrizTransf()[2][3] << std::endl;
            std::cout << "                                             "    << ourCamera->getMatrizTransf()[3][0] << "  " << ourCamera->getMatrizTransf()[3][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[3][2] << "  " << ourCamera->getMatrizTransf()[3][3] << std::endl;
            std::cout << std::endl;
            primerDibujado = true;
        }

        if(move) 
        {
            std::cout << "------------------ Posición nodo modelo-cámara --------------------" << std::endl;
            std::cout << "-------------------------------------------------------------------" << std::endl;
            std::cout << "Matriz transformación nodoModelCamara =  "    << nodoModelCamara->getMatrizTransf()[0][0] << "  " << nodoModelCamara->getMatrizTransf()[0][1] << "  " 
                                                                        << nodoModelCamara->getMatrizTransf()[0][2] << "  " << nodoModelCamara->getMatrizTransf()[0][3] << std::endl;
            std::cout << "                                         "    << nodoModelCamara->getMatrizTransf()[1][0] << "  " << nodoModelCamara->getMatrizTransf()[1][1] << "  " 
                                                                        << nodoModelCamara->getMatrizTransf()[1][2] << "  " << nodoModelCamara->getMatrizTransf()[1][3] << std::endl;
            std::cout << "                                         "    << nodoModelCamara->getMatrizTransf()[2][0] << "  " << nodoModelCamara->getMatrizTransf()[2][1] << "  " 
                                                                        << nodoModelCamara->getMatrizTransf()[2][2] << "  " << nodoModelCamara->getMatrizTransf()[2][3] << std::endl;
            std::cout << "                                         "    << nodoModelCamara->getMatrizTransf()[3][0] << "  " << nodoModelCamara->getMatrizTransf()[3][1] << "  " 
                                                                        << nodoModelCamara->getMatrizTransf()[3][2] << "  " << nodoModelCamara->getMatrizTransf()[3][3] << std::endl;
            std::cout << std::endl;

            std::cout << "------------------ Posición modelo --------------------" << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
            std::cout << "Matriz transformación ourModel (dibujar) =  "     << ourModel->getMatrizTransf()[0][0] << "  " << ourModel->getMatrizTransf()[0][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[0][2] << "  " << ourModel->getMatrizTransf()[0][3] << std::endl;
            std::cout << "                                            "     << ourModel->getMatrizTransf()[1][0] << "  " << ourModel->getMatrizTransf()[1][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[1][2] << "  " << ourModel->getMatrizTransf()[1][3] << std::endl;
            std::cout << "                                            "     << ourModel->getMatrizTransf()[2][0] << "  " << ourModel->getMatrizTransf()[2][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[2][2] << "  " << ourModel->getMatrizTransf()[2][3] << std::endl;
            std::cout << "                                            "     << ourModel->getMatrizTransf()[3][0] << "  " << ourModel->getMatrizTransf()[3][1] << "  " 
                                                                            << ourModel->getMatrizTransf()[3][2] << "  " << ourModel->getMatrizTransf()[3][3] << std::endl;
            std::cout << std::endl;

            std::cout << "------------------ Posición cámara --------------------" << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
            std::cout << "Matriz transformación ourCamara (dibujar) =  "    << ourCamera->getMatrizTransf()[0][0] << "  " << ourCamera->getMatrizTransf()[0][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[0][2] << "  " << ourCamera->getMatrizTransf()[0][3] << std::endl;
            std::cout << "                                             "    << ourCamera->getMatrizTransf()[1][0] << "  " << ourCamera->getMatrizTransf()[1][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[1][2] << "  " << ourCamera->getMatrizTransf()[1][3] << std::endl;
            std::cout << "                                             "    << ourCamera->getMatrizTransf()[2][0] << "  " << ourCamera->getMatrizTransf()[2][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[2][2] << "  " << ourCamera->getMatrizTransf()[2][3] << std::endl;
            std::cout << "                                             "    << ourCamera->getMatrizTransf()[3][0] << "  " << ourCamera->getMatrizTransf()[3][1] << "  " 
                                                                            << ourCamera->getMatrizTransf()[3][2] << "  " << ourCamera->getMatrizTransf()[3][3] << std::endl;
            std::cout << std::endl;
        }*/

        /*std::cout << "------------------ Posición modelo --------------------" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "Posición modelo = " 
        << "X = " <<  ourModel->getTraslacion().x 
        << "; Y = " << ourModel->getTraslacion().y 
        << "; Z = " << ourModel->getTraslacion().z 
        << ";" << std::endl;
        std::cout << std::endl;

        std::cout << "------------------ Posición cámara --------------------" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "Posición cámara = " 
        << "X = " <<  ourCamera->getTraslacion().x 
        << "; Y = " << ourCamera->getTraslacion().y 
        << "; Z = " << ourCamera->getTraslacion().z 
        << ";" << std::endl;
        std::cout << std::endl;*/

        // Input esc (close window)
        // ------------------------
        if (device->processInput(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(device->getWindow(), true);
        }

        // Medición de fps (frames per second)
        // ------------------
        device->updateFrames();
        fps = device->getFPS();

        // Si cambian los FPS los actualizamos
        if(lastFPS != fps)
        {
            // Display the frame count here any way you want.
            device->setTitle("SoulMirror FPS : " + std::to_string(fps) + ";");
            lastFPS = fps;
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(device->getWindow());
        glfwPollEvents();
    }

    return 0;

}

    