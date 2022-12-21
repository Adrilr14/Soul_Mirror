#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

struct PhysicsComponent_t : ComponentBase_t<PhysicsComponent_t>{
    explicit PhysicsComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};

    //xyz guardan la posicion actual
    //initxyz guardan unicamente la posicion inicial. este valor en principio no deberia modificarse una vez asignado al crear la entidad
    float   x   {0}, y  {0},  z {0};
    float   initx {0}, inity {0}, initz {0};
    float   vx  {0}, vy {0}, vz {0};
    int32_t rx 	{0}, ry {0}, rz {0}; //rotacion en x,y,z
    //float w {0}, h{0}, d{0};
};