#include <game/sys/camera.hpp>
#include <facade/ControllerMan.hpp>
#include <iostream>

void CameraSystem_t::addManager(EntityManager_t& man){
    //manager = &man;
}

void CameraSystem_t::cameraUpdate() const{
    //std::cout<<"entro al camara update";
    float x,y,z = 0;
    //si al final la camara va a poder cambiarse entre 1 y 3 persona, habra que modificar esto para que la posicion de la camara sea la misma que la del player
    //primero saco la posicion del player actual, accediendo al array de input, que es solo el player, y de ahi sacando esa entity en concreto
    //auto& e = manager->getEntities()[0];
    //if(e.template getComponent<InputComponent_t>())
      //  std::cout<<e.getEntityID();
    //auto&xd = manager->getComponents<InputComponent_t>();
    auto& inpcmp = manager.getComponents<InputComponent_t>();
    auto* player = manager.getEntityByID(inpcmp[0].getEntityID());
    if(player && player->template getComponent<PhysicsComponent_t>()){
        auto* phycmp = player->template getComponent<PhysicsComponent_t>();
        x = phycmp->x;
        y = 40; //este es un valor por defecto
        z = phycmp->z - 15;
    }
    //en principio ya tengo la posicion que va a tener la camara, ahora tengo que encontrar la entidad con el cmp "Camara" y asignarla a traves de su physicscmp
    auto& camcmp = manager.getComponents<CameraComponent_t>();
    auto* cament = manager.getEntityByID(camcmp[0].getEntityID());
    if(cament && cament->template getComponent<PhysicsComponent_t>()){
        auto* phycmp = cament->template getComponent<PhysicsComponent_t>();
        phycmp->x = x;
        phycmp->y = y;
        phycmp->z = z;
    }
    //delete player;
    //delete cament;
    //ControllerMan::p().controller().cameraTrack(cament);
    
}