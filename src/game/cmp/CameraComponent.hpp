#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct CameraComponent_t : ComponentBase_t<CameraComponent_t>{
    explicit CameraComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    bool isFPS{false};

};