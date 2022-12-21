#pragma once
#include <string_view>
#include <cstdint>


//Fordward declaration
struct EntityManager_t;
struct Entity_t;

struct GameOBjectFactory_t {
    explicit GameOBjectFactory_t(EntityManager_t& em):
    m_EntMan(em){}
    Entity_t& createEntity(float whd,int32_t ax,int32_t ay,int32_t az,const std::string_view nombre,const std::string_view ruta) const;
    void createPlayer(float,float,float, const std::string_view) const;
    void createStaticEntity(const std::string_view,const std::string_view, const std::string_view) const;
    void createEnemy(int32_t, int32_t,int32_t,const std::string_view, const std::string_view, const std::string_view) const;
    void createCamera();
    void readLevel(std::string_view);
private:
    EntityManager_t& m_EntMan;
};


