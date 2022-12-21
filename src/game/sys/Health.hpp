#pragma once

#include <ecs/util/typealias.hpp>

template <typename GameCTX_t>
struct HealthSystem_t{

    explicit HealthSystem_t() = default;
    constexpr void update(GameCTX_t& g) const noexcept;

}; 
