#pragma once
#include <unordered_map>
#include <vector>


template<typename T>
using Vec_t = std::vector<T>;
template<typename KEY_t, typename VALUE_t>
using Hash_t = std::unordered_map<KEY_t,VALUE_t>;


using EntityID_t    = std::size_t;
using ComponentID_t = std::size_t;
using ComponentTypeID_t = std::size_t;