#pragma once

#include <cstdint>
#include <ecs/cmp/entity.hpp>
#include <ecs/util/typealias.hpp>
#include <ecs/man/entityManager.hpp>
struct EventInfo;

using VecEntities_t = Vec_t<Entity_t>;


struct Controller_t
{
    virtual ~Controller_t() = default;
    virtual void createWindow() = 0; //este solo crea la ventana y recoge las instancias del video driver, scene manager y guienvironment;
    virtual void beginScene() = 0;
    virtual void getInput() = 0;
    virtual void updateEntities() = 0;//este metodo sirve para actualizar la posicion de las entidades
    virtual bool run() = 0;
    virtual void renderInit() = 0;
    virtual void physicsInit() = 0;
    virtual void Addcamera() = 0;
    virtual void cameraUpdate() = 0;
    virtual void addEntities(EventInfo) = 0;
    virtual void renderScene() = 0;
    virtual void endScene() = 0;
    virtual void shutEngine() = 0;
    virtual void addManager(EntityManager_t&) = 0;
    virtual void checkColisions() = 0;
    
    protected:
        EntityManager_t* manager {nullptr};
};
