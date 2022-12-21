#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

struct BoundingBox_t {
    
};

struct CollisionComponent_t : ComponentBase_t<CollisionComponent_t>{
    explicit CollisionComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};
    BoundingBox_t box;
};