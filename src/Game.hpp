//#pragma once
//#include "game/sys/physics.hpp"
//#include "game/sys/camera.hpp"
//#include "game/sys/input.hpp"
//#include "game/sys/IAphysics.hpp"
//#include "game/sys/collision.hpp"
//#include "game/util/gameobjectfactory.hpp"
//#include "game/sys/shoot.hpp"
//#include "Motor/BulletEngine/BulletEngine.hpp"
//#include <memory>
////struct PhysicsSystem_t;
////struct InputSystem_t;
////struct CameraSystem_t;
////struct IAPhySystem_t;
////struct ControllerMan;
//class State;
//
//class Game{
//    public:
//        virtual ~Game(){};
//        static Game* GetInstance();
//        //void SetState(State::States stateType);
//        void InitGame();
//        void MainLoop();
//
//    private:
//        Game() = default;
//        static Game* game;
//        EntityManager_t manager;
//        std::unique_ptr<GameOBjectFactory_t> factory;
//        //EventManager eventman;
//        std::unique_ptr<CollisionSystem_t> collision;
//        std::unique_ptr<PhysicsSystem_t> physics;
//        InputSystem_t  input;
//        std::unique_ptr<CameraSystem_t> camera;
//        std::unique_ptr<ShootSystem_t> shoot;
//        std::unique_ptr<IAPhySystem_t>  ia;
//        std::shared_ptr<BulletEngine> bullet_t;
//        bool gameStarted = false;
//};
//
//

  
#pragma once
#include <game/sys/physics.hpp>
#include <game/sys/camera.hpp>
#include <game/sys/input.hpp>
#include <game/sys/IAphysics.hpp>
#include <game/sys/shoot.hpp>
#include <game/util/gameobjectfactory.hpp>
#include <State/State.hpp>
#include <facade/Controller.hpp>
#include <memory>
//struct PhysicsSystem_t;
//struct InputSystem_t;
//struct CameraSystem_t;
//struct IAPhySystem_t;
//struct ControllerMan;
struct State;

struct Game{
    public:
        Game() = default;
        ~Game(){};
        Game* GetInstance();
        //void SetState(State::States stateType);   
        void InitGame();
        void MainLoop();
        void addEventListeners();
        void setState(State::State_Type);
        void setStateChange(EventInfo);

    private:
        
        std::unique_ptr<Game> game;
        EntityManager_t manager;
        std::unique_ptr<GameObjectFactory_t> factory;
        //EventManager eventman;
        std::unique_ptr<PhysicsSystem_t> physics;
        InputSystem_t  input;
        std::unique_ptr<CameraSystem_t> camera;
        std::unique_ptr<ShootSystem_t> shoot;
        std::unique_ptr<IAPhySystem_t>  ia;
        std::unique_ptr<State> state;
        Controller_t* renderengine {nullptr};
        bool gamePaused = false;
};

