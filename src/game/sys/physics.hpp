#pragma once

#include <ecs/util/typealias.hpp>

struct ControllerMan;
struct EntityManager_t;

struct PhysicsSystem_t
{
    explicit PhysicsSystem_t(EntityManager_t& em):
    manager(em){}
    //explicit PhysicsSystem_t() = default;
    void addManager(EntityManager_t&);
    void physicsInit() const;
    void physicsUpdate() const;
private:
    //EntityManager_t* manager {nullptr};
    EntityManager_t& manager;
}; //PhysicsSystem
