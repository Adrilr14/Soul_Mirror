#pragma once
#include "Item.hpp"
#include "../../EventManager/EventManager.hpp"


struct Shield_t : public Item_t {
    
    void Defender(EventInfo info);
};
