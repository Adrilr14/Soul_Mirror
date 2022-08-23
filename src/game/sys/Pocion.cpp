
#include "Pocion.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/HPComponent.hpp"
#include "../../EventManager/EventManager.hpp"

// GLFW library
#include <glfw3.h>
#define GLFW_INCLUDE_NONE

void Pocion_t::Beber(){
    //std::cout << "Ejecuto la funcion de beber la pocion" << std::endl;
    double now = glfwGetTime();
    if(now - before >= (15.0/20.0)){
        if(numberPotions > 0){
            auto& inpcmp = manager->getComponents<InputComponent_t>();
            auto* player = manager->getEntityByID(inpcmp[0].getEntityID());
            auto* hpcmp = player->getComponent<HPComponent_t>();
            //std::cout<<"vida antes de sumar: "<<hpcmp->life<<"\n";
            //std::cout << "NumberPotions : " << numberPotions << std::endl;
            if(hpcmp->life < 100){
                hpcmp->life += 10;
                //std::cout<<"vida despues: "<<hpcmp->life<<"\n";
                numberPotions--;
                EventManager::getInstancia().addEvent(Event{EventType::Beber});
                if(hpcmp->life > hpcmp->maxLife){
                    hpcmp->life = hpcmp->maxLife;
                }
            }
        }   
    }
}