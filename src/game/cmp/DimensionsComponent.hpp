#pragma once
#include <cstdint>
#include <tuple>
#include "../../ecs/cmp/component.hpp"


struct DimensionsComponent_t : ComponentBase_t<DimensionsComponent_t>{
    explicit DimensionsComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};

    //Getters
    const float getHeight() const { return height; };
    const float getWidth() const  { return width;  };
    const float getLength() const { return length; };
    const std::tuple<float,float,float> getData() const { return std::tuple{height,width,length}; };

    //Setters
    void setHeight(float d_height) { height = d_height; };
    void setWidth(float d_width)   { width = d_width; };
    void setLength(float d_length) { length = d_length; };

    //En este componente vamos a guardar las dimensiones de los modelados
private:
    float height;   //Dato para la altura 
    float width;    //Dato para la anchura
    float length;   //Dato para la longitud
};