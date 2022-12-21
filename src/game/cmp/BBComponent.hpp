#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct BBComponent_t : ComponentBase_t<BBComponent_t>{
    explicit BBComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    int minX {-1}, maxX {1};
    int minY {-1}, maxY {1};
    int minZ {-1}, maxZ {1};
    int centerX {0}, centerY {0}, centerZ{0};

};