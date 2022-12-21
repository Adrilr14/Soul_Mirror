#pragma once
#include <string_view>
#include <cstdint>
#include <EventManager/EventManager.hpp>

//Fordward declaration
struct EntityManager_t;
struct Entity_t;
struct GameOBjectFactory_t {
    explicit GameOBjectFactory_t(EntityManager_t& em) : m_EntMan{em}{}
    void createPlayer(float,float,float, const std::string_view,const std::string_view) const;
    void createStaticEntity(float,float,float,float,float,float,const std::string_view,const std::string_view, const std::string_view) const;
    void createEnemy(float,float,float,const std::string_view, const std::string_view, const std::string_view) const;
    void createCamera();
    void readLevel(EventInfo) noexcept;
    void addEventListeners();
    void prueba(EventInfo);
private:
    EntityManager_t& m_EntMan;
};


