#pragma once

#include <string_view>

struct BulletFacade{
    
    virtual ~BulletFacade() = default;
    virtual void createWolrdSystem() = 0;
    virtual void updateCollisionEngine() = 0;
    virtual void createObjects(float posX,float posY,float posZ,float w,float h,float l,bool staticE,std::string_view n) = 0;
};
