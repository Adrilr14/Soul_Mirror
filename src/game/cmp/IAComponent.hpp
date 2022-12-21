#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

enum IAType{
    fuzzylogic,
    bhtree,
    stbehav,
    simple
};

enum AIActions{
    atack,
    def,
    move,
    look
};

//hay varios tipos de IA (fuzzy logic, behaviour tree... igual hay que darle mas vueltas a esto)
struct IAComponent_t : ComponentBase_t<IAComponent_t>{
    explicit IAComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    bool reposition {false};//esto para saber si le toca reposicionarse o no
    IAType type{simple};  
    AIActions actions;//esto no se si tiene sentido, habra que verlo
};