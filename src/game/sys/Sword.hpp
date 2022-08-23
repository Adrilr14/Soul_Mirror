#pragma once
#include "Item.hpp"
#include "../../game/util/Vector3D.hpp"
#include "../../EventManager/EventManager.hpp"


struct Entity_t;

struct Sword_t : public Item_t{

    explicit Sword_t() = default;
    virtual ~Sword_t(){};
    void Atacar(EventInfo info);


//Variables de clase
    double damage { 10.0 };
    double before { 0 };
};
