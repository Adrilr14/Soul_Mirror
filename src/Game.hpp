  
#pragma once
#include <game/sys/physics.hpp>
#include <game/sys/camera.hpp>
#include <game/sys/input.hpp>
#include <game/sys/IAphysics.hpp>
#include "game/sys/collision.hpp"
#include "game/sys/render.hpp"
#include <memory>
//struct PhysicsSystem_t;
//struct InputSystem_t;
//struct CameraSystem_t;
//struct IAPhySystem_t;
//struct ControllerMan;
class State;

class Game{
    public:
        virtual ~Game(){};
        static Game* GetInstance();
        //void SetState(State::States stateType);
        void InitGame();
        void MainLoop();

    private:
        Game() = default;
        static Game* game;
        EntityManager_t manager;
        std::unique_ptr<PhysicsSystem_t> physics;
        InputSystem_t  input;
        std::unique_ptr<CameraSystem_t> camera;
        std::unique_ptr<IAPhySystem_t>  ia;
        std::unique_ptr<CollisionSystem_t> collider;
        std::unique_ptr<RenderSystem_t> render;
        bool gameStarted = false;
};
