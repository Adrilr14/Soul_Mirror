//#include <game/sys/IAphysics.hpp>

#include "shoot.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/ShootComponent.hpp"
//#include <game/cmp/IAComponent.hpp>
#include "../../ecs/man/entityManager.hpp"
#include "../../EventManager/EventManager.hpp"
#include <iostream>
#include <chrono>

void ShootSystem_t::update() const{
    double pi = 3.14159265359;
    //float x,z;
    //x = z = 0;
    for(auto& shoot : manager.getComponents<ShootComponent_t>()){
        //std::cout<<"Tamanyo del vector de entidades: "<<manager.getEntities().size()<<"\n";
        auto* bala = manager.getEntityByID(shoot.getEntityID());
        if(bala && bala->template getComponent<PhysicsComponent_t>()){
            auto* phy = bala->template getComponent<PhysicsComponent_t>();
            //phy->x += 0.3
            phy->x += phy->vx * cos(shoot.angle);
            phy->z += phy->vz * sin(shoot.angle);
            //std::cout<<"posicion de la bala en X: "<<phy->x<<" y en Z: "<<phy->z<<"\n";
        }
    }
}
