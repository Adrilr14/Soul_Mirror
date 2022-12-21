#include <facade/RavenGraphics.hpp>
#include <game/sys/render.hpp>
#include <game/sys/physics.hpp>
#include <game/sys/camera.hpp>
#include <game/sys/input.hpp>
#include <game/sys/IAphysics.hpp>
#include <ecs/man/entityManager.hpp>
#include <facade/ControllerMan.hpp>
#include <game/util/gameobjectfactory.hpp>
#include <Game.hpp>

int main(){
   
    Game* game = Game::GetInstance();
    game->InitGame();
    game->MainLoop();


    /*EntityManager_t manager;
    GameOBjectFactory_t factory { manager };
    factory.createEntity(10.0f,0,0,0,"pared_1","media/z1_p1.STL");
    factory.createEntity(10.0f,0,0,0,"pared_2","media/z1_p2.STL");
    factory.createEntity(10.0f,0,0,0,"pared_3","media/z1_p3.STL");
    factory.createEntity(10.0f,0,0,0,"pared_4","media/z1_p4.STL");
    factory.createEntity(10.0f,0,0,0,"pared_5","media/z1_p5.STL");
    factory.createEntity(10.0f,0,0,0,"pared_6","media/z1_p6.STL");
    factory.createEntity(10.0f,0,0,0,"pared_7","media/z1_p7.STL");

    factory.createPlayer(10.0f,120,0,-86);
    factory.createCamera();//int32_t ax, int32_t ay, int32_t az, std::string_view nombre, std::string_view ruta
    factory.createEnemy(99,0,-67,"enemy","xd");
    RenderSystem_t<EntityManager_t> render(1920,1080,manager);
    PhysicsSystem_t<EntityManager_t> physics;
    InputSystem_t<EntityManager_t> input;
    CameraSystem_t<EntityManager_t> camera;
    IAPhySystem_t<EntityManager_t> ia;
    

    render.renderInit();
    physics.physicsInit();
    //render.renderUpdate();
    //auto& camvec = manager.getComponents<CameraComponent_t>();
    //auto* cament = manager.getEntityByID(camvec.getEntityID());
    //TODO Cambiar que en lugar de recibir el manager reciban el array de entitys
    while(render.getRun()){
        input.update(manager);
        physics.physicsUpdate(manager);
        ia.update(manager);
        render.renderUpdatePlayer(manager);
        camera.cameraTrack(manager);
        render.renderUpdate(); 
    }*/
    
    return 0;
}

