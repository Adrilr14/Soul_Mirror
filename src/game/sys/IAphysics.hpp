#pragma once

#include <cstdint>
#include <chrono>
#include <ecs/util/typealias.hpp>
#include <facade/RavenGraphics.hpp>

struct ControllerMan;
struct EntityManager_t;
struct PhysicsComponent_t;
struct IAComponent_t;

struct IAPhySystem_t{
    explicit IAPhySystem_t(EntityManager_t& em):
    manager(em){}
    void addManager(EntityManager_t&);//no se usa
    void update() const;
    //metodos auxiliares para los steering behaviors
    void meterRuta(Entity_t*) const;//aqui metemos la ruta del erizo, no esta directamente ligado al steering pero de momento hay que meter la ruta en algun sitio
    float calculateDistance(float,float,float,float) const;
    float calculatePendiente(float,float,float,float) const;
    float calculateAngle(float,float,float,float) const;
    float calculateOrientation(float,float) const;
    float calculateAverageVelocity() const;
    float truncate(float, float, float) const;//de momento no se usa
    //metodos de distintos steering behaviors
    void updateSteering(Entity_t*) const;
    void updateSteering() const;
    void Seek(PhysicsComponent_t*, IAComponent_t*) const;
    void Arrive(PhysicsComponent_t*, IAComponent_t*, auto, auto) const;
    void Arrive(PhysicsComponent_t*, IAComponent_t*) const;
    //metodos de entidades sin IA
    void spider(PhysicsComponent_t*, IAComponent_t*) const;
    void seta(PhysicsComponent_t*, IAComponent_t*) const;

    private:
        EntityManager_t& manager;
        mutable std::chrono::time_point<std::chrono::steady_clock> cadencia;//reloj que se va a usar para la pausa entre disparos de la seta
        mutable std::chrono::time_point<std::chrono::steady_clock> reload;//reloj para timear la pausa cada 3 disparos de la seta
        mutable bool reloadCheck  {false}; //booleano de control para activar el reloj de reload
        mutable bool cadenciaCheck{false}; //booleano de control para timear la pausa entre disparos ~0.3s
        mutable bool prueba{false};
        static constexpr double dt{1.0/60.0};
        mutable bool prueba2{false};
};  //RenderSystem_t
