#pragma once
#include "../../ecs/cmp/component.hpp"
#include <tuple>
#include <string_view>
#include <string>
#include <cstdint>
#include <iostream>

struct RenderComponent_t : ComponentBase_t<RenderComponent_t>{
    explicit RenderComponent_t(EntityID_t eid)
    : ComponentBase_t(eid)
    {}

    void loadDimensions(float dw,float dh,float dl){
        w = dw;
        h = dh;
        l = dl;
    }

    void loadFilesNames(const std::string_view path, const std::string_view path2){
        std::cout<<"entro al loadfilesnames\n" << " model: " << path.data() << " textura: " << path2.data() << " " <<std::endl ;
        modelPath = path.data();
        texturePath = path2.data();
    }

    const std::tuple<float,float,float> getData() const { return std::tuple{h,w,l}; };

    float w { 0 }, h { 0 }, l { 0 };
    std::string modelPath;
    std::string texturePath;
    bool isVisible{true};
};
