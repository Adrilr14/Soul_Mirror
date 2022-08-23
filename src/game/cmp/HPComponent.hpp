#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct HPComponent_t : ComponentBase_t<HPComponent_t>{
    explicit HPComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    float life {100};
    float maxLife {100};
};