#pragma once
#include <cstdint> 

#include <Motor/MotorRaven/ravenMotor.hpp>
#include <ecs/util/typealias.hpp>
#include <facade/Controller.hpp>

struct EntityManager_t;

struct RavenGraphics : public Controller_t{
    RavenGraphics(){};
    virtual ~RavenGraphics();
    //Funciones para el motor de Irrlicht
    void createWindow(uint32_t , uint32_t) override;
    void beginScene() override;
    void getInput() override;
    void updateEntities() override;
    bool run() override;
    void renderInit() override;
    void physicsInit() override;
    void Addcamera() override;
    void cameraUpdate() override;
    void addEntities() override;
    void renderScene() override;
    void endScene() override;
    void shutEngine() override;
    void addManager(EntityManager_t&) override;

private:
ravenMotor rm;
}; //facade RavenGraphics

