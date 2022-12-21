#pragma once

#include "../../ecs/man/entityManager.hpp"
#include <ecs/util/typealias.hpp>


struct CollisionSystem_t{
     
    public:
        explicit CollisionSystem_t(EntityManager_t& em):
        manager(em){}

        void update();
        bool Collision(Entity_t& f,Entity_t& s);
    private:
        EntityManager_t& manager;
};
