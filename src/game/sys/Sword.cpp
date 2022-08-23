#include "Sword.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include <glfw3.h>
#include <iostream>

//Función para atacar a los enemigos
void Sword_t::Atacar(EventInfo i) {
    
    //Creando la espada
    //Necesitamos la posicion del jugador 

    double now = glfwGetTime();

    auto inpCmp = manager->getComponents<InputComponent_t>();
    auto ent = manager->getEntityByID(inpCmp[0].getEntityID());
    if(ent){
        auto phy = ent->getComponent<PhysicsComponent_t>(); 
        if(now - before >= (25.0/35.0)){
            //std::cout << "Estoy entrando en el if";
            auto espada = manager->getEntityByID(i.id);
            if(espada){
            //auto posicion = espada->getComponent<PhysicsComponent_t>();
            //posicion->x = phy->x+0.8,
            //posicion->y = phy->y+1.5,
            //posicion->z = phy->z-1;

            //auto rotacionArma = std::tuple<float,float,float>(90,0,0);

            EventInfo info;
            info.id = i.id;
            //info.posX = posicion->x;
            //info.posY = posicion->y;
            //info.posZ = posicion->z;
            //info.rotationAxis = rotacionArma;

            ////Lanzamos un evento que haga que el motor grafico ponga la espada en su lugar para atacar
            //EventManager::getInstancia().addEvent(Event{EventType::setWeaponsPos,info});

            //Ahora tenemos que comprobar que en el momento en el que haga la accion del espadazo hay una colision
            EventManager::getInstancia().addEvent(Event{EventType::Collision_Sword,info});  

            EventManager::getInstancia().addEvent(Event{EventType::Espada_No_Colision});
            before = now;  
            }
        }
    }
}

