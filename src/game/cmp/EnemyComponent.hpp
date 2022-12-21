#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct EnemyComponent_t : ComponentBase_t<EnemyComponent_t>{
    explicit EnemyComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};


};