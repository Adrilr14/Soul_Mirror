#include "Arco.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/DirecComponent.hpp"

void Arco_t::Lanzamiento(EventInfo i){
    ////Necesitamos la posicion del jugador  
    // 1º paso obtenemos el jugador

    auto personaje = manager->getComponents<InputComponent_t>()[0];
    auto entidadPersonaje = manager->getEntityByID(personaje.getEntityID());
    if(entidadPersonaje){
        auto phy = entidadPersonaje->getComponent<PhysicsComponent_t>();
        auto dir = entidadPersonaje->getComponent<DirecComponent_t>();

        EventInfo info;
        info.id = i.id;
        //Rotacion del arma
        auto rotacionArma = std::tuple<float,float,float>(90,0,0);  

        info.posX = phy->x;
        info.posY = phy->y;
        info.posZ = phy->z;
        //Direccion de la bala que va a crear 
        if(dir->dirPrevia == 1){
            info.angle = 180;
        }else if(dir->dirPrevia == 2){
            info.angle = 0;
        }else if(dir->dirPrevia == 3){
            info.angle = 90;
        }else{
            info.angle = 270;
        }
        EventManager::getInstancia().addEvent(Event{EventType::setWeaponsPos,info});
        //Creamos una nueva entidad que sea una esfera
        EventManager::getInstancia().addEvent(Event{EventType::Create_Shot, info});
    }
}