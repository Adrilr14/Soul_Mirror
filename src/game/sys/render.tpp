#include <game/sys/render.hpp>
#include <facade/RavenGraphics.hpp>
#include <facade/ControllerMan.hpp>
#include <ecs/man/entityManager.hpp>
//Esto es para quitarlo hay pq incluye enn include del Irrlicht ver lo de Fran

template <typename GameCTX_t>
RenderSystem_t<GameCTX_t>::RenderSystem_t(uint32_t m_w,uint32_t m_h,GameCTX_t& g)
: w{m_w},h{m_h},manager{g} {}



template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::renderInit() const {
    ControllerMan::p().controller().createWindow(w,h,manager.getEntities());
    ControllerMan::p().controller().renderInit();
}


template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::renderUpdate() const{
    ControllerMan::p().controller().renderScene();
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::renderUpdatePlayer(GameCTX_t& g) const{
    ControllerMan::p().controller().renderEntities(g);
}


template <typename GameCTX_t>
bool RenderSystem_t<GameCTX_t>::getRun() const{
    return ControllerMan::p().controller().run();
}

