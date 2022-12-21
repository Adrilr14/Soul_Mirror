#pragma once

#include <ecs/util/typealias.hpp>
#include <EventManager/EventManager.hpp>
struct ControllerMan;
struct EntityManager_t;

/*este sistema se encarga de cambiar el componente direccion del player, para saber a donde se va a mover
y moverlo en consecuencia a la direccion que tiene
se usa el manager de eventos para cambiar la direccion, que el jugador elige a traves del input de teclado*/
struct PhysicsSystem_t
{
    explicit PhysicsSystem_t(EntityManager_t& em):
    manager{em}{}
    //explicit PhysicsSystem_t() = default;
    void addManager(EntityManager_t&);
    void physicsInit() const;
    void physicsUpdate() const;
    void switchDirection(EventInfo);
    void addEventListeners();
    void probando(EventInfo);
private:
    //EntityManager_t* manager {nullptr};
    EntityManager_t& manager;
}; //PhysicsSystem
