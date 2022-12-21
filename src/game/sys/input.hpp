#pragma once
#include <ecs/util/typealias.hpp>
#include <ecs/util/keyboard.hpp>
#include <EventManager/EventManager.hpp>

struct EntityManager_t;


struct InputSystem_t 
{
    explicit InputSystem_t();
    //void addManager(EntityManager_t&);
    void onEvent3(Event& e);
    void onkeyPressed(KeySym k);
    void onkeyRealeased(KeySym k);
    void update();   
    void addEventListeners();
private:
   inline static Keyboard_t ms_keyboard{};
   EntityManager_t* manager;
};
