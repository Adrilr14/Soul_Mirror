#pragma once

#include "../../facade/BulletFacade.hpp"
#include "../../game/util/ptr_manager.hpp"
#include <btBulletCollisionCommon.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <unordered_map>
#include <memory>

constexpr float gravity = -9.81f;
constexpr float widthCh = (3.1347/2);
constexpr float heightCh = 2.94421;
constexpr float lengthCh = (10.1948/2);
constexpr float dt = 1.0/420.f;

struct EventInfo;

struct BulletEngine : public BulletFacade{
    
    explicit BulletEngine() = default;
    void createWolrdSystem() override;
    void clearScene();
    void updateCollisionEngine() override;
    void createCharacter(float posX,float posY,float posZ);
    void createSword(btScalar posX,btScalar posY,btScalar posZ,float width,float height);
    bool hasCollision(std::string_view name);
    void createObjects(float posX,float posY,float posZ,float w,float h,float l,bool staticE,std::string_view) override;
    void walkingCharacter(float posX,float posY,float posZ);
    void moveKinematicObject(float x,float y,float z);
    void moveSword(float x,float y, float z);
    static void myTickCallback(btDynamicsWorld *world, btScalar timeStep);
    void addEventListeners();
    btKinematicCharacterController* getCharacter();
    btDiscreteDynamicsWorld* getWorld();

private:
    std::unique_ptr<btDefaultCollisionConfiguration> config;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> bdInterface;
    std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
    //btSequentialImpulseConstraintSolver* solver;
    std::unique_ptr<btDiscreteDynamicsWorld> world;
    //btDiscreteDynamicsWorld* world;
    std::unordered_map<btCollisionShape*,std::string> shapes;
    std::unique_ptr<btKinematicCharacterController> character;
    //btPairCachingGhostObject* m_ghostObject;
    std::unique_ptr<btPairCachingGhostObject> m_ghostObject;
  
};
