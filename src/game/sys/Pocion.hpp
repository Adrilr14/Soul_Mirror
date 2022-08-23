#pragma once
#include "Item.hpp"

struct Entity_t;

struct Pocion_t : public Item_t{

    explicit Pocion_t() = default;
    //virtual ~Pocion_t(){};
    void Beber();


//Variables de clase
    int hp_valor { 10 };
    int numberPotions { 0 };
    double before;
};
