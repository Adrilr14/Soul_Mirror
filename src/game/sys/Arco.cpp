#include "Arco.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/DirecComponent.hpp"
#include <glfw3.h>
double PI2 = 3.14159265359;

void Arco_t::Lanzamiento(EventInfo i){
    ////Necesitamos la posicion del jugador  
    // 1º paso obtenemos el jugador
    double now = glfwGetTime();

    if(now - before >= (25.0/40.0)){
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
            info.posY = 4.3;
            info.posZ = phy->z;
            info.shottype = 0;
            //Direccion de la bala que va a crear 
            double PI = 3.14159265359;
            if(dir->dirPrevia == 1){
                info.angle = (1/2)*PI;
                info.rotY = 90.0;
            }else if(dir->dirPrevia == 2){
                info.angle = (3/2)*PI; 
                info.rotY = -90.0;
            }else if(dir->dirPrevia == 3){
                info.angle =  PI/2;
                info.rotY = 0;
            }else if(dir->dirPrevia == 4){
                info.angle =  3*PI/2;
                info.rotY = 180;
            }else if(dir->dirPrevia == 5){
                info.angle = 45; 
                info.rotY = 45;
            }else if(dir->dirPrevia == 6){
                info.angle = 90; 
                info.rotY = -45; 
            }else if(dir->dirPrevia == 7){
                info.angle = -45; 
                info.rotY = -225;
            }else{
                info.angle = 180; 
                info.rotY = 225;
            }
            info.playerShoot = true;
            EventManager::getInstancia().addEvent(Event{EventType::setWeaponsPos,info});
            //Creamos una nueva entidad que sea una esfera
            EventManager::getInstancia().addEvent(Event{EventType::Create_Shot, info});

            EventManager::getInstancia().addEvent(Event{EventType::Soltar_Flecha});
            before = now;
        }
    }
}