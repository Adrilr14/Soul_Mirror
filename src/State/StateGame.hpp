#pragma once
#include "State.hpp"
#include "../game/sys/physics.hpp"
#include "../game/sys/camera.hpp"
#include "../game/sys/IAphysics.hpp"
#include "../game/sys/shoot.hpp"
#include "../game/sys/collision.hpp"
#include "../game/util/gameobjectfactory.hpp"
#include <memory>

struct RavenSound;
struct EntityManager_t;
struct Controller_t;

struct StateGame : public State{
    explicit StateGame();
    void addEventListeners();
    void playSoundEvent(EventInfo);
    void update() override;
    void getInput() override;
    void draw() override;
    void endScene() override;
    void playEvent();

    private:
        Controller_t* renderengine {nullptr};
        RavenSound* soundSystem {nullptr};
        EntityManager_t manager;
        std::unique_ptr<GameObjectFactory_t> factory;
        //EventManager eventman;
        std::unique_ptr<PhysicsSystem_t> physics;
        std::unique_ptr<CameraSystem_t> camera;
        std::unique_ptr<ShootSystem_t> shoot;
        std::unique_ptr<IAPhySystem_t>  ia;
        std::unique_ptr<CollisionSystem_t> collision;
        std::shared_ptr<BulletEngine> bullet_t;
};