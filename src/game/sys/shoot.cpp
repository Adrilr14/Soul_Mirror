//#include <game/sys/IAphysics.hpp>
#include <game/sys/shoot.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/ShootComponent.hpp>
//#include <game/cmp/IAComponent.hpp>
#include <ecs/man/entityManager.hpp>
#include <EventManager/EventManager.hpp>
#include <iostream>
#include <cmath>
#include <chrono>

void ShootSystem_t::update() const{
    double pi = M_PI;
    //float x,z;
    //x = z = 0;
    for(auto& shoot : manager.getComponents<ShootComponent_t>()){
        //std::cout<<"Tamanyo del vector de entidades: "<<manager.getEntities().size()<<"\n";
        auto* bala = manager.getEntityByID(shoot.getEntityID());
        if(bala && bala->template getComponent<PhysicsComponent_t>()){
            auto* phy = bala->template getComponent<PhysicsComponent_t>();
            //phy->x += 0.3
            phy->x += cos(shoot.angle * pi / 180);
            phy->z += sin(shoot.angle * pi / 180);
            //std::cout<<"posicion de la bala en X: "<<phy->x<<" y en Z: "<<phy->z<<"\n";
        }
    }
}
//posicion player: 7.4 220.1 seta: -4.1 244.7
//El angulo total es de: -64.9449
void ShootSystem_t::updateToDestroy() const{
    for(auto& shoot : manager.getComponents<ShootComponent_t>()){
        auto* bala = manager.getEntityByID(shoot.getEntityID());
        if(bala && bala->template getComponent<PhysicsComponent_t>()){
            auto* phy = bala->template getComponent<PhysicsComponent_t>();
            if(std::abs(phy->x - phy->initx) > 80 || std::abs(phy->z - phy->initz > 80)){
                //std::cout<<"Id de la bala a destruir: "<<bala->getEntityID()<<std::endl;
                //bala->deleteEntity();
                EventInfo info;
                info.id = bala->getEntityID();
                manager.destroyEntityByID(bala->getEntityID());
                //EventManager::getInstancia().addEvent(Event{EventType::Delete_Entity_Manager,info});
                EventManager::getInstancia().addEvent(Event{EventType::Delete_Entity_Render,info});
            }
        }
    }
}

void ShootSystem_t::calculateAngle(){

}