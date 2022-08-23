#include <iostream>
#include "input.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/DirecComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../../ecs/man/entityManager.hpp"
//esta clase puede que sea innecesaria ya que el input lo hace el motor grafico asi que me lo puedo ahorrar

/*void InputSystem_t::addManager(EntityManager_t& man){
    manager = &man;
}*/

InputSystem_t::InputSystem_t(){
    InputSystem_t::addEventListeners();
}

//void InputSystem_t::onkeyPressed(KeySym k){
//    ms_keyboard.keyPressed(k);
//}

//void InputSystem_t::onkeyRealeased(KeySym k){
//    ms_keyboard.keyReleased(k);
//}


//FALTA HACER UN EVENT MANAGER PARA CAPTURAR LOS EVENTOS COMO POR EJEMPLO LOS DEL INPUT
//ESTO FUNCIONA PERO FALTA RECOGER LOS EVENTOS QUE ESO LO HACE EL IRRLICHT AVERIGUAR COMO

void InputSystem_t::onEvent3(Event& e){
    //std::cout << "Se ejecuta el onEvent del EventManager \n";
}

void InputSystem_t::update(){
    for(auto& inp : manager->getComponents<InputComponent_t>()){
        auto* e = manager->getEntityByID(inp.getEntityID());
        if(e && e->getComponent<PhysicsComponent_t>()){   
            //ControllerMan::p().controller().checkTeclado(e);
            //EventManager::getInstancia().showListener();
            //if(ms_keyboard.isKeyPressed(inp.key_down)){
                
            //}
        }
    }
}

void InputSystem_t::addEventListeners(){
    //EventManager::getInstancia().AddEventToListener(Event::EventType::Input_D,std::bind(&InputSystem_t::onEvent3, this, std::placeholders::_1));
    //EventManager::getInstancia().AddEventToListener(Event::EventType::Input_A,std::bind(&InputSystem_t::onEvent3, this, std::placeholders::_1));
    //EventManager::getInstancia().AddEventToListener(Event::EventType::Input_S,std::bind(&InputSystem_t::onEvent3, this, std::placeholders::_1));
    //EventManager::getInstancia().AddEventToListener(Event::EventType::Input_W,std::bind(&InputSystem_t::onEvent3, this, std::placeholders::_1));
}