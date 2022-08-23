#include "RavenGraphics.hpp"
#include "../EventManager/EventManager.hpp"


// GLEW library
#define GLEW_STATIC
#include <glew.h>

// GLFW library
#include <glfw3.h>
#define GLFW_INCLUDE_NONE

#include "../game/cmp/RenderComponent.hpp"
#include "../game/cmp/PhysicsComponent.hpp"
#include "../game/cmp/InputComponent.hpp"
#include "../game/cmp/IAComponent.hpp"
#include "../game/cmp/DirecComponent.hpp"
#include "../game/cmp/HPComponent.hpp"
#include "../game/cmp/CameraComponent.hpp"
#include "../game/cmp/ItemComponent.hpp"
#include "../game/cmp/ShootComponent.hpp"
#include "../game/cmp/PlayerComponent.hpp"
#include "../facade/RavenSound.hpp"
#include "../Game.hpp"
#include <iostream>

RavenGraphics::RavenGraphics(){
    //rvMotor = std::make_unique<MotorRaven>(1920,1080,"Soul Mirror",true);
    device = new MotorRaven(1920,1080,"Soul Mirror",true);
    //ourShader = device->crearShader("src/Shaders/");
    then = device->getTime();
    now = device->getTime();
    device->beginScene();
    // build and compile shaders
    // -------------------------
    //ourShader = device->crearShader("src/Shaders/");
    device->addShader();

    //BILLBOARDS
    //----------

    //--------------------------------- Menus ------------------------------------------
    //----------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/play.png", false);

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/controls.png", false);
    device->setBillboardActivo(2, false);

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/credits.png", false);
    device->setBillboardActivo(3, false);

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/about.png", false);
    device->setBillboardActivo(4, false);

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/exit.png", false);
    device->setBillboardActivo(5, false);

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/controls_inside.png", false);
    device->setBillboardActivo(6, false);

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/adri.png", false);
    device->setBillboardActivo(7, false);
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/alex.png", false);
    device->setBillboardActivo(8, false);
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/lna.png", false);
    device->setBillboardActivo(9, false);
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/fran.png", false);
    device->setBillboardActivo(10, false);
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/miky.png", false);
    device->setBillboardActivo(11, false);

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/start_screen/about_insideLetra.png", false);
    device->setBillboardActivo(12, false);

    //--------------------------------- HUD ------------------------------------------
    //--------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 1645, 10, "media/HUD/weapons/espadaeng.png", false);
    billboardEspada = 13;
    device->setBillboardActivo(billboardEspada, false);
    billboardArmaActiva = billboardEspada;

    device->addBillboard(-2, nullptr, 1645, 10, "media/HUD/weapons/escudoeng.png", false);
    billboardEscudo = 14;
    device->setBillboardActivo(billboardEscudo, false);

    device->addBillboard(-2, nullptr, 1645, 10, "media/HUD/weapons/pocioneng.png", false);
    billboardPocion = 15;
    device->setBillboardActivo(billboardPocion, false);

    device->addBillboard(-2, nullptr, 1645, 10, "media/HUD/weapons/arcoeng.png", false);
    billboardArco = 16;
    device->setBillboardActivo(billboardArco, false);

    device->addBillboard(-2, nullptr, 1645, 10, "media/HUD/weapons/bombaeng.png", false);
    billboardBomba = 17;
    device->setBillboardActivo(billboardBomba, false);

    //----------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_0_10.png", false);
    billboardSalud10 = 18;
    device->setBillboardActivo(billboardSalud10, false);
    billboardSaludActiva = billboardSalud10;

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_1_10.png", false);
    device->setBillboardActivo(billboardSalud10+1, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_2_10.png", false);
    device->setBillboardActivo(billboardSalud10+2, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_3_10.png", false);
    device->setBillboardActivo(billboardSalud10+3, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_4_10.png", false);
    device->setBillboardActivo(billboardSalud10+4, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_5_10.png", false);
    device->setBillboardActivo(billboardSalud10+5, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_6_10.png", false);
    device->setBillboardActivo(billboardSalud10+6, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_7_10.png", false);
    device->setBillboardActivo(billboardSalud10+7, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_8_10.png", false);
    device->setBillboardActivo(billboardSalud10+8, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_9_10.png", false);
    device->setBillboardActivo(billboardSalud10+9, false);

    device->addBillboard(-2, nullptr, 48, 902, "media/HUD/salud/vida_10_10.png", false);
    billboardSaludActual = billboardSalud10+10;
    device->setBillboardActivo(billboardSaludActual, false);

    //----------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 0, 804, "media/HUD/objetos/pocionpeq1.png", false);
    billboardPocionx1 = 29;
    device->setBillboardActivo(billboardPocionx1, false);
    billboardPocionActual = billboardPocionx1;

    device->addBillboard(-2, nullptr, 0, 804, "media/HUD/objetos/pocionpeq2.png", false);
    device->setBillboardActivo(billboardPocionx1+1, false);

    device->addBillboard(-2, nullptr, 0, 804, "media/HUD/objetos/pocionpeq3.png", false);
    device->setBillboardActivo(billboardPocionx1+2, false);

    device->addBillboard(-2, nullptr, 0, 804, "media/HUD/objetos/pocionpeq4.png", false);
    device->setBillboardActivo(billboardPocionx1+3, false);

    device->addBillboard(-2, nullptr, 0, 804, "media/HUD/objetos/pocionpeq5.png", false);
    device->setBillboardActivo(billboardPocionx1+4, false);

    //----------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 151, 810, "media/HUD/objetos/llave1.png", false);
    billboardLlavex1 = 34;
    device->setBillboardActivo(billboardLlavex1, false);
    billboardLlaveActual = billboardLlavex1;
    
    device->addBillboard(-2, nullptr, 151, 810, "media/HUD/objetos/llavex2.png", false);
    device->setBillboardActivo(billboardLlavex1+1, false);

    device->addBillboard(-2, nullptr, 151, 810, "media/HUD/objetos/llavex3.png", false);
    device->setBillboardActivo(billboardLlavex1+2, false);

    device->addBillboard(-2, nullptr, 151, 810, "media/HUD/objetos/llavex4.png", false);
    device->setBillboardActivo(billboardLlavex1+3, false);

    //------------------------------ CUADRO DIALOGO -----------------------------------
    //---------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/cuadro_dialogo.png", false);
    billboardCuadroDialogo = 38;
    device->setBillboardActivo(billboardCuadroDialogo, false);

    //---------------------------------- PAUSE ----------------------------------------
    //---------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/pause/resume.png", false);
    billboardPausaResume = 39;
    device->setBillboardActivo(billboardPausaResume, false);
    billboardPausaActual = billboardPausaResume;

    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/pause/exit.png", false);
    billboardPausaExit = 40;
    device->setBillboardActivo(billboardPausaExit, false);

    //---------------------------------- GAME OVER ----------------------------------------
    //-------------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/gameover.png", false);
    billboardGameOver = 41;
    device->setBillboardActivo(billboardGameOver, false);

    //---------------------------------- END GAME -----------------------------------------
    //-------------------------------------------------------------------------------------
    device->addBillboard(-2, nullptr, 0, 0, "media/HUD/end.png", false);
    billboardEndGame = 42;
    device->setBillboardActivo(billboardEndGame, false);

    //--------------------------------- LOADING --------------------------------------
    //--------------------------------------------------------------------------------
    std::string loadingFrame = "";
    for (unsigned int i = 1; i < 21; i++)
    {
        loadingFrame = "media/HUD/loading/" + std::to_string(i) + ".png";
        device->addBillboard(-2, nullptr, 0, 0, loadingFrame.data(), false);
        device->setBillboardActivo((43+i)-1, false);
    }


    //TEXTOS
    //------
    /*const char *text =  "This is the first prototype of our game.\n"
                        "The purpose of the game is to show the mechanics\n"
                        "and reach the end of the map.";
    device->addTexto(-2, nullptr, text, glm::vec4(1.f, 1.f, 1.f, 1.f), 241, 829, 32, "media/fonts/font_2.png");
    device->setTextoActivo(1, false);*/

    //SKYBOX
    //------
    //device->addSkybox("media/skybox/right.jpg",
    //                    "media/skybox/left.jpg",
    //                    "media/skybox/top.jpg",
    //                    "media/skybox/bottom.jpg",
    //                    "media/skybox/front.jpg",
    //                    "media/skybox/back.jpg");
//
    //PONER LAS LUCES COMO COMPONENTE Y CREARLAS EN EL .MAX Y EXPORTALAS AL JSON
    device->crearLuzPuntual(120, nullptr, glm::vec3(0.f, 1000.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
    addEventListeners();
}
// Función para rotar la cámara pasada
// -----------------------------------
void RavenGraphics::rotateCamera(MotorRaven *dev, Nodo *camera, float fdt, float speed) {
    ////std::cout << "Hola" << std::endl;
//
    //float movementX = 0.f;
    //float movementY = 0.f;
    //auto cameracmp = manager->getComponents<CameraComponent_t>()[0];
    //auto entidadCamara = manager->getEntityByID(cameracmp.getEntityID());
    //auto phycmp = entidadCamara->getComponent<PhysicsComponent_t>();
//
    //if (dev->processInput(GLFW_KEY_LEFT))
    //{
    //    //movementY = -(speed * fdt);
    //    movementY = -(speed * fdt) * 2;
    //    //camera->rotar(glm::vec3(0.f, movementY, 0.f));
    //    phycmp->ry += movementY;
    //}
    //else if (dev->processInput(GLFW_KEY_RIGHT))
    //{
    //    //movementZ = (speed * fdt);
    //    movementY = (speed * fdt) * 2;
    //    //camera->rotar(glm::vec3(0.f, movementY, 0.f));
    //    phycmp->ry += movementY;
    //}
//
    //if (dev->processInput(GLFW_KEY_DOWN))
    //{
    //    movementX = -(speed * fdt);
    //    //camera->rotar(glm::vec3(movementX, 0.f, 0.f));
    //    phycmp->rx += movementX;
    //}
    //else if (dev->processInput(GLFW_KEY_UP))
    //{
    //    movementX = (speed * fdt);
    //    //camera->rotar(glm::vec3(movementX, 0.f, 0.f));
    //    phycmp->rx += movementX;
    //}
}

// Función para mover un billboard
// -----------------------------------
void RavenGraphics::moveBillboard(MotorRaven *dev) {
//
//    int nbillboard = 1;
//
//    auto posX = device->getBillboardPosX(nbillboard);
//    auto posY = device->getBillboardPosY(nbillboard); 
//
//    if (dev->processInput(GLFW_KEY_J))
//    {
//        posX -= 1;
//        dev->setBillboardPos(nbillboard, posX, -1);
//    }
//    else if (dev->processInput(GLFW_KEY_L))
//    {
//        posX += 1;
//        dev->setBillboardPos(nbillboard, posX, -1);
//    }
//
//    if (dev->processInput(GLFW_KEY_K))
//    {
//        posY -= 1;
//        dev->setBillboardPos(nbillboard, -1, posY);
//    }
//    else if (dev->processInput(GLFW_KEY_I))
//    {
//        posY += 1;
//        dev->setBillboardPos(nbillboard, -1, posY);
//    }
//
//    if (dev->processInput(GLFW_KEY_0))
//    {
//        //std::cout << "Posición en X = " << posX << "; Posición en Y = " << posY << std::endl;
//    }
//    
}

// Función para mover un texto
// -----------------------------------
void RavenGraphics::moveText() {
/*
    int nText = 1;

    auto posX = device->getTextoPosX(nText);
    auto posY = device->getTextoPosY(nText); 

    if (device->processInput(GLFW_KEY_F))
    {
        posX -= 1;
        device->setTextoPos(nText, posX, -1);
    }
    else if (device->processInput(GLFW_KEY_H))
    {
        posX += 1;
        device->setTextoPos(nText, posX, -1);
    }

    if (device->processInput(GLFW_KEY_G))
    {
        posY -= 1;
        device->setTextoPos(nText, -1, posY);
    }
    else if (device->processInput(GLFW_KEY_T))
    {
        posY += 1;
        device->setTextoPos(nText, -1, posY);
    }

    if (device->processInput(GLFW_KEY_0))
    {
        std::cout << "Posición en X = " << posX << "; Posición en Y = " << posY << std::endl;
    }
*/
}


void RavenGraphics::createWindow(){
    //Sobrecargar los parametros de entrada de la funcion
    device->createWindow(1920,1080,"Soul Mirror",true);
}

void RavenGraphics::beginScene() {
    //device->beginScene();
}

void RavenGraphics::endScene() {
    //device->endScene();
}


bool RavenGraphics::menuNavegation() {
    // Variable para comprobar si se ha pulsado alguna tecla
    bool pulsada = false;

    if ((device->processInput(GLFW_KEY_W) || device->processInput(GLFW_KEY_UP)) && now - beforeMenuNavegation >= 0.33 && menuActivo < 6)
    {
        EventManager::getInstancia().addEvent(Event{EventType::Menu_Change});
        // Desactivamos el menú anterior
        device->setBillboardActivo(menuActivo, false);

        menuActivo--;

        if(menuActivo == 0) menuActivo = 5;

        // Activamos el menú nuevo
        device->setBillboardActivo(menuActivo, true);

        pulsada = true;

    }
    else if ((device->processInput(GLFW_KEY_S) || device->processInput(GLFW_KEY_DOWN)) &&  now - beforeMenuNavegation >= 0.33 && menuActivo < 6)
    {
        EventManager::getInstancia().addEvent(Event{EventType::Menu_Change});
        // Desactivamos el menú anterior
        device->setBillboardActivo(menuActivo, false);

        menuActivo++;

        if(menuActivo == 6) menuActivo = 1;

        // Activamos el menú nuevo
        device->setBillboardActivo(menuActivo, true);

        pulsada = true;
    }

    if ((device->processInput(GLFW_KEY_A) || device->processInput(GLFW_KEY_LEFT)) && now - beforeMenuNavegation >= 0.33)
    {
        EventManager::getInstancia().addEvent(Event{EventType::Menu_Change});
        if(menuActivo == 7 || menuActivo == 8 || menuActivo == 9 || menuActivo == 10 || menuActivo == 11)
        {
            // Desactivamos el menú anterior
            device->setBillboardActivo(menuActivo, false);

            menuActivo--;

            if(menuActivo == 6) menuActivo = 11;

            // Activamos el menú nuevo
            device->setBillboardActivo(menuActivo, true);

            pulsada = true;
        }
        
    }
    else if ((device->processInput(GLFW_KEY_D) || device->processInput(GLFW_KEY_RIGHT)) && now - beforeMenuNavegation >= 0.33)
    {
        EventManager::getInstancia().addEvent(Event{EventType::Menu_Change});
        if(menuActivo == 7 || menuActivo == 8 || menuActivo == 9 || menuActivo == 10 || menuActivo == 11)
        {
            // Desactivamos el menú anterior
            device->setBillboardActivo(menuActivo, false);

            menuActivo++;

            if(menuActivo == 12) menuActivo = 7;

            // Activamos el menú nuevo
            device->setBillboardActivo(menuActivo, true);

            pulsada = true;
        }
    }

    if(device->processInput(GLFW_KEY_ENTER) && now - beforeMenuNavegation >= 0.33)
    {
        // Desactivamos el menú anterior
        device->setBillboardActivo(menuActivo, false);

        if(menuActivo == 2){
            menuActivo = 6;
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Select});
        }else if(menuActivo == 6){
            menuActivo = 2;
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Back});
        } 

        if(menuActivo == 3){
            menuActivo = 7;
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Select});
        } 
        else if(menuActivo == 7 || menuActivo == 8 || menuActivo == 9 || menuActivo == 10 || menuActivo == 11){
            menuActivo = 3; 
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Back});
        }
        if(menuActivo == 4) 
        {
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Select});
            menuActivo = 12;
            //device->setTextoActivo(1, true);
        }
        else if(menuActivo == 12)
        {
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Back});
            menuActivo = 4;
            //device->setTextoActivo(1, false);
        }

        if(menuActivo == 5) glfwSetWindowShouldClose(device->getWindow(), true);

        // Activamos el menú nuevo
        device->setBillboardActivo(menuActivo, true);
        
        pulsada = true;
    }
    
    return pulsada;
}

