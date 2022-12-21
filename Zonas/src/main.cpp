
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

#include <iostream>
#include <memory>
#define GLFW_INCLUDE_NONE

auto device = std::make_unique<MotorRaven> ();
//auto gr = std::make_unique<GestorRecursos> ();
const GLint WIDTH = 1280, HEIGHT = 720;
const GLclampf red = 0.52157f, green = 0.79608f, blue = 0.84314f, alpha = 1.0f;


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    /*if(glfwGetKey(window, GLFW_KEY_F)){
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Soul Mirror", glfwGetPrimaryMonitor(), NULL);  
    } */
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Soul Mirror", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions 
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers 
    if (GLEW_OK != glewInit()){ 
        std::cout << "Failed to initialize GLEW" << std::endl; 
        return EXIT_FAILURE; 
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    auto ourShader = device->crearShader("src/Shaders/");

    // load textures
    // -----------
    auto diffuse = device->crearTextura("media/texturas/cofre/cofre_1001_BaseColor.png");
    auto height = device->crearTextura("media/texturas/cofre/cofre_1001_Height.png");
    auto metallic = device->crearTextura("media/texturas/cofre/cofre_1001_Metallic.png");
    auto normal = device->crearTextura("media/texturas/cofre/cofre_1001_Normal.png");
    auto roughness = device->crearTextura("media/texturas/cofre/cofre_1001_Roughness.png");

    // load models
    // -----------
    //auto ourModel = gr->getRMalla("media/obj/cofre.obj", diffuse, height, metallic, normal, roughness);
    auto ourModel = device->crearModelo(nullptr, glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1.0), "media/obj/cofre.obj", diffuse, height, metallic, normal, roughness);

    // create camera
    // -----------
    auto camera = device->crearCamara(nullptr, glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1.0), false, 40.0, 1280.0, 720.0, 50.0, 0.0, 100.0);

    
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // view/projection transformations
        /*glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();*/
        glm::mat4 view = glm::inverse(camera->getMatrizTransf());
        glm::mat4 projection = device->getProjection();
        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader->setMat4("model", model);
        ourModel->getEntidad()->dibujar(model, ourShader->ID);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;

}

    