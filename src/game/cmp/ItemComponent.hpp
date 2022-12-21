#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

struct ItemComponent_t : ComponentBase_t<ItemComponent_t>{
    explicit ItemComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    

};