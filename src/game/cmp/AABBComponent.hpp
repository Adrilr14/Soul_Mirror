//#pragma once
//
//#include "../../ecs/cmp/component.hpp"
//#include "../"
//#include <game/Physics/Intersection.hpp>
//#include <vec3.hpp>
//#include <common.hpp>
//
//struct AABBComponent : ComponentBase_t<AABBComponent>{
//    
//    explicit AABBComponent(std::size_t eid)
//    :   ComponentBase_t(eid)
//    {};
//
//    inline const glm::vec3 getMinExtens() const { return minExtens; };
//    inline const glm::vec3 getMaxExtens() const { return maxEntens; };
//
//    Intersection_t IntersectAABB(const AABBComponent& o){
//        glm::vec3 distancia1 = o.getMinExtens() - maxEntens;
//        glm::vec3 distancia2 = minExtens - o.getMaxExtens();
//        glm::vec3 resultDistance = glm::max(distancia1,distancia2);
//        float maxDistancia = AABBComponent::maxVec3(resultDistance);
//        
//        return Intersection_t(maxDistancia < 0, maxDistancia);
//    }
//
//    float maxVec3(glm::vec3 const& v){
//        return glm::max(glm::max(v.x,v.y),v.z);
//    }
//
//private:
//    glm::vec3 minExtens; //Estas dos variables representan los corners
//    glm::vec3 maxEntens;
//};
//