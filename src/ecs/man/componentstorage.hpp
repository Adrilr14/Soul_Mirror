#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>
#include <iostream>
#include "../cmp/component.hpp"
#include "../util/typealias.hpp"


struct ComponentVectorBase_t {
    virtual ~ComponentVectorBase_t() = default;
    virtual Component_t* deleteCmpByID(EntityID_t eid) = 0;
};

template <typename CMP_t>
struct ComponentVector_t : ComponentVectorBase_t{
    Vec_t<CMP_t> components;

    constexpr auto findComponentIteratirByID(EntityID_t eid) noexcept {
        //TODO!! Linear Search! Cambiar
        std::optional itopt = std::find_if(components.begin(),components.end(),
        [&eid](CMP_t& cmp){ return cmp.getEntityID() == eid; });

        if(*itopt == components.end()){
            itopt.reset();
        }
        return itopt;
    }

    Component_t* deleteCmpByID(EntityID_t eid) override final{
        auto itopt = findComponentIteratirByID(eid);
        if(!itopt){
            return nullptr;
        }
        
        auto it = *itopt;
        if(it+1 != components.end()){
            *it = components.back(); //Posible problema: Mirar el video de Fran V2 S16 minuto 59:00 en adelante
        }

        components.pop_back();
        return it.base();
        //TODO cambiar la forma de borrar el componente de la entidad
        //components.erase(it);
    }
};


struct ComponentStorage_t {
    //constructor
    explicit ComponentStorage_t(std::size_t initsize)
    : m_initialSize(initsize){
    
    } 


    template<typename CMP_t>
    CMP_t& createComponent(EntityID_t eid){
        auto& v = getComponents<CMP_t>();
        auto& cmp = v.emplace_back(eid);
        return cmp;
    }


    template<typename CMP_t>
    Vec_t<CMP_t>& createComponentVector(){
        auto typeID = CMP_t::getComponentTypeID();
        auto v = std::make_unique<ComponentVector_t<CMP_t>>();
        v->components.reserve(m_initialSize);
        auto* vecptr = v.get();
        m_componentVector[typeID] = std::move(v);
        return vecptr->components;
    }

    template <typename CMP_t>
    Vec_t<CMP_t>& getComponents(){
        Vec_t<CMP_t>* comvec { nullptr };
        auto typeID = CMP_t::getComponentTypeID();
        auto it = m_componentVector.find(typeID);
        if( it != m_componentVector.end()){
            auto* v = dynamic_cast<ComponentVector_t<CMP_t>*>(it->second.get());
            if(v != nullptr){ //Si el dynamic cast falla devuelve un null asi q hay q comprobarlo
                comvec = &(v->components);
            } 
        }else{  
                comvec = &createComponentVector<CMP_t>();
        }
        return *comvec;
    }

    template <typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const {
        Vec_t<CMP_t>* comvec { nullptr };
        auto typeID = CMP_t::getComponentTypeID();
        auto it = m_componentVector.find(typeID);
        if( it != m_componentVector.end()){
            auto* v = dynamic_cast<ComponentVector_t<CMP_t>*>(it->second.get());
            if( v != nullptr){
                comvec = &(v->components);   
            }
        }else{
            throw " a "; 
        }
        return *comvec;
    }

    void clearAll(){
        m_componentVector.clear();
    }

    inline Component_t* deleteCmpByTypeID(ComponentTypeID_t cid, EntityID_t eid){
        std::cout << "deleteCmpByTypeID" << std::endl;
        auto it = m_componentVector.find(cid);
        if(it == m_componentVector.end()){
            return nullptr; //TODO Error management
        }
        return it->second->deleteCmpByID(eid);

    }

    size_t size(){
        return m_componentVector.size();
    }
    //elimino estas operaciones canonicas porque no me interesa tenerlas
    ComponentStorage_t(const ComponentStorage_t&)               = delete;
    ComponentStorage_t(ComponentStorage_t&&)                    = delete;
    ComponentStorage_t& operator=(const ComponentStorage_t&)    = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&)         = delete;
    
    private:
        Hash_t<ComponentTypeID_t, std::unique_ptr<ComponentVectorBase_t>> m_componentVector;
        std::size_t m_initialSize { 50 };
};