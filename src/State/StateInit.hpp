#pragma once
#include <State/State.hpp>

//struct RavenSound;
struct EventInfo;
struct Controller_t;

struct StateInit : public State{
    StateInit();
    void addEventListeners();
    void playSoundEvent();
    void update() override;
    void getInput() override;
    void draw() override;
    void endScene() override;

    private:
        Controller_t* renderengine {nullptr};
        //RavenSound* soundSystem {nullptr};
};