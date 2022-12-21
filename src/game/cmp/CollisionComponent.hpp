#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

    //Tenemos que implementar OBB
    //La diferencia principal entre AABB Y OBB es que AABB no puede rotar mientras que OBB si
    //AABB - is Axis-Aligned Bounding Box.
    //OBB - Oriented Bounding Box. https://forum.playcanvas.com/t/whats-the-difference-between-aabb-and-obb/3725
    //Como nuestro personaje puede rotar en varias direcciones tenemos que implementar OBB.

struct BoundingBox_t {
    uint32_t xLeft  { 0 },  xRight    { 0 };
    uint32_t yUp    { 0 },  yDown     { 0 };
    uint32_t zInit  { 0 },  zFinish   { 0 };
};

struct CollisionComponent_t : ComponentBase_t<CollisionComponent_t>{
    explicit CollisionComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};
    BoundingBox_t box;
};