void RavenGraphics::animacionDead(EventInfo){
    if(device->getSceneManager()->getEntidad() != device->getAnimacion(animacionMuerte))
        device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionMuerte));    
}

void RavenGraphics::animacionPunch(EventInfo){
    bool playerDead = Game::GetInstance()->isPlayerDead();
    if(!playerDead && device->getSceneManager()->getEntidad() != device->getAnimacion(animacionHerida))
        device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionHerida));   
}

void RavenGraphics::animacionArrastrar(EventInfo){
    bool playerDead = Game::GetInstance()->isPlayerDead();
    if(!playerDead && device->getSceneManager()->getEntidad() != device->getAnimacion(animacionEmpujar))
        device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionEmpujar));    
}


void RavenGraphics::drawInit(){
    // Medición de tiempoBillboards
    // ------------------
    now = device->getTime();
    frameDeltaTime = (now - then) / 1000.f;
    then = now;

    // Actualización del viewport
    // --------------------------
    //device->updateViewport();

    // Comprobamos si nos movemos por el menú
    bool pulsada = menuNavegation();

    // Comprobamos si se mueve el texto
    moveText();

    // Si se pulsa alguna tecla se reinicia la cuenta de FPS
    if(pulsada) beforeMenuNavegation = now;

    // Dibujamos el menú
    device->drawBillboards();

    // Dibujamos el texto
    device->drawTextos();

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

void RavenGraphics::drawCredits(){

}

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

void RavenGraphics::drawGame(){
// don't forget to enable shader before setting uniforms
        //ourShader->use();

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
        //bool move = moveModel(device, model, frameDeltaTime, 10000.f);

        // Si se pulsa alguna tecla se reinicia la cuenta de FPS
        //if(pulsadaInputGame) beforeInputGame = now;
        
        // Comprobamos si se mueve el billboard
        // ------------------------------------
        moveBillboard(device);
        // render the scene
        // ----------------
        //rotateCamera(ourCamera,frameDeltaTime, 10000.f);
        rotateCamera(device, ourCamera, frameDeltaTime, 10000.f);

        auto posPlayer = device->getSceneManager()->getNodoFromID(1)->getTraslacion();
        
        ourCamera->setTraslacion(posPlayer);

        //device->dibujarEscena(ourShader->ID);
        device->dibujarEscena();

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


void RavenGraphics::drawControls(){

}

void RavenGraphics::drawPause(){
    now = device->getTime();
    frameDeltaTime = (now - then) / 1000.f;
    then = now;

    // Actualización del viewport
    // --------------------------
    device->updateViewport();

    // Aumentamos el contador de FPS, que se usa para que no se mueva tan rápido por el menú

    // Comprobamos si nos movemos por el menú
    //bool pulsada = menuNavegation();

    // Si se pulsa alguna tecla se reinicia la cuenta de FPS
    //if(pulsada) contFPS = 0;

    // Comprobamos si nos movemos por el menú
    //pulsadaPause = false;

    // Si se pulsa alguna tecla se reinicia la cuenta de FPS
    //if(pulsadaPause) beforeMenuPause = now;

    // Dibujamos el menú
    device->drawBillboards();

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

//*************METODOS DE ACTUALIZACION
void RavenGraphics::cameraUpdate() {
    
}

void RavenGraphics::updateEntities() {
    glm::vec3 newPosition;
     for(auto& iacmp : manager->getComponents<IAComponent_t>()){
         //std::cout<<"ID de la IA: "<<iacmp.getEntityID()<<"\n";
        auto* e = manager->getEntityByID(iacmp.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->template getComponent<PhysicsComponent_t>();
            if(phycmp){
                newPosition.x = phycmp->x;
                newPosition.y = phycmp->y;
                newPosition.z = phycmp->z;
                
                if(device->getSceneManager()->getNodoFromID(e->getEntityID())){//hay que ver que el nodo existe, si no explota
                    //std::cout<<"La posicion del enemy es X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
                    device->getSceneManager()->getNodoFromID(e->getEntityID())->setTraslacion(newPosition);
                }
            }
            //delete phycmp;
        }
        //delete e;
    }

    for(auto& phyCmp : manager->getComponents<PhysicsComponent_t>()){
        auto entidad = manager->getEntityByID(phyCmp.getEntityID());
        if(entidad){
            if(device->getSceneManager()->getNodoFromID(entidad->getEntityID())){
                device->getSceneManager()->getNodoFromID(entidad->getEntityID())->setTraslacion(
                    glm::vec3(phyCmp.x,phyCmp.y,phyCmp.z));
                device->getSceneManager()->getNodoFromID(entidad->getEntityID())->setRotacion(
                    glm::vec3(phyCmp.rx,phyCmp.ry,phyCmp.rz));
            }
        }
    }
    
    for(auto& renCmp : manager->getComponents<RenderComponent_t>()){
        auto entidad = manager->getEntityByID(renCmp.getEntityID());
        if(entidad){
            if(device->getSceneManager()->getNodoFromID(entidad->getEntityID())){
                device->getSceneManager()->getNodoFromID(entidad->getEntityID())->setVisibilidad(renCmp.isVisible);
                if(renCmp.texturePathDamage != ""){
                    device->cambiarTextura(device->getSceneManager()->getNodoFromID(entidad->getEntityID()),renCmp.texturePathDamage.data());
                    ids.push_back(entidad->getEntityID());
                    segundos.push_back(now);
                }
            }
        }
    }

    for(unsigned int i = 0; i < segundos.size(); i++ ){
        if(now - segundos[i] >= 1.0){
            auto* entidadCambText = manager->getEntityByID(ids[i]);
            if(entidadCambText){
                auto* render = entidadCambText->getComponent<RenderComponent_t>();
                if(render){
                    device->cambiarTextura(device->getSceneManager()->getNodoFromID(entidadCambText->getEntityID()),render->texturePath.data());
                    render->texturePathDamage = "";
                    ids.erase(ids.begin()+i);
                    segundos.erase(segundos.begin()+i);
                }
            }
            segundos[i] = now;
        }
    }

    /*if(now - beforeTexture >= 1.5){
        if(ids.size() > 0){
            int i = ids.front();
            auto* entidadCambText = manager->getEntityByID(i);
            if(entidadCambText){
                auto* render = entidadCambText->getComponent<RenderComponent_t>();
                if(render){
                    device->cambiarTextura(device->getSceneManager()->getNodoFromID(entidadCambText->getEntityID()),render->texturePath.data());
                    render->texturePathDamage = "";
                    ids.pop_front();
                }
            }
        }
        beforeTexture = now;
    }
    */
    ////int dirPrev = -1;
    //auto& player = manager->getComponents<InputComponent_t>();
    //auto* e = manager->getEntityByID(player[0].getEntityID());
    //if(e && e->template getComponent<PhysicsComponent_t>()){
    //    auto* phycmp = e->template getComponent<PhysicsComponent_t>();
    //    if(phycmp){
    //        auto* ren = e->template getComponent<RenderComponent_t>();
    //        //auto posBulletCh = world->getCharacter()->getGhostObject()->getWorldTransform().getOrigin();
    //        newPosition.x = phycmp->x; 
    //        newPosition.y = ren->l/2;
    //        newPosition.z = phycmp->z; 
    //        auto dir = e->template getComponent<DirecComponent_t>();
    //        //dirPrev = dir->dirPrevia;
    //        //std::cout << "Posicion del personaje X Y Z : " << newPosition.x << " " <<  newPosition.y << " " << newPosition.z << std::endl; 
    //        auto items = e->getComponent<ItemComponent_t>();
    //        if(items->m_seleccionado != Weapons_utilities::not_catched){
    //            auto* arma = manager->getEntityByID(items->m_seleccionado);
    //            if(arma){
    //                std::cout << "La arma :" << items->m_seleccionado << std::endl;
    //                EventInfo info;
    //                info.id = items->m_seleccionado;
    //                auto nodoWeapon = device->getSceneManager()->getNodoFromID(info.id); 
    //                auto posicion = arma->getComponent<PhysicsComponent_t>();
    //                auto render = arma->getComponent<RenderComponent_t>();
    //                //auto rotacionArma = std::tuple<float,float,float>(90,0,0);
    //                //Miramos la direccion del personaje 
    //                auto rotacionArma = std::tuple<float,float,float>(0,0,0);
    //                if(dir){
    //                    if(dir->dirPrevia == 1){
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = -90; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,-90);
    //                    }else if(dir->dirPrevia == 2){
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = 90; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,90);
    //                    }else if(dir->dirPrevia == 3){
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = 0; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,0);
    //                    }else if(dir->dirPrevia == 4){
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = 180; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,180);
    //                    }else if(dir->dirPrevia == 5){
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = -45; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,-45); 
    //                    }else if(dir->dirPrevia == 6){
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = 45; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,45);
    //                    }else if(dir->dirPrevia == 7){
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = 225; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,225);
    //                    }else{
    //                        posicion->rx = 90; posicion->ry = 0; posicion->rz = 135; 
    //                        //rotacionArma = std::tuple<float,float,float>(90,0,135);
    //                    }
    //                    rotacionArma = std::tuple<float,float,float>(posicion->rx,posicion->ry,posicion->rz);
    //                }
    //                posicion->x = newPosition.x;
    //                posicion->y = newPosition.y;
    //                posicion->z = newPosition.z;
    //                render->isVisible = true;
    //                info.posX = posicion->x;
    //                info.posY = posicion->y;
    //                info.posZ = posicion->z;
    //                info.rotationAxis = rotacionArma;
    //                nodoWeapon->setVisibilidad(true);
    //                EventManager::getInstancia().addEvent(Event{EventType::setWeaponsPos,info});
    //            }
    //        }
    //        if(device->getSceneManager()->getNodoFromID(e->getEntityID())){
    //            device->getSceneManager()->getNodoFromID(e->getEntityID())->setTraslacion(newPosition);
    //            device->getSceneManager()->getNodoFromID(e->getEntityID())->setRotacion(glm::vec3(phycmp->rx,phycmp->ry,phycmp->rz));
    //        }
    //        //if(smgr->getSceneNodeFromId(e->getEntityID())){
    //        //    smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);   
    //        //    //world->walkingCharacter(newPosition.X,newPosition.Y,newPosition.Z);
    //        //}//hay que ver que el nodo existe, si no explota{
    //        //std::cout<<"X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
    //    }
    //    //delete phycmp;
    //}
    //    //delete e;



    for(auto& bala : manager->getComponents<ShootComponent_t>()){
        auto* e = manager->getEntityByID(bala.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            //std::cout << "ShootComponent : " << e->getName() << std::endl;
            auto* phycmp = e->template getComponent<PhysicsComponent_t>();
            newPosition.x = (phycmp->x);
            newPosition.y = (phycmp->y);
            newPosition.z = (phycmp->z);
            //std::cout << "Posicion de la bala X Y Z : " << newPosition.x << " " <<  newPosition.y << " " << newPosition.z << std::endl; 
            if(device->getSceneManager()->getNodoFromID(e->getEntityID()))//hay que ver que el nodo existe, si no explota
                device->getSceneManager()->getNodoFromID(e->getEntityID())->setTraslacion(newPosition);
        }
    }
}

