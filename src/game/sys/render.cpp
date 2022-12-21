#include <game/sys/render.hpp>
#include <facade/RavenGraphics.hpp>
#include <facade/ControllerMan.hpp>
#include <ecs/man/entityManager.hpp>
//Esto es para quitarlo hay pq incluye enn include del Irrlicht ver lo de Fran

RenderSystem_t::RenderSystem_t(uint32_t m_w,uint32_t m_h)
: w{m_w},h{m_h} {}


void RenderSystem_t::renderInit() const {
    ControllerMan::p().controller().createWindow(w,h);
    ControllerMan::p().controller().renderInit();
}


void RenderSystem_t::renderUpdate() const{
    ControllerMan::p().controller().renderScene();
}

void RenderSystem_t::renderUpdatePlayer() const{
   
}


bool RenderSystem_t::getRun() const{
    return ControllerMan::p().controller().run();
}

