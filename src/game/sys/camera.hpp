#pragma once

#include <cstdint>
#include <ecs/util/typealias.hpp>
#include <facade/RavenGraphics.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/CameraComponent.hpp>

struct ControllerMan;

struct EntityManager_t;

struct CameraSystem_t{
    explicit CameraSystem_t(EntityManager_t& em):
    manager(em){}
    void addManager(EntityManager_t&);
    void cameraUpdate() const;
    void changeView();//este metodo igual no se usa nunca, no se 
    
    private:
        EntityManager_t& manager;
};  //RenderSystem_t