//*************METODOS DE INPUT***************
void RavenGraphics::getInputInit(){
        EventInfo info;
        info.state_type = 4;

        if(device->processInput(GLFW_KEY_ENTER) && menuActivo == 1){
            // Desactivamos el menú
            device->setBillboardActivo(1, false);

            // Activamos el HUD
            device->setBillboardActivo(billboardEspada, true);
            device->setBillboardActivo(billboardSaludActual, true);
            //device->setBillboardActivo(billboardPocionActual, true);
            //device->setBillboardActivo(billboardLlaveActual, true);

            EventManager::getInstancia().addEvent(Event{EventType::State_Change,info});
        }
    
}

void RavenGraphics::getInputCredits(){
   
}

void RavenGraphics::getInputGame(){
    auto& inpcmp = manager->getComponents<InputComponent_t>();
    //con esto sacamos la entidad del jugador
    auto* e = manager->getEntityByID(inpcmp[0].getEntityID());
    auto* input = e->getComponent<InputComponent_t>();
    input->keySpace = false;
    input->leftclick = false;
    EventInfo info;
    if(e){
        auto direc = e->getComponent<DirecComponent_t>();
        auto itemCmp = e->getComponent<ItemComponent_t>();
        bool playerDead = Game::GetInstance()->isPlayerDead();

        auto hp = e->getComponent<HPComponent_t>();
        auto vidaPlayer = hp->life;

        //**NUMERO POCIONES Y LLAVES***
        auto nLlaves = itemCmp->keys.numberofKeys;
        auto nPociones = itemCmp->potion.numberPotions;

        if (llavesAntes != nLlaves)
        {
            if(llavesAntes == 0)
            {
                device->setBillboardActivo(billboardLlaveActual, true);
            }
            else
            {
                llavesAntes = nLlaves;
                if (nLlaves == 0) 
                { 
                    device->setBillboardActivo(billboardLlaveActual, false);
                }
                else if (billboardLlaveActual != (billboardLlavex1+nLlaves)-1)
                {
                    device->setBillboardActivo(billboardLlaveActual, false);
                    billboardLlaveActual = (billboardLlavex1+nLlaves)-1;
                    device->setBillboardActivo(billboardLlaveActual, true);
                }
            }

            llavesAntes = nLlaves;
        }
        
        if (pocionesAntes != nPociones)
        {
            if(pocionesAntes == 0)
            {
                device->setBillboardActivo(billboardPocionActual, true);
            }
            else
            {
                if (nPociones == 0) 
                { 
                    device->setBillboardActivo(billboardPocionActual, false);
                }
                else if (billboardPocionActual != (billboardPocionx1+nPociones)-1)
                {
                    device->setBillboardActivo(billboardPocionActual, false);
                    billboardPocionActual = (billboardPocionx1+nPociones)-1;
                    device->setBillboardActivo(billboardPocionActual, true);
                }
            }
            
            pocionesAntes = nPociones;
        }
        //****CAMBIOS DE ARMA***
        auto* playerCmp = e->getComponent<PlayerComponent_t>();
        if(device->processClick(GLFW_MOUSE_BUTTON_LEFT) && now - beforeInputGame >= 0.6){
            if(itemCmp->m_seleccionado != Weapons_utilities::not_catched
                && itemCmp->weapons[itemCmp->m_seleccionado] == true && playerCmp->temporal == 0){
                
                auto* arma = manager->getEntityByID(2); // ID 2 porque es el cubo invisible con aabb
                if(arma && !playerDead){
                    if(itemCmp->m_seleccionado == Weapons_utilities::Espada){device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionEspada));}
                    else if(itemCmp->m_seleccionado == Weapons_utilities::Arco){device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionArco));}
                    else if(itemCmp->m_seleccionado == Weapons_utilities::Pocion && nPociones > 0 && vidaPlayer < hp->maxLife){device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionPocion));}
                    else if(itemCmp->m_seleccionado == Weapons_utilities::Escudo){device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionEscudo));}

                    info.id = arma->getEntityID();
                    itemCmp->executeAction(info);
                    input->leftclick = true;
                    //int segundos = 0;
                    //clock_t tiempoDeInicio, tiempoAcual;    
                    //tiempoDeInicio = time(NULL); // Obtiene el tiempo a la hora de iniciar el cronometro - Variable de referencia
                    //while(1){
                    ///* Se inicia el cronometro */
                    //    tiempoAcual = time(NULL); // Obtiene el tiempo para ser comparado con la variable de refencia
                    //    segundos = (tiempoAcual-tiempoDeInicio); // Se obtiene la cantidad de segundos

                    //    if(segundos == 2){ //Comprueba que la cantidad de segundos sea menor a 60 segundos
                    //        std::cout << "ENTRA"<< std::endl;
                    //        break;
                    //    }
                    //}
                }else{
                    //std::cout << "Control de errores";
                    //Hacer que no se borre el arma cuando pasa de zona cambiar el valor del fore en vez de a 1 al tam del invenatario
                }
            }else{
                auto playerChilds = e->getComponent<PlayerComponent_t>();
                auto entidadB = manager->getEntityByID(playerChilds->temporal);
                if(entidadB){
                    double PI = 3.14159265359;
                    auto shoot = manager->addComponent<ShootComponent_t>(*entidadB);
                    auto shootcmp = entidadB->getComponent<ShootComponent_t>();
                    shootcmp->type = Balatype::playershot;
                    auto phycmp = entidadB->getComponent<PhysicsComponent_t>();
                    Vector3D positionsShooting = direc->getValuesDirection(direc->dirPrevia);
                    phycmp->x += positionsShooting.m_x*10;
                    phycmp->y  = 2;
                    phycmp->z += positionsShooting.m_z*10;
                    phycmp->vx = 1; phycmp->vz = 1;
                    if(direc->dirPrevia == 1){
                        shootcmp->angle = (1/2)*PI;
                        //rotacionArma = std::tuple<float,float,float>(90,0,-90);
                    }else if(direc->dirPrevia == 2){
                        shootcmp->angle = (3/2)*PI; 
                        //rotacionArma = std::tuple<float,float,float>(90,0,90);
                    }else if(direc->dirPrevia == 3){
                        shootcmp->angle =  PI/2;
                        //rotacionArma = std::tuple<float,float,float>(90,0,0);
                    }else if(direc->dirPrevia == 4){
                        shootcmp->angle =  3*PI/2;
                        //rotacionArma = std::tuple<float,float,float>(90,0,180);
                    }else if(direc->dirPrevia == 5){
                        shootcmp->angle = 45; 
                        //rotacionArma = std::tuple<float,float,float>(90,0,-45); 
                    }else if(direc->dirPrevia == 6){
                        shootcmp->angle = 90; 
                        //rotacionArma = std::tuple<float,float,float>(90,0,45);
                    }else if(direc->dirPrevia == 7){
                        shootcmp->angle = -45; 
                        //rotacionArma = std::tuple<float,float,float>(90,0,225);
                    }else{
                        shootcmp->angle = 180; 
                        //rotacionArma = std::tuple<float,float,float>(90,0,135);
                    }
                    playerChilds->removeTemporal();
                    itemCmp->m_seleccionado = Weapons_utilities::Espada;
                }
            }
            beforeInputGame = now;   
        }

        // Comprobar si acaban las animaciones de las armas para cambiarlas
        // ----------------------------------------------------------------
        if(!playerDead){
            if(device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionEspada))
            {
                if(device->animationIsEnd(device->getSceneManager()->getNodoFromID(1)))
                {
                    device->setAnimationEnd(device->getSceneManager()->getNodoFromID(1), false);
                    //device->setAnimationNumMalla(device->getSceneManager()->getNodoFromID(1), 0);
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionStandby));
                }
            }

            if(device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionArco))
            {
                if(device->animationIsEnd(device->getSceneManager()->getNodoFromID(1)))
                {
                    device->setAnimationEnd(device->getSceneManager()->getNodoFromID(1), false);
                    //device->setAnimationNumMalla(device->getSceneManager()->getNodoFromID(1), 0);
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionStandby));
                }
            }

            if(device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionPocion))
            {
                if(device->animationIsEnd(device->getSceneManager()->getNodoFromID(1)))
                {
                    device->setAnimationEnd(device->getSceneManager()->getNodoFromID(1), false);
                    //device->setAnimationNumMalla(device->getSceneManager()->getNodoFromID(1), 0);
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionStandby));
                }
            }

            if(device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionEscudo) && !device->processClick(GLFW_MOUSE_BUTTON_LEFT))
            {
                if(device->animationIsEnd(device->getSceneManager()->getNodoFromID(1)))
                {
                    device->setAnimationEnd(device->getSceneManager()->getNodoFromID(1), false);
                    //device->setAnimationNumMalla(device->getSceneManager()->getNodoFromID(1), 0);
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionStandby));
                }
            }
        }

        if(device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionMuerte)){
            if(device->animationIsEnd(device->getSceneManager()->getNodoFromID(1)))
                device->setBillboardActivo(billboardGameOver, true);  
            
        }
        
        //CUANDO EL PLAYER MUERE, SI PULSA ENTER VOLVEMOS A JUGAR
        if(Game::GetInstance()->isPlayerDead()){
            //std::cout<<"kpasaklok\n";
            if(device->processInput(GLFW_KEY_ENTER)){
                //std::cout<<"kpasaklok\n";
                EventManager::getInstancia().addEvent(Event{EventType::Player_Dead});
                //auto phycmp = e->getComponent<PhysicsComponent_t>();
                //si entra aqui, quitamos el billboard de muerte
                //restablecemos la vida del player
                //lo ponemos al inicio de la zona
                //y el isplayerdead del game vuelve a ser false
                device->setBillboardActivo(billboardGameOver, false);
                hp->life = 100;
                //phycmp->x = phycmp->zonex; phycmp->z = phycmp->zonez;
                device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionStandby));
                Game::GetInstance()->setPlayerDead(false);
            }
        }
        //auto nodoWeapon = device->getSceneManager()->getNodoFromID(itemCmp->m_seleccionado); //ARREGLAR ESTO SI ES -1 POR EL NOT CHATCHED PETA
        if(device->processInput(GLFW_KEY_1)){
            EventManager::getInstancia().addEvent(Event{EventType::Input_1});
            //nodoWeapon->setVisibilidad(false);
            itemCmp->m_seleccionado = Weapons_utilities::Espada;
            //std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;

            // Desactivamos el billboard actual, activamos el nuevo y cambiamos el billboard activo(si es diferente)
            if(billboardEspada != billboardArmaActiva){
                device->setBillboardActivo(billboardEspada, true);
                device->setBillboardActivo(billboardArmaActiva, false);
                billboardArmaActiva = billboardEspada;
            }
        }

        if(device->processInput(GLFW_KEY_2)){
            EventManager::getInstancia().addEvent(Event{EventType::Input_2});
            //nodoWeapon->setVisibilidad(false);
            itemCmp->m_seleccionado = Weapons_utilities::Escudo;
            //std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;

            // Desactivamos el billboard actual, activamos el nuevo y cambiamos el billboard activo(si es diferente)
            if(billboardEscudo != billboardArmaActiva){
                device->setBillboardActivo(billboardEscudo, true);
                device->setBillboardActivo(billboardArmaActiva, false);
                billboardArmaActiva = billboardEscudo;
            }
        }

        if(device->processInput(GLFW_KEY_3)){
            EventManager::getInstancia().addEvent(Event{EventType::Input_3});
            //nodoWeapon->setVisibilidad(false);
            itemCmp->m_seleccionado = Weapons_utilities::Pocion;
            //std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;  

            // Desactivamos el billboard actual, activamos el nuevo y cambiamos el billboard activo(si es diferente)
            if(billboardPocion != billboardArmaActiva){
                device->setBillboardActivo(billboardPocion, true);
                device->setBillboardActivo(billboardArmaActiva, false);
                billboardArmaActiva = billboardPocion;
            }
        }

        if(device->processInput(GLFW_KEY_4)){
            EventManager::getInstancia().addEvent(Event{EventType::Input_4});
            //nodoWeapon->setVisibilidad(false);
            itemCmp->m_seleccionado = Weapons_utilities::Arco;
            //std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;
            if(itemCmp->weapons[Weapons_utilities::Arco] == true){      
                // Desactivamos el billboard actual, activamos el nuevo y cambiamos el billboard activo(si es diferente)
                if(billboardArco != billboardArmaActiva){
                    device->setBillboardActivo(billboardArco, true);
                    device->setBillboardActivo(billboardArmaActiva, false);
                    billboardArmaActiva = billboardArco;
                }
            }
        }

        //if(device->processInput(GLFW_KEY_5)){
        //    EventManager::getInstancia().addEvent(Event{EventType::Input_5});
        //    itemCmp->m_seleccionado = Weapons_utilities::Bomba;
        //    std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;
        //    
        //    // Desactivamos el billboard actual, activamos el nuevo y cambiamos el billboard activo(si es diferente)
        //    if(billboardBomba != billboardArmaActiva){
        //        device->setBillboardActivo(billboardBomba, true);
        //        device->setBillboardActivo(billboardArmaActiva, false);
        //        billboardArmaActiva = billboardBomba;
        //    }
        //}

        //****MOVIMIENTO****
        if(device->getSceneManager()->getNodoFromID(1)->getEntidad() != device->getAnimacion(animacionEspada) 
          && device->getSceneManager()->getNodoFromID(1)->getEntidad() != device->getAnimacion(animacionEscudo)
          && device->getSceneManager()->getNodoFromID(1)->getEntidad() != device->getAnimacion(animacionPocion)
          && device->getSceneManager()->getNodoFromID(1)->getEntidad() != device->getAnimacion(animacionArco)){
            if(device->processInput(GLFW_KEY_A)){
                //std::cout<<"me estoy moviendo\n";   
                info.direction = 1;
                direc->dirPrevia = 1;
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
                //derecha
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                    if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
                
            }
            else if(device->processInput(GLFW_KEY_D)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 2;
                direc->dirPrevia = 2;
                EventManager::getInstancia().addEvent(Event{EventType::Input_A, info});
                //izquierda
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                    if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
            } 
            if(device->processInput(GLFW_KEY_W)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 3;
                direc->dirPrevia = 3;
                EventManager::getInstancia().addEvent(Event{EventType::Input_W, info});
                //arriba
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                    if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
            }
            else if(device->processInput(GLFW_KEY_S)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 4;
                direc->dirPrevia = 4;
                EventManager::getInstancia().addEvent(Event{EventType::Input_S, info});
                //abajo
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                    if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
            }
            if(device->processInput(GLFW_KEY_A) && device->processInput(GLFW_KEY_W)){
                info.direction = 5;
                direc->dirPrevia = 5;
                info.rotation = 30;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WD, info});
                // Dirección hacia derecha-arriba
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
            }
            else if(device->processInput(GLFW_KEY_D) && device->processInput(GLFW_KEY_W)){
                info.direction = 6;
                direc->dirPrevia = 6;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WA, info});
                // Dirección hacia izquierda-arriba
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                    if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
            }
            else if(device->processInput(GLFW_KEY_A) && device->processInput(GLFW_KEY_S)){
                info.direction = 7;
                direc->dirPrevia = 7;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SD, info});
                // Dirección hacia derecha-abajo
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                    if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
            }
            else if(device->processInput(GLFW_KEY_D) && device->processInput(GLFW_KEY_S)){
                info.direction = 8;
                direc->dirPrevia = 8;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SA, info});
                //Dirección hacia izquierda-abajo
                if(!playerDead){
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionAndar));
                    if (isRunning) device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionCorrer));
                }
            }
            if(device->processInput(GLFW_KEY_LEFT_SHIFT)  || device->processInput(GLFW_KEY_RIGHT_SHIFT)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_Shift});
                if(!isRunning)
                    isRunning = true;
            }
            
            if(!device->processInput(GLFW_KEY_LEFT_SHIFT) || device->processInput(GLFW_KEY_RIGHT_SHIFT)){
                if(isRunning){
                    EventManager::getInstancia().addEvent(Event{EventType::Release_Shift});
                    isRunning = false;
                }
            }

            if(!device->processInput(GLFW_KEY_A) && !device->processInput(GLFW_KEY_S) && !device->processInput(GLFW_KEY_D) && !device->processInput(GLFW_KEY_W) && !device->processInput(GLFW_KEY_SPACE)){
                if(isRunning){
                    EventManager::getInstancia().addEvent(Event{EventType::Release_Shift});
                    isRunning = false;
                }

                if(device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionCorrer) || device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionAndar)
                || device->getSceneManager()->getNodoFromID(1)->getEntidad() == device->getAnimacion(animacionEmpujar))
                {
                    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionStandby));
                }
            }

            if(device->processInput(GLFW_KEY_SPACE)){
                input->keySpace = true;
                EventManager::getInstancia().addEvent(Event{EventType::Input_Space});
            }
        }
        

        if(device->processInput(GLFW_KEY_ESCAPE) && now - beforeInputGame >= 0.33){
                Game* game = Game::GetInstance();

                // Activamos el billboard de pause
                device->setBillboardActivo(billboardPausaActual, true);

                // Guardamos el tiempo actual
                beforeInputGame = now; 

                // Guardamos el tiempo actual
                beforeMenuPause = now;

                game->pauseTrue();
                //EventManager::getInstancia().addEvent(Event{EventType::Input_8});
        }

        //****COMPROBAMOS LA VIDA****
        
        for (unsigned int i = 0; i <= hp->maxLife/10; i++)
        {
            if(vidaPlayer/10 == i)
            {
                device->setBillboardActivo(billboardSaludActual, false);
                device->setBillboardActivo(billboardSaludActiva + i, true);
                billboardSaludActual = billboardSaludActiva + i;
            }
        }

        //************ FIN DE JUEGO **********
        if(apareceChico && now - beforeChico >= 2.0)
        {
            device->setBillboardActivo(billboardEndGame, true);

            Game* game = Game::GetInstance();
            game->pauseTrue();
        }

    }
}

