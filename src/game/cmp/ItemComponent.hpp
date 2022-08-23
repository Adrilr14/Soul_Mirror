#pragma once
#include <vector>
#include <cstdint>
#include "../../ecs/cmp/component.hpp"
#include "../util/typealias.hpp"
#include "../sys/Sword.hpp"
#include "../sys/Shield.hpp"
#include "../sys/Arco.hpp"
#include "../sys/Key.hpp"
#include "../sys/Pocion.hpp"


struct ItemComponent_t : ComponentBase_t<ItemComponent_t>{
    explicit ItemComponent_t(std::size_t eid,std::size_t sizeVector = 6)
    :   ComponentBase_t(eid)
    {
        inventario.reserve(sizeVector);
    };
    //Le hacemos un reserve de 6 Items
    //Los items tendran siempre las mismas posiciones
    // Item 1 :  (Posicion 0 del vector) -> Espada
    // Item 2 :  (Posicion 1 del vector) -> Escudo
    // Item 3 :  (Posicion 2 del vector) -> Arco
    // Item 4 :  (Posicion 3 del vector) -> Bomba
    // Item 5 :  (Posicion 4 del vector) -> Pocion
    // Item 6 :  (Posicion 5 del vector) -> Llaves puertas
    void AddItem(Item_t newItem){
        //Comprobamos el nuevo Item que clase es 
        inventario.push_back(newItem);
    }   

    void AddSword(const Sword_t& s){
        sword = s;
    }

    void AddShield(const Shield_t& s){
        shield = s;
    }

    void AddArc(const Arco_t& s){
        arc = s;
    }

    void AddPotion(const Pocion_t& p){
        potion = p;
    }

    void executeAction(EventInfo info){ 
        if(m_seleccionado == Weapons_utilities::Espada){
            sword.Atacar(info);
        }else if(m_seleccionado == Weapons_utilities::Escudo){
            shield.Defender(info);
        }else if(m_seleccionado == Weapons_utilities::Arco){
            arc.Lanzamiento(info);
        }else if(m_seleccionado == Weapons_utilities::Pocion){
            potion.Beber();
        }
        //Primero de todo miramos que item esta seleccionado
        //std::cout << "El seleccionado " << m_seleccionado;
        //std::cout << "El size: " << inventario.size() << std::endl;
        //auto weaponSelected = inventario[0];
        //////Ahora hacemos un switch para saber la conversion que hay q hacer
        //
        //if(m_seleccionado == Weapons_utilities::Espada){
        //    auto casted = static_cast<Sword_t&>(weaponSelected);
        //    casted.Atacar(info);
        //}//else if(m_seleccionado == 1){
        //    auto casted = static_cast<Shield_t&>(weaponSelected);
        //}else if(m_seleccionado == 2){
        //    auto casted = static_cast<Arco_t&>(weaponSelected);
        //    casted.Lanzamiento();
        //}
    }

    
    //Creamos un vector de items para saber que items tiene en un principio 
    //nuestro personaje
    std::vector<Item_t> inventario;
    Sword_t sword;
    Shield_t shield;
    Arco_t arc;
    Key keys;
    Pocion_t potion;  //espada //escudo //pocion //arco
    bool weapons[4] = {true,true,true,false};
    Weapons_utilities m_seleccionado { Weapons_utilities::Espada };
};