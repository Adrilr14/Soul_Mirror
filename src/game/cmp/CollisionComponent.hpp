#pragma once
#include <vector>
#include "../../ecs/cmp/component.hpp"


struct CollisionComponent_t : ComponentBase_t<CollisionComponent_t>{
    explicit CollisionComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};

    std::vector<int> pedestales; 
    int maxPedestales {0};
    Entity_t* entidadTemporal {nullptr};
};