//void RavenGraphics::stopWalking(EventInfo){
//    device->getSceneManager()->getNodoFromID(1)->setEntidad(device->getAnimacion(animacionStandby));
//}

void RavenGraphics::getInputControls(){
    
}


void RavenGraphics::getInputPause(){
    if(!apareceChico)
    {
        if ((device->processInput(GLFW_KEY_W) || device->processInput(GLFW_KEY_UP)) && now - beforeMenuPause >= 0.33)
        {
            // Desactivamos la pausa anterior
            device->setBillboardActivo(billboardPausaActual, false);

            if(billboardPausaActual == billboardPausaResume) billboardPausaActual = billboardPausaExit;
            else if(billboardPausaActual == billboardPausaExit) billboardPausaActual = billboardPausaResume;

            // Activamos la pausa nueva
            device->setBillboardActivo(billboardPausaActual, true);

            //pulsadaPause = true;

            // Guardamos el tiempo actual
            beforeMenuPause = now;
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Change});
        }
        else if ((device->processInput(GLFW_KEY_S) || device->processInput(GLFW_KEY_DOWN)) && now - beforeMenuPause >= 0.33)
        {
            // Desactivamos la pausa anterior
            device->setBillboardActivo(billboardPausaActual, false);

            if(billboardPausaActual == billboardPausaResume) billboardPausaActual = billboardPausaExit;
            else if(billboardPausaActual == billboardPausaExit) billboardPausaActual = billboardPausaResume;

            if(menuActivo == 6) menuActivo = 1;

            // Activamos la pausa nueva
            device->setBillboardActivo(billboardPausaActual, true);

            //pulsadaPause = true;

            // Guardamos el tiempo actual
            beforeMenuPause = now;
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Change});
        }
        
        if(device->processInput(GLFW_KEY_ENTER) && now - beforeMenuPause >= 0.33){
            if(billboardPausaActual == billboardPausaResume)
            {
                // Guardamos el tiempo actual
                beforeInputGame = now;

                // Guardamos el tiempo actual
                beforeMenuPause = now;

                // Desactivamos la pausa
                device->setBillboardActivo(billboardPausaActual, false);

                Game* game = Game::GetInstance();
                game->pauseFalse();
                EventManager::getInstancia().addEvent(Event{EventType::Menu_Select});
            }
            else if (billboardPausaActual == billboardPausaExit)
            {
                glfwSetWindowShouldClose(device->getWindow(), true);
            }
        }

        if(device->processInput(GLFW_KEY_ESCAPE) && now - beforeMenuPause >= 0.33){

            // Guardamos el tiempo actual
            beforeInputGame = now;

            // Guardamos el tiempo actual
            beforeMenuPause = now;

            // Desactivamos la pausa
            device->setBillboardActivo(billboardPausaActual, false);

            Game* game = Game::GetInstance();
            game->pauseFalse();
            EventManager::getInstancia().addEvent(Event{EventType::Menu_Back});
        }
    }

    else{
        if(device->processInput(GLFW_KEY_ENTER))
        {
            glfwSetWindowShouldClose(device->getWindow(), true);
        }
    }
    
}

