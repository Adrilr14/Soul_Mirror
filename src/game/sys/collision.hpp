#pragma once

#include "../../ecs/man/entityManager.hpp"
#include "../../ecs/util/typealias.hpp"

struct PhysicsComponent_t;

struct CollisionSystem_t{
     
    public:
        explicit CollisionSystem_t(EntityManager_t& em):
        manager(em){}

        void update();
        bool Collision(Entity_t* first,Entity_t* second);
        bool Collision(Entity_t* first,Entity_t* second, int direc);
        int IntersectionOBBOBB(Entity_t* first,Entity_t* second) const;
        void collisionZone();
        void DynamicsObjects();
        void collisionStatics();
        void collisionEnemy();
        void collisionCaja(EventInfo);
        void collisionBalas();
        void moverCaja(PhysicsComponent_t* cajitaphy, int direc, bool control);
        void SwordAttack(EventInfo info);
        void ShieldDefense(EventInfo info);
        void addEventListeners();
    private:
        EntityManager_t& manager;
        double before {-1};
        int colisionados {0};
        double beforeBalas {-1};
};
