#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct DynamicComponent_t : ComponentBase_t<DynamicComponent_t>{
    explicit DynamicComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    //El componente Dnamic Objects nos dira si son objetos por ejemplo como
    //el cofre, las llaves, las puertas,etc...
};