//**** METODO ANYADIR ANIMACIONES *****
void RavenGraphics::addAnimations() {

    // Activamos la pantalla de carga
    device->drawLoading();
    // Animación Standby
    auto texture = device->crearTextura("media/Texturas/Personaje/chica/chica");
    animacionStandby = device->addAnimacion("media/obj/Animaciones/animacionIddle/iddle.obj", texture, 15, 20);

    // Animación Andar
    animacionAndar = device->addAnimacion("media/obj/Animaciones/andar/andar.obj", texture, 25, 21);

    // Animación Correr
    animacionCorrer = device->addAnimacion("media/obj/Animaciones/animacionCorrer/animacionCorrer.obj", texture, 35, 21);

    // Animación Herida
    animacionHerida = device->addAnimacion("media/obj/Animaciones/herida/herida.obj", texture, 18, 18);

    // Animación Muerte
    animacionMuerte = device->addAnimacion("media/obj/Animaciones/muerte/muerte.obj", texture, 20, 24);

    // Animación Empujar
    animacionEmpujar = device->addAnimacion("media/obj/Animaciones/empujar/empujar.obj", texture, 25, 25);

    // Animación Ataque espada
    texture = device->crearTextura("media/Texturas/Personaje/chicaEspada/chicaEspada");
    animacionEspada = device->addAnimacion("media/obj/Animaciones/espada/espada.obj", texture, 35, 25);

    // Animación Proteger escudo (Solo es un modelo)
    texture = device->crearTextura("media/Texturas/Personaje/chicaEscudo/chicaEscudo");
    animacionEscudo = device->addAnimacion("media/obj/Animaciones/protegerEscudo/protegerEscudo.obj", texture, 25, 1);

    // Animación Beber poción
    texture = device->crearTextura("media/Texturas/Personaje/chicaPocion/chicaPocion");
    animacionPocion = device->addAnimacion("media/obj/Animaciones/pocion/pocion.obj", texture, 15, 20);

    // Animación Ataque arco
    texture = device->crearTextura("media/Texturas/Personaje/chicaArco/chicaArco");
    animacionArco = device->addAnimacion("media/obj/Animaciones/animacionArco/animacionArco.obj", texture, 40, 25);
    
}

