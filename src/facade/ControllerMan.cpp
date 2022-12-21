#include <facade/ControllerMan.hpp>
#include <facade/irrlichtGraphics.hpp>
#include <facade/RavenGraphics.hpp>
#include <iostream>

ControllerMan::ControllerMan(){
    m_motor = new irrlichtGraphics();
}

ControllerMan::~ControllerMan(){
    delete m_motor;
}

Controller_t& ControllerMan::controller(){
    return *m_motor;
}

ControllerMan& ControllerMan::p(){
    static ControllerMan instancia;
    return instancia;
}

void ControllerMan::switchMotor(){
    delete m_motor;

    switch (m_seleccionado){
    case TControllerMan::irrlichtGraphics:
        m_motor = new irrlichtGraphics();
        m_seleccionado = TControllerMan::irrlichtGraphics; 
        break;
    case TControllerMan::RavenGraphics:
        m_motor = new RavenGraphics();
        m_seleccionado = TControllerMan::RavenGraphics; 
    default:
        break;
    }
}