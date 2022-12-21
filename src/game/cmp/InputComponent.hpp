#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>
///#include <X11/keysym.h>
///#include <X11/X.h>

struct InputComponent_t : ComponentBase_t<InputComponent_t>{
    explicit InputComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};

    //KeySym key_up       {XK_w};
    //KeySym key_left     {XK_a};
    //KeySym key_right    {XK_d};
    //KeySym key_down     {XK_s};
};