#pragma once
#include <cstdint>
#include "../util/typealias.hpp"

struct Component_t{
    explicit Component_t(EntityID_t eid) 
    : entityID {eid}
    {}

    virtual ~Component_t() = default;
    constexpr ComponentID_t   getCompId()     const noexcept {return ComponentID;};
    constexpr EntityID_t      getEntityID()   const noexcept {return entityID;};
    
    protected:
    inline static ComponentTypeID_t nextTypeID { 0 };
    
    private:
        ComponentID_t ComponentID {++nextID};
        EntityID_t entityID;
        inline static std::size_t nextID {0}; 
};

template <typename TYPE>
struct ComponentBase_t : Component_t {
    explicit ComponentBase_t(EntityID_t eid)
    : Component_t(eid) {}
    virtual ~ComponentBase_t() = default;
    static ComponentTypeID_t getComponentTypeID() noexcept{
        static ComponentTypeID_t typeID { ++nextTypeID };
        return typeID;
    }
};