#pragma once

#include <cstdint>

struct ControllerMan;

struct RenderSystem_t
{
    RenderSystem_t(uint32_t,uint32_t);
    void renderInit() const;
    void renderUpdate() const;
    void renderUpdatePlayer() const;
    bool getRun() const;
private:
const uint32_t w {0};   //width de la ventana
const uint32_t h {0};   //height de la ventana  
//EntityManager_t& manager;
};  //RenderSystem_t
