#pragma once
#include <cstdint>
#include "../../ecs/cmp/component.hpp"


//este componente seguramente sera prescindible en un futuro, es para las paredes de momento ya que el personaje y tal no tiene modelado y se carga con un addcube
struct StaticComponent_t : ComponentBase_t<StaticComponent_t>{
    explicit StaticComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    bool isFPS{false};

};