#include <game/sys/physics.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <ecs/man/entityManager.hpp>
#include <iostream>



void PhysicsSystem_t::addManager(EntityManager_t& man){
    //manager = &man;
}

void PhysicsSystem_t::physicsInit() const{
    //ControllerMan::p().controller().physicsInit();
}


void PhysicsSystem_t::physicsUpdate() const{
    //std::cout<<"entro al physics";
     //cojo la primera entidad, que es el personaje
    //std::cout<<"Direccion actual:"<<e.direcc->dir<<std::endl;
    //std::cout<<"Velocidad actual X:"<<e.physics->vx<<" Velocidad actual Z:"<<e.physics->vz<<std::endl;
    //compruebo que ni la direccion ni el physics sean nullptr
    //1:derecha 2:izquierda 3:arriba 4:abajo 5:arriba derecha 6:arriba izquierda 7:abajo derecha 8:abajo izquierda
     
    for(auto& phy : manager.getComponents<PhysicsComponent_t>()){
        auto* e = manager.getEntityByID(phy.getEntityID());
        if(e && e->template getComponent<DirecComponent_t>()){  
            auto* dircmp = e->template getComponent<DirecComponent_t>();
            switch(e->template getComponent<DirecComponent_t>()->dir){
            //de 1 a la 4 direcciones en un solo eje
            case 1://derecha
                phy.x += phy.vx;
                //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
                break;

            case 2://izquierda
                phy.x -= phy.vx;
                //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
                break;

            case 3://arriba
                phy.z += phy.vz;
                break;

            case 4://abajo
                phy.z -= phy.vz;
                break;
            //movimientos en diagonal
            case 5://arriba derecha
                phy.z += phy.vz;
                phy.x += phy.vx;
                break;

            case 6://arriba izquierda
                phy.z += phy.vz;
                phy.x -= phy.vx;
                break;

            case 7://abajo derecha
                phy.z -= phy.vz;
                phy.x += phy.vx;
                break;

            case 8://abajo izquierda
                phy.z -= phy.vz;
                phy.x -= phy.vx;
                break;
            }
            //std::cout<<"Posicion en X: "<<phy.x<<" Posicion en Z: "<<phy.z<<"\n";
            dircmp->dir = -1;
        }
        
    }
    
}