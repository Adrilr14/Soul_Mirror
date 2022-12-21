#include <game/sys/IAphysics.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/IAComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <ecs/man/entityManager.hpp>
#include <iostream>
#include <cmath>

void IAPhySystem_t::addManager(EntityManager_t& man){
    //manager = &man;
}

void IAPhySystem_t::update() const{
    float x,y,z,x2,y2,z2;//estas variables van a ser la posicion del player y de la entidad, para hacer un calculo del rango posteriormente
    //xyz el player, x2,y2,z2 el enemigo
    //voy a sacar primero la posicion del player
    /*puedo usar el direccomponent porque en principio solo lo va a tener el player, si esto cambiara
    se puede hacer un componente que sea player, y asi no hay ninguna duda*/
    
    for(auto& player : manager.getComponents<InputComponent_t>()){
        auto* e = manager.getEntityByID(player.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phy = e->template getComponent<PhysicsComponent_t>(); 
            x = phy->x; y = phy->y; z = phy->z; 
        }
    }

    for(auto& ia : manager.getComponents<IAComponent_t>()){
        auto* e = manager.getEntityByID(ia.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            //std::cout<<"la entity existe y tiene physics\n";
            auto* phy = e->template getComponent<PhysicsComponent_t>(); 
            x2 = phy->x; y2 = phy->y; z2 = phy->z;
            //voy a calcular la distancia en los ejes X-Z entre el jugador y el enemigo
            //hay que tener en cuenta los 4 casos posibles: izquierda arriba, izquierda abajo, derecha arriba y derecha abajo
            //miro primero en el eje X
            bool& repos = e->template getComponent<IAComponent_t>()->reposition;
            float rangex = std::abs(x-x2);
            float rangez = std::abs(z-z2);
            if(rangex <= 15 && rangez <= 15 && !repos){
                if(x < x2)
                    phy->x -= 0.2;
                else if(x > x2)//si entra aqui significa que el player esta a la derecha del enemigo
                    phy->x += 0.2;

                if(z < z2)//si entra aqui significa que el player esta abajo del enemigo
                    phy->z -= 0.2;
                else if(z > z2)
                    phy->z += 0.2; 
            }
            //ahora tengo que tratar de reposicionarlo
            float disx = std::abs(x2 - phy->initx);
            float disz = std::abs(z2 - phy->initz);
            if(disx >=15 || disz >= 15)
                repos = true;
            
            if(repos){
                if(x2 < phy->initx)
                    phy->x += 0.2;
                else if(x2 > phy->initx)
                    phy->x -= 0.2;

                if(z2 < phy->initz)
                    phy->z += 0.2;
                else if(z2 > phy->initz)
                    phy->z -= 0.2; 
                
                if(phy->x == phy->initx && phy->z == phy->initz)
                    repos = false;
            }
        }    
    }       
}
    
