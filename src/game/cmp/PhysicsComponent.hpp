#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct PhysicsComponent_t : ComponentBase_t<PhysicsComponent_t>{
    explicit PhysicsComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};

    //xyz guardan la posicion actual
    //initxyz guardan unicamente la posicion inicial. este valor en principio no deberia modificarse una vez asignado al crear la entidad
    float   x   {0}, y  {0},  z {0};
    float   initx {0}, inity {0}, initz {0};
    float   vx  {0}, vy {0}, vz {0};
    float   rx 	{0}, ry {0}, rz {0}; //rotacion en x,y,z
    float   sx 	{0}, sy {0}, sz {0}; //escala en x,y,z
    float   vangular {0.0},  vlineal {0.0};//velocidad angular y lineal
    float   acangular  {0.0}, aclineal {0.0};//aceleracion angular y lineal
    static constexpr float Rozamiento{0.95};//constante de rozamiento
    static constexpr float MAXVlin{10.0};//max vlineal
    static constexpr float MAXVang{20.0};//max vangular
    static constexpr float MAXAcl{MAXVlin/0.2};//max aclineal
    static constexpr float MAXAcng{MAXVang/0.5};//max acangular
    float orientation{0.0};
    //float w {0}, h{0}, d{0};
};