#pragma once
#include "Item.hpp"
#include "../../EventManager/EventManager.hpp"


struct Entity_t;

struct Sword_t : public Item_t{

    explicit Sword_t() = default;
    virtual ~Sword_t(){};
    void Atacar(EventInfo info);


//Variables de clase
    double damage { 0.5 };
};
