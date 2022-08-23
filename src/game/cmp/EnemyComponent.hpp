#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"

struct EnemyComponent_t : ComponentBase_t<EnemyComponent_t>{
    explicit EnemyComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};

    //Tendre que hacer un enum con los tipos de enemigo que existen
    //Para asi poder hacer una accion o otra porque el puercoespin 
    //no puede morir
    double damage { 0.0 };
};