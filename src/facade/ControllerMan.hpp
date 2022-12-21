#pragma once
#include <memory>
#include <facade/Controller.hpp>
 struct Controller_t;
 enum class TControllerMan {irrlichtGraphics,RavenGraphics};

class ControllerMan
{
public:
    ~ControllerMan();
    static ControllerMan& p();
    Controller_t& controller();

    void switchMotor();
private:
    ControllerMan(); 
    //Constructor por defecto privado
    //std::unique_ptr<Controller_t> m_motor;
    Controller_t*     m_motor = nullptr;
    //TControllerMan  m_seleccionado = TControllerMan::irrlichtGraphics; //El que ponemos seleccionado por defecto 
    TControllerMan  m_seleccionado = TControllerMan::RavenGraphics; 

 };
 