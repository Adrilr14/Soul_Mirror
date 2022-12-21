#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct DirecComponent_t : ComponentBase_t<DirecComponent_t>{
    explicit DirecComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    int dir {-1};
    int dirPrevia {-1};
    int dirCollision {-1};
};