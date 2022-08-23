#pragma once
#include <cstdint>
#include <ecs/cmp/component.hpp>

struct MoveComponent_t : ComponentBase_t<MoveComponent_t>{
    explicit MoveComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    //este componente no tiene nada, sirve unicamente para saber qué entidades se pueden mover y hacerlo directamente en el motor grafico recorriendo este array

};