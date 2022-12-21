#pragma once
#include <functional>
#include <memory>
#include <string_view>
    //Tipos de eventos que pueden ejecutarse
    //poner todos los tipos de eventos
enum EventType {
    //**********EVENTOS DE INPUT**********
    Input_W ,
    Input_A ,
    Input_S ,
    Input_D , 
    Input_V ,
    Input_WD,
    Input_WA,
    Input_SD,
    Input_SA,
    Input_1 ,
    Input_2 ,
    Input_3 ,
    Input_4 ,
    Input_5 ,
    Pause,
    NewZone,
    Collision_Sword,
    Collision_Shield,
    State_Change, //EVENTO DE CAMBIO DE ESTADO QUE VENDRA DEFINIDO POR LA VARIABLE STATE_TYPE DE EVENTINFO
    PrintPhysics,//esto es de prueba, en el futuro se quitara
    Probando,//esto es de prueba, en el futuro se quitara
    //********BORRADO DE UNA SOLA ENTIDAD*******
    Delete_Entity_Render,
    Delete_Entity_Manager,
    Remove_Entity_MG,
    //********EVENTOS CAMBIO DE ZONA*********
    Delete_Entities_Bullet,
    Delete_Entities_Render, //este evento va a borrar TODO lo que se este renderizando
    Delete_Entities_Manager, //este evento borra todas las entidades del array y tambien los de los cmp
    Change_Zone, //evento para cambiar de zona. Crea las nuevas entitys
    Render_Change_Zone, //despues de ejecutar el Change_zone, se lanza este evento para decirle al motor grafico que renderice las nuevas entitys
    //*********EVENTOS DE LOS ENEMIGOS********  
    Create_Shot,//crea las balas del enemigo seta en el GAMEOBJECT, NO EN EL MOTOR GRAFICO
    Create_Shot_MG,//CREA UNA BALA EN EL MOTOR GRAFICO
    Calculate_Angle,//calcula el angulo de las balas
    //********EVENTOS SONOROS***********
    Play_Music,
    Stop_Music,
    Stop_Walking,
    setWeaponsPos,
    WindowResize
};

struct EventInfo {
    std::size_t id;
    int zone;//este no se usa tampoco de momento
    int direction;
    int rotation;//este de momento no se usa, lo dejo por si acaso
    std::tuple<float,float,float> rotationAxis;
    int state_type;
    float posX;
    float posY;
    float posZ;
    float angle;//angulo que se le asigna a la bala
    std::string_view model;
    std::string_view texture;
    bool shotdir;
    /*state type
    1 = init, 2 = pause, 3 = controls, 4 = game, 5 = credits
    */
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







