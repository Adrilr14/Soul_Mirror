#pragma once
#include "Item.hpp"
#include "../../EventManager/EventManager.hpp"

struct Arco_t : public Item_t {
    
    explicit Arco_t() = default;
    virtual ~Arco_t(){};

    void Lanzamiento(EventInfo);
    void AddEventListeners();

//Variables de Clase
private:
    std::size_t municion { 10 };
    double before { -1 };
};
