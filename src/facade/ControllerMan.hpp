#pragma once

#include "Controller.hpp"
#include <memory>

struct Controller_t;
enum class TControllerMan {irrlichtGraphics,RavenGraphics};

class ControllerMan{
        using MemoryStorage = std::unique_ptr<std::byte[]>;
public:
    ~ControllerMan();
    static ControllerMan& p(); //Cambiar name a getInstancia
    Controller_t* controller();

    void switchMotor();
private:
    //Constructor por defecto privado
    ControllerMan(); 
    Controller_t* m_motor;
    std::size_t ControllerMemory { 500 };
    MemoryStorage mem { std::make_unique<std::byte[]>(ControllerMemory) };
    TControllerMan  m_seleccionado = TControllerMan::RavenGraphics; //El que ponemos seleccionado por defecto 
 };
 