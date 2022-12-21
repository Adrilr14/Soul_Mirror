#pragma once

#include "Controller.hpp"
#include "../Motor/MotorRaven/ravenMotor.hpp"
#include "../ecs/util/typealias.hpp"
#include "../ecs/man/entityManager.hpp"
#include "../Motor/MotorRaven/MotorRaven.hpp"
#include "../Motor/MotorRaven/RShader.hpp"
#include "../Motor/MotorRaven/Nodo.hpp"

#include <memory>
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
    void getInputControls() override;
    void getInputPause() override;

    //metodos de anyadir y borrar entidades
    void Addcamera() override;
    void rotateCamera(MotorRaven *dev,Nodo* camera, float fdt, float speed);
    void addEntities(EventInfo) override;//crea todas las entidades que tiene el manager en ese momento
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

    void worldPhysics(std::shared_ptr<BulletEngine> w) override;


private:
    //std::unique_ptr<MotorRaven> rvMotor;
    MotorRaven* device;
    int nodesCount { 0 }; 
    double then;
    double now;
    int lastFPS { 0 };
    int fps { 0 };
    float frameDeltaTime;
    bool primerDibujado { false } ;
    //RShader* ourShader;
    Nodo* ourCamera;
    //Nodo* ourCofre;
    std::shared_ptr<BulletEngine> world { nullptr };

}; //facade RavenGraphics

