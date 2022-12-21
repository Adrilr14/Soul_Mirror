#pragma once
#include <ecs/cmp/component.hpp>
#include <string_view>
#include <string>
#include <cstdint>

struct RenderComponent_t : ComponentBase_t<RenderComponent_t>{
    explicit RenderComponent_t(EntityID_t eid)
    : ComponentBase_t(eid)
    {}

    void loadDimensions(uint32_t dw,uint32_t dh,uint32_t dl){
        w = dw;
        h = dh;
        l = dl;
    }

    void loadFilesNames(const std::string_view path,const std::string_view texture){
        modelPath = path.data();
        texturePath = texture.data();
    }

    uint32_t w { 0 }, h { 0 }, l { 0 };
    std::string modelPath;
    std::string texturePath;
};
