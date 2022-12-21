#pragma once
#include <cstdint> 


#include <ecs/util/typealias.hpp>
#include <facade/Controller.hpp>

struct EntityManager_t;

struct RavenGraphics : public Controller_t{
    RavenGraphics(){};
    virtual ~RavenGraphics();
    //Funciones para el motor de Irrlicht
    void createWindow() override;
    void beginScene() override;
    void getInput() override;
    void updateEntities() override;
    bool run() override;
    void renderInit() override;
    void physicsInit() override;
    void Addcamera() override;
    void cameraUpdate() override;
    void addEntities(EventInfo) override;
    void renderScene() override;
    void endScene() override;
    void shutEngine() override;
    void addManager(EntityManager_t&) override;
    void addEventListeners();
    void checkColisions() override;

}; //facade RavenGraphics

