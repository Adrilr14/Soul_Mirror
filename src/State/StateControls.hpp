#pragma once
#include "State.hpp"

struct Controller_t;
struct StateControls : public State{
    StateControls();
    void update() override;
    void getInput() override;
    void draw() override;
    virtual void endScene() override;

    private:
        Controller_t* renderengine {nullptr};
};