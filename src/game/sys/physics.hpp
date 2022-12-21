#pragma once
#include <chrono>
#include "../../ecs/util/typealias.hpp"
#include "../../EventManager/EventManager.hpp"
#include "../../Motor/BulletEngine/BulletEngine.hpp"
struct ControllerMan;
struct EntityManager_t;

/*este sistema se encarga de cambiar el componente direccion del player, para saber a donde se va a mover
y moverlo en consecuencia a la direccion que tiene
se usa el manager de eventos para cambiar la direccion, que el jugador elige a traves del input de teclado*/
struct PhysicsSystem_t
{
    explicit PhysicsSystem_t(EntityManager_t& em,std::shared_ptr<BulletEngine> b):
    manager{em}, bullet_t(b){}
    //explicit PhysicsSystem_t() = default;
    void addManager(EntityManager_t&);
    void physicsInit() const;
    void physicsUpdate() const;
    void switchDirection(EventInfo);
    void positionChangeZone(EventInfo info);
    void addEventListeners();
    void probando(EventInfo);
private:
    //EntityManager_t* manager {nullptr};
    mutable std::chrono::time_point<std::chrono::steady_clock> now;
    mutable bool iswalking{false};
    EntityManager_t& manager;
    std::shared_ptr<BulletEngine> bullet_t;
}; //PhysicsSystem
