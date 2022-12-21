#pragma once
#include <string_view>
#include <cstdint>
#include "../../EventManager/EventManager.hpp"
#include "../../Motor/BulletEngine/BulletEngine.hpp"

//Fordward declaration
struct EntityManager_t;
struct Entity_t;
struct GameObjectFactory_t {
    explicit GameObjectFactory_t(EntityManager_t& em,std::shared_ptr<BulletEngine>& b) : m_EntMan(em), bulletEngine_t(b) {

    }
    void createPlayer(float,float,float,const std::string_view,const std::string_view) const;
    void createStaticEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const;
    void createNonStaticEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const;
    void createStaticEntityNonRender(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel) const;
    void createEnemy(float,float,float,const std::string_view, const std::string_view, const std::string_view,int type) const;
    void createShot(EventInfo info);
    void createCamera();
    void createWeapons(const std::string_view name,const std::string_view ruta,const std::string_view texture) const; 
    void readLevel(EventInfo) noexcept;
    void addEventListeners();
    void prueba(EventInfo);
private:
    EntityManager_t& m_EntMan;
    std::shared_ptr<BulletEngine>& bulletEngine_t;
};


