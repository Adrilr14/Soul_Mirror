#pragma once
#include <functional>
#include <memory>
#include <string_view>
#include <string>
    //Tipos de eventos que pueden ejecutarse
    //poner todos los tipos de eventos
enum EventType {
    herida_Animation,//hace la animacion del player
    dead_Animation,
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
    Input_Shift,
    Input_Space,
    Release_Shift,
    empujar_Animation,
    Pause,
    Teleport,
    Collision_Sword,
    Collision_Shield,
    Change_Position_Attacked, //Evento para cambiar la posicion del perosnaje cuando le han atacado para que asi no muera enseguida
    State_Change, //EVENTO DE CAMBIO DE ESTADO QUE VENDRA DEFINIDO POR LA VARIABLE STATE_TYPE DE EVENTINFO
    PrintPhysics,//esto es de prueba, en el futuro se quitara
    Probando,//esto es de prueba, en el futuro se quitara
    setVisibilidad, //Set visibilidad Motor Grafico
    addChildNode, //Añadir un nodo hijo a un nodo padre
    create_Espejo,
    create_Deku,
    //********BORRADO DE UNA SOLA ENTIDAD*******
    Delete_Entity_Render,
    Delete_Entity_Manager,
    Remove_Entity_MG,
    //********EVENTOS CAMBIO DE ZONA*********
    Delete_Entities_Bullet,
    Delete_Entities_Render, //este evento va a borrar TODO lo que se este renderizando
    Delete_Entities_Manager, //este evento borra todas las entidades del array y tambien los de los cmp
    Change_ruta,
    Change_zona,
    Read_Level, //evento para cambiar de zona. Crea las nuevas entitys
    Player_Dead,//pone al player en el inicio de la zona si ha muerto y decide continuar
    PruebaHP,
    Render_Change_Zone, //despues de ejecutar el Change_zone, se lanza este evento para decirle al motor grafico que renderice las nuevas entitys
    //*********EVENTOS DE LOS ENEMIGOS********  
    Create_Shot,//crea las balas del enemigo seta en el GAMEOBJECT, NO EN EL MOTOR GRAFICO
    Create_Shot_MG,//CREA UNA BALA EN EL MOTOR GRAFICO
    Calculate_Angle,//calcula el angulo de las balas
    //********EVENTOS SONOROS***********
    Play_Music,
    Stop_Music,
    Menu_Back,
    Menu_Select,
    Menu_Change,
    Stop_Walking,
    Beber,
    Correr,		
    Corte,
    Coger,
    Enemy_Seta,
    Enemy_Spider,
    Desierto,//este es de ambiente, igual no hace falta
    Colision_Escudo,
    Espada_No_Colision,
    Colision_Flecha,
    Explosion,
    Fuego,
    Herida,
    Industrial,//lo mismo que el desierto
    Bosque,
    Nieve,//lo mismo que desierto e industrial
    Soltar_Flecha,
    Soltar_Objeto,
    Muerte,
    Objeto,
    Abrir_Puerta,
    Arrastrar,
    Mecanismo, 
    setWeaponsPos,
    NewZone,
    WindowResize
};

struct EventInfo {
    std::size_t id;
    int zone;//este no se usa tampoco de momento
    int direction;
    int rotation;//este de momento no se usa, lo dejo por si acaso
    std::tuple<float,float,float> rotationAxis;
    int state_type;
    int shottype;
    float posX { 0.0} ;
    float posY { 0.0 };
    float posZ { 0.0 };
    float rotX;
    float rotY;
    float rotZ;
    float angle;//angulo que se le asigna a la bala
    std::string_view model;
    std::string_view texture;
    bool shotdir;
    bool visibilidad;
    bool playerShoot {false};
    std::string ruta;
    std::string zona;
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







