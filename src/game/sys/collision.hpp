#pragma once

#include "../../ecs/man/entityManager.hpp"
#include "../../ecs/util/typealias.hpp"
#include "../../Motor/BulletEngine/BulletEngine.hpp"

struct CollisionSystem_t{
     
    public:
        explicit CollisionSystem_t(EntityManager_t& em,std::shared_ptr<BulletEngine> b):
        manager(em), bullet_t(b){}

        void update();
        bool Collision(Entity_t* first,Entity_t* second);
        void collisionZone();
        void collisionStatics();
        void SwordAttack(EventInfo info);
        void ShieldDefense(EventInfo info);
        void addEventListeners();
    private:
        EntityManager_t& manager;
        std::shared_ptr<BulletEngine> bullet_t;
};
