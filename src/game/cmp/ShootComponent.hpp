#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

struct ShootComponent_t : ComponentBase_t<ShootComponent_t>{
    explicit ShootComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};

    float angle{0};
    float baseDamage { 10.0 };
    bool right{true};
};