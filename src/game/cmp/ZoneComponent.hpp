#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>
//lo mas seguro es que este cmp no tenga uso
struct ZoneComponent_t : ComponentBase_t<ZoneComponent_t>{
    explicit ZoneComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    int zone{1};

};