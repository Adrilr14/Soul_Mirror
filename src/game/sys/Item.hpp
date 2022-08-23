#pragma once

struct EntityManager_t;

struct Item_t{
    
    Item_t(){};
    ~Item_t(){};
    void addManager(EntityManager_t& man){
        manager = &man;
    };

protected:
    EntityManager_t* manager {nullptr};
};
