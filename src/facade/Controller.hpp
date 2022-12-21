#pragma once

#include <cstdint>
#include "../ecs/cmp/entity.hpp"
#include "../ecs/util/typealias.hpp"
#include "../ecs/man/entityManager.hpp"
#include "../Motor/BulletEngine/BulletEngine.hpp"


struct EventInfo;

using VecEntities_t = Vec_t<Entity_t>;


struct Controller_t
{
    virtual ~Controller_t() = default;
    //metodos de dibujado
    virtual void createWindow() = 0;//no se usa porque la ventana ya la crea el constructor, la dejo por si acaso
    virtual void beginScene() = 0;//llama a beginscene de irrlicht
    virtual void endScene() = 0;//llama a endscene de irrlicht
    virtual void drawInit() = 0;//dibujado del init state
    virtual void drawCredits() = 0;//dibujado del credits state
    virtual void drawGame() = 0;//dibujado del juego
    virtual void drawControls() = 0;//dibujado del controls state
    virtual void drawPause() = 0;//la pausa no es un estado como tal, pero hay que dibujar cosas

    //metodos de actualizacion
    virtual void cameraUpdate() = 0;
    virtual void updateEntities() = 0;//este metodo sirve para actualizar la posicion de las entidades
    
    //metodos de input
    virtual void getInputInit() = 0;
    virtual void getInputCredits() = 0;
    virtual void getInputGame() = 0;
    virtual void getInputControls() = 0;
    virtual void getInputPause() = 0;//la pausa como tal no es un estado, pero hay que recibir su input igualmente

    //metodos de anyadir y borrar entidades
    virtual void Addcamera() = 0;
    virtual void addEntities(EventInfo) = 0;//crea todas las entidades que tiene el manager en ese momento
    virtual void addEntity(EventInfo) = 0;//crea una unica entidad con la informacion que le llega por parametro
    virtual void removeEntities(EventInfo) = 0;//borra todas las entidades de la escena
    virtual void removeEntity(EventInfo) = 0;//elimina la entidad con el id que le llega por parametro
    
    //otros metodos
    virtual bool run() = 0;
    virtual void renderScene() = 0;
    virtual void shutEngine() = 0;
    virtual void addManager(EntityManager_t&) = 0;
    virtual void checkColisions() = 0;
    virtual void worldPhysics(std::shared_ptr<BulletEngine> w) = 0;

    protected:
        EntityManager_t* manager {nullptr};
};