//*************METODOS DE ANYADIR Y BORRAR ENTIDADES****
void RavenGraphics::Addcamera() {
    //device->crearCamara(50, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(-60.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), false, -50.0, 50.0, -37.5, 37.5, -1000.0, 1000.0);
    auto posicion = device->getSceneManager()->getNodoFromID(1)->getTraslacion();
    auto camcmp = manager->getComponents<CameraComponent_t>();
    ourCamera = device->crearCamara(camcmp[0].getEntityID(), nullptr, glm::vec3(posicion.x, posicion.y, posicion.z), glm::vec3(45.f, 180.f, 0.f), glm::vec3(1.f, 1.f, 1.f), false, -50.0, 50.0, -37.5, 37.5, -1000.0, 1000.0);
    //ourCamera = device->crearCamara(camcmp[0].getEntityID(), nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), false, -50.0, 50.0, -37.5, 37.5, -1000.0, 1000.0);
}

void RavenGraphics::addEntities(EventInfo info) { 
    
    for(auto& ren : manager->getComponents<RenderComponent_t>()){
        auto* ent = manager->getEntityByID(ren.getEntityID());
        if(ent){
            auto phy = ent->getComponent<PhysicsComponent_t>();
            if(phy && ren.isVisible == true){
                auto name = ent->getName();
                name = name.substr(0, name.find("_"));
                if (ent->getEntityID() == 1)
                {
                    auto texture = device->crearTextura("media/Texturas/Personaje/chica/chica");
                    device->crearModeloAnimado(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(phy->rx,phy->ry,phy->rz), glm::vec3(1.f, 1.f, 1.f), animacionStandby);
                }
                else if( name == "SkyboxBosque")
                {
                    //std::cout << "Nombre e ID : "  << ent->getName() << " : " << ent->getEntityID() << "  Y Textura:  " << ren.texturePath.data() << std::endl;
                    device->addSkybox(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(phy->rx,phy->ry,phy->rz), glm::vec3(1.f, 1.f, 1.f), ren.modelPath.data(),
                                    "media/skybox_daylight_2/right.bmp",
                                    "media/skybox_daylight_2/left.bmp",
                                    "media/skybox_daylight_2/top.bmp",
                                    "media/skybox_daylight_2/bottom.bmp",
                                    "media/skybox_daylight_2/front.bmp",
                                    "media/skybox_daylight_2/back.bmp");
                }
                else if( name == "SkyboxHabitacion")
                {
                    //std::cout << "Nombre e ID : "  << ent->getName() << " : " << ent->getEntityID() << "  Y Textura:  " << ren.texturePath.data() << std::endl;
                    device->addSkybox(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(phy->rx,phy->ry,phy->rz), glm::vec3(1.f, 1.f, 1.f), ren.modelPath.data(),
                                    "media/sunsetflat/right.png",
                                    "media/sunsetflat/left.png",
                                    "media/sunsetflat/top.png",
                                    "media/sunsetflat/bottom.png",
                                    "media/sunsetflat/front.png",
                                    "media/sunsetflat/back.png");
                }
                else if( name == "SkyboxTutorial")
                {
                    //std::cout << "Nombre e ID : "  << ent->getName() << " : " << ent->getEntityID() << "  Y Textura:  " << ren.texturePath.data() << std::endl;
                    device->addSkybox(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(phy->rx,phy->ry,phy->rz), glm::vec3(1.f, 1.f, 1.f), ren.modelPath.data(),
                                    "media/Clear/right.png",
                                    "media/Clear/left.png",
                                    "media/Clear/top.png",
                                    "media/Clear/bottom.png",
                                    "media/Clear/front.png",
                                    "media/Clear/back.png");
                }
                else
                {
                    //std::cout << "Nombre e ID : "  << ent->getName() << " : " << ent->getEntityID() << "  Y Textura:  " << ren.texturePath.data() << std::endl;
                    auto texture = device->crearTextura(ren.texturePath.data());
                    //std::cout << "ROTACION X Y Z :  " << phy->rx << " " << phy->ry << " " << phy->rz << " " << std::endl;
                    auto ourModel = device->crearModelo(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(phy->rx,phy->ry,phy->rz), glm::vec3(1.f, 1.f, 1.f), ren.modelPath.data(), texture);
                    //if(ent->getName() == "Casa") {ourModel->setVisibilidad(false);}
                    //auto ourModel = device->crearModelo(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(0.f,0.0,0.f), glm::vec3(1.f, 1.f, 1.f), ren.modelPath.data(), texture);
                }
                
            }
        }
            device->drawLoading();
    }
    Addcamera();

    // Desactivamos la pantalla de carga
    device->desactivateLoading();
    //auto posicion = device->getSceneManager()->getNodoFromID(1)->getTraslacion();
    //auto texture = device->crearTextura("media/Texturas/Bosque/chica/chica");
    //device->crearModeloAnimado(-3, nullptr, glm::vec3(posicion.x, posicion.y, posicion.z), glm::vec3(0.f,0.f,0.f), glm::vec3(1.f, 1.f, 1.f), "media/obj/Bosque/standby75/standby75.obj", texture, 25, 75);
    //device->crearModeloAnimado(-3, nullptr, posicion, glm::vec3(0.f,0.f,0.f), glm::vec3(1.f, 1.f, 1.f), "media/obj/Bosque/Player/Player.obj", texture, 25, 2);
    //ourCofre = device->crearModelo(-1, nullptr, glm::vec3(posicion.x, posicion.y + 2.f, posicion.z), glm::vec3(0.f,0.f,0.f), glm::vec3(1.f, 1.f, 1.f), "media/obj/Bosque/Cofre.obj", texture);
    //ourCofre->setVisibilidad(false);
}

