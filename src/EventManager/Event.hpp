#pragma once
#include <functional>
#include <memory>
#include <string>
    //Tipos de eventos que pueden ejecutarse
enum EventType {
    //poner todos los tipos de eventos
    Input_W ,
    Input_A ,
    Input_S ,
    Input_D , 
    Input_WD,
    Input_WA,
    Input_SD,
    Input_SA,
    
    Probando,
    //eventos de input posibles
    Delete_Entities_Render, //este evento va a borrar TODO lo que se este renderizando
    Delete_Entities_Manager, //este evento borra todas las entidades del array y tambien los de los cmp
    Change_Zone, //evento para cambiar de zona. Crea las nuevas entitys
    Render_Change_Zone, //despues de ejecutar el Change_zone, se lanza este evento para decirle al motor grafico que renderice las nuevas entitys
    Play_Music,
    Stop_Music,
    WindowResize
};

struct EventInfo {
    int id;
    int zone;
    int direction;
    //std::string song_name;
};

struct Event{
    EventType type;
    EventInfo info;
    Event(EventType tipo) : type{tipo} {}
    Event(EventType tipo, EventInfo info1) : type{tipo}, info{info1}{}
};

//function<void(DataMap*)> callback;

struct EventListener{
    EventType listenerType;
    //void (*callback)(EventInfo);
    std::function<void(EventInfo)> callback;
    EventListener(EventType tipo, std::function<void(EventInfo)> call) :
        listenerType{tipo}, callback{call}{}
    
};

typedef std::vector<EventListener> VecLis;
/*#pragma once

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
};*/







