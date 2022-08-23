#pragma once

#include "Controller.hpp"
#include "../ecs/util/typealias.hpp"
#include "../ecs/man/entityManager.hpp"
#include "../Motor/MotorRaven/MotorRaven.hpp"
#include "../Motor/MotorRaven/RShader.hpp"
#include "../Motor/MotorRaven/Nodo.hpp"

#include <memory>
#include <list>
#include <cstdint> 


struct EntityManager_t;
class  MotorRaven;


struct RavenGraphics : public Controller_t{
    RavenGraphics();
    //Funciones para el motor de Irrlicht
    //Funciones para el motor de Irrlicht
    void createWindow() override;
    void beginScene() override;
    void endScene() override;
    void drawInit() override;//dibujado del init state
    void drawCredits() override;//dibujado del credits state
    void drawGame() override;//dibujado del juego
    void drawControls() override;//dibujado del controls state
    void drawPause() override;

    //metodos de actualizacion
    void cameraUpdate() override;
    void updateEntities() override;//este metodo sirve para actualizar la posicion de las entidades
    
    //metodos de input
    void getInputInit() override;
    void getInputCredits() override;
    void getInputGame() override;
    //void stopWalking(EventInfo);
    void getInputControls() override;
    void getInputPause() override;

    //metodos de anyadir y borrar entidades
    void Addcamera() override;
    void rotateCamera(MotorRaven *dev,Nodo* camera, float fdt, float speed);
    void addEntities(EventInfo) override;//crea todas las entidades que tiene el manager en ese momento
    void addAnimations() override;// crea todas las animaciones del juego
    void addEntity(EventInfo) override;//crea una unica entidad con la informacion que le llega por parametro
    void removeEntities(EventInfo) override;//borra todas las entidades de la escena
    void removeEntity(EventInfo) override;//elimina la entidad con el id que le llega por parametro
    
    //otros metodos
    bool run() override;
    void renderScene() override;
    void shutEngine() override;
    void addManager(EntityManager_t&) override;
    void addEventListeners();
    void checkColisions() override;
    void setPositionWeapons(EventInfo info);
    void addChild(EventInfo info);
    void setVisibilidad(EventInfo info);
    void moveBillboard(MotorRaven *dev);
    void moveText();
    bool menuNavegation();

    void animacionDead(EventInfo);
    void animacionPunch(EventInfo);
    void animacionArrastrar(EventInfo);

private:
    //std::unique_ptr<MotorRaven> rvMotor;
    MotorRaven* device;
    int nodesCount { 0 }; 
    bool primerDibujado { false } ;
    bool isRunning { false };
    //RShader* ourShader;
    Nodo* ourCamera;
    //Nodo* ourCofre;

    // Variables de tiempo
    int lastFPS { 0 };
    int fps { 0 };
    float frameDeltaTime { 0.f };
    double then { 0.0 };
    double now { 0.0 };
    double beforeTexture { 0.0 };
    double beforeMenuNavegation { 0.0 };
    double beforeInputGame { 0.0 };
    double beforeMenuPause { 0.0 };

    
    //Variables de ids y de segundos
    std::vector<int> ids;
    std::vector<double> segundos;
    // Variables navegación del menú
    int menuActivo { 1 }; // 1 --> Start; 2 --> Controls; 3 --> Credits; 4 --> About; 5 --> Exit; 6 --> Inside Controls; 7-11 --> Inside Credits; 12 --> Inside About; 
    //int contFPS { 0 };

    // Variables billboard de arma
    int billboardArmaActiva;
    int billboardEspada;
    int billboardEscudo;
    int billboardPocion;
    int billboardArco;
    int billboardBomba;

    // Variables billboard de salud
    int billboardSaludActual; // Variable para saber la salud actual del player
    int billboardSaludActiva; // Variable para conocer la barra de salud que hay que utilizar
    int billboardSalud10;

    // Variables billboard pociones y llaves
    int billboardPocionx1;
    int billboardPocionActual;
    int billboardLlavex1;
    int billboardLlaveActual;
    int llavesAntes {0};
    int pocionesAntes {0};

    // Variables cuadro de diálogo, menú pausa, game over y end game
    int billboardCuadroDialogo;
    int billboardPausaActual;
    int billboardPausaResume;
    int billboardPausaExit;
    int billboardGameOver;
    int billboardEndGame;

    // Posiciones animaciones en el vector
    int animacionStandby;
    int animacionAndar;
    int animacionCorrer;
    int animacionHerida;
    int animacionMuerte;
    int animacionEmpujar;
    int animacionEspada;
    int animacionEscudo;
    int animacionPocion;
    int animacionArco;

    // Fin de juego
    bool apareceChico = false;
    double beforeChico { 0.0 };

}; //facade RavenGraphics