void RavenGraphics::addEntity(EventInfo info){
    //Esta funcion deberia cambiarsele el nombre porque va a ser para crear 
    //Creamos un shoot
    
    auto texture = device->crearTextura(info.ruta.data());
    device->crearModelo(info.id, nullptr, glm::vec3(info.posX,4.55872,info.posZ), glm::vec3(0.f,0.f,0.f), glm::vec3(1.f, 1.f, 1.f), info.zona.data(), texture);

    if(info.ruta == "media/Texturas/Bosque/chico/chico")
    {
        beforeChico = now;
        apareceChico = true;
    }
    
}

void RavenGraphics::setPositionWeapons(EventInfo info){
    //auto nodoWeapon = device->getSceneManager()->getNodoFromID(info.id); 
    //if(nodoWeapon){
    //    nodoWeapon->setTraslacion(glm::vec3(info.posX,info.posY,info.posZ));
    //    auto [rx,ry,rz] = info.rotationAxis;
    //    nodoWeapon->setRotacion(glm::vec3(rx,ry,rz));
    //}
    //nodoWeapon->setVisibilidad(true);
}

void RavenGraphics::removeEntities(EventInfo info){
    //Destruimos todas las entidades menos la del personaje
    device->endScene();
    device->beginScene();
}

void RavenGraphics::removeEntity(EventInfo info){
    device->getSceneManager()->getNodoFromID(info.id)->setVisibilidad(false);
    device->getSceneManager()->borrarHijo(device->getSceneManager()->getNodoFromID(info.id));
}

