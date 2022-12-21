#include "Shield.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"

void Shield_t::Defender(EventInfo i){
    //Creando el escudo
    //Necesitamos la posicion del jugador 
    std::cout << "Entro al menos en el defender";
    auto inpCmp = manager->getComponents<InputComponent_t>();
    auto ent = manager->getEntityByID(inpCmp[0].getEntityID());
    if(ent){
      auto phy = ent->getComponent<PhysicsComponent_t>();
        auto escudo = manager->getEntityByID(i.id);
        if(escudo){
            auto posicion = escudo->getComponent<PhysicsComponent_t>();
            posicion->x = phy->x+0.8,
            posicion->y = phy->y+1,
            posicion->z = phy->z+0.8;

            EventInfo info;
            info.id = i.id;
            info.posX = posicion->x;
            info.posY = posicion->y;
            info.posZ = posicion->z;

            //Lanzamos un evento que haga que el motor grafico ponga el escudo en su lugar para atacar
            EventManager::getInstancia().addEvent(Event{EventType::setWeaponsPos,info});

            //Ahora tenemos que comprobar que en el momento en el que haga la accion del escudo hay una colision
            EventManager::getInstancia().addEvent(Event{EventType::Collision_Shield,info});    
        }
    }
}