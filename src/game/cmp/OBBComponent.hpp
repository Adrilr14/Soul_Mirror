#pragma once
#include <vec3.hpp>
#include <vector>
#include <limits>
#include <stdlib.h>
#include "../../ecs/cmp/component.hpp"

struct OBBComponent_t : ComponentBase_t<OBBComponent_t>{
    explicit OBBComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};
    //One popular way to define them is to specify a (center) point C and orthonormal set of basis vectors {uˆ,vˆ,wˆ} 
    float center;   //Point C
    std::vector<float> axis;
    float half_width,half_height,half_depth;//three scalars representing the half-width, half-height, and half-depth

    bool RayIntersectOBB(float P,glm::vec3 d, OBBComponent_t box){
        
        auto tNear = -std::numeric_limits<float>::infinity();
        auto tFar  = std::numeric_limits<float>::infinity();

        for(unsigned int i = 0; i < axis.size();i++){
            //Check for ray Parallel to planes
    
        }
    }
};