void RavenGraphics::addChild(EventInfo info){
    device->getSceneManager()->añadirHijo(device->getSceneManager()->getNodoFromID(info.id));
}

void RavenGraphics::setVisibilidad(EventInfo info){
    device->getSceneManager()->getNodoFromID(info.id)->setVisibilidad(info.visibilidad);
}

//*************OTROS METODOS******
bool RavenGraphics::run() {
    return !glfwWindowShouldClose(device->getWindow());
}

void RavenGraphics::renderScene() {

}

void RavenGraphics::shutEngine(){

}

void RavenGraphics::addManager(EntityManager_t& mg){
    manager = &mg;
}

void RavenGraphics::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Render_Change_Zone,std::bind(&RavenGraphics::addEntities,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Delete_Entities_Render,std::bind(&RavenGraphics::removeEntities,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Create_Shot_MG,std::bind(&RavenGraphics::addEntity,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Remove_Entity_MG,std::bind(&RavenGraphics::removeEntity,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::setWeaponsPos,std::bind(&RavenGraphics::setPositionWeapons,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::addChildNode,std::bind(&RavenGraphics::addChild,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::dead_Animation,std::bind(&RavenGraphics::animacionDead,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::herida_Animation,std::bind(&RavenGraphics::animacionPunch,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::empujar_Animation,std::bind(&RavenGraphics::animacionArrastrar,this,std::placeholders::_1)));
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Stop_Walking_Input,std::bind(&RavenGraphics::stopWalking,this,std::placeholders::_1)));
}


void RavenGraphics::checkColisions(){
    
}