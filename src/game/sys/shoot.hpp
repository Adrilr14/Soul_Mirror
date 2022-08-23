#pragma once

#include <cstdint>
#include "../../ecs/util/typealias.hpp"
#include "../../facade/RavenGraphics.hpp"

struct ControllerMan;
struct EntityManager_t;
struct ShootSystem_t
{
    explicit ShootSystem_t(EntityManager_t& em):
    manager(em){}
    void addManager(EntityManager_t&);
    void update() const;
    
    private:
        EntityManager_t& manager;
};  
