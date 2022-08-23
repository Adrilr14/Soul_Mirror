#pragma once
#include "Item.hpp"
#include <string>
#include <vector>

struct Key : public Item_t {

    explicit Key() = default;
    virtual ~Key(){ numberofKeys = 0; };

    void addKey(){
        numberofKeys++;
    }

    bool Looking(){
        if(numberofKeys > 0){
            numberofKeys--;
            return true;
        }
        return false;
    }

    int numberofKeys {0};
};