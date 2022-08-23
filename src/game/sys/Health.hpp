#pragma once

struct EntityManager_t;

struct HealthSystem_t{
    explicit HealthSystem_t(EntityManager_t& em):
    manager(em){}
    void Update() const;
    
    private:
        EntityManager_t& manager;
};