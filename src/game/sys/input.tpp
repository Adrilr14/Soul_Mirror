#include <game/sys/input.hpp>
#include <iostream>
#include <game/cmp/RenderComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/PhysicsComponent.hpp>

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::onkeyPressed(KeySym k){
    ms_keyboard.keyPressed(k);
}

template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::onkeyRealeased(KeySym k){
    ms_keyboard.keyReleased(k);
}

//FALTA HACER UN EVENT MANAGER PARA CAPTURAR LOS EVENTOS COMO POR EJEMPLO LOS DEL INPUT
//ESTO FUNCIONA PERO FALTA RECOGER LOS EVENTOS QUE ESO LO HACE EL IRRLICHT AVERIGUAR COMO
template <typename GameCTX_t>
void InputSystem_t<GameCTX_t>::update(GameCTX_t& g) const{
    for(auto& inp : g.template getComponents<InputComponent_t>()){
        auto* e = g.getEntityByID(inp.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){   
            ControllerMan::p().controller().checkTeclado(e);
            //if(ms_keyboard.isKeyPressed(inp.key_left)){
            //    std::cout << "toca la left" << std::endl;
            //}
        }
    }
}