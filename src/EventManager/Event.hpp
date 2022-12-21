#pragma once

struct Event {

public:
    //Tipos de eventos que pueden ejecutarse
    enum EventType {
        //poner todos los tipos de eventos
        Input_W ,
        Input_A ,
        Input_S ,
        Input_D , 
        WindowResize
    };

    Event(EventType evt) : evtType(evt) {}
    const EventType getEventType() const { return evtType;};
private:
    EventType evtType;
};


