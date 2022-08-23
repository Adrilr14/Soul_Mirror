#pragma once
#include <string_view>
#include <cstdint>
#include "../../EventManager/EventManager.hpp"


//Fordward declaration
struct EntityManager_t;
struct Entity_t;
struct GameObjectFactory_t {
    explicit GameObjectFactory_t(EntityManager_t& em,std::string_view r,std::string_view z) : m_EntMan(em), ruta(r), zona(z)  {

    }
    void createPlayer(float,float,float,float w,float h,float l,const std::string_view,const std::string_view) const;
    void createStaticEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const;
    void createColliderEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const;
    void createColliderNonEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const;
    void createNonStaticEntity(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel, const std::string_view rutatexture) const;
    void createStaticEntityNonRender(float x,float y,float z,float rx,float ry,float rz,float width,float height,float length,const std::string_view nombre, 
    const std::string_view rutamodel) const;
    void createObjectsGeneric(float x, float y, float z,float rx, float ry, float rz, float width,float height,float length , const std::string_view nombre, const std::string_view rutamodel, 
    const std::string_view rutatexture,bool staticValue, bool collisionableValue, bool renderizableValue) const;
    void createEnemy(float x, float y, float z, float rx, float ry, float rz, float width,float height,float length , const std::string_view nombre, const std::string_view rutamodel, const std::string_view rutatexture,int type,int typerizo) const;
    void createShot(EventInfo info);
    void createCamera();
    std::size_t createWeapons(const std::string_view name) const; 
    void setRuta(EventInfo info) noexcept;
    void setZona(EventInfo info) noexcept;
    void readLevel(EventInfo) noexcept;
    void createEspejo(EventInfo);
    void createDeku(EventInfo);
    void addEventListeners();
    void prueba(EventInfo);
private:
    EntityManager_t& m_EntMan;
    std::string ruta; //Ruta para saber que zonas tiene que cargar.
    std::string zona; //Zona a cargar si es una habitacion, una zona etc...
    //std::shared_ptr<BulletEngine>& bulletEngine_t;
};


