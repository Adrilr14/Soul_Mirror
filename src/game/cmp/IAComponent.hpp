#pragma once
#include <cstdint>
#include <chrono>//esto puede que no se use aqui, la dejo de momento pero habria que quitarla en un futuro
#include <ecs/cmp/component.hpp>

enum IAType{//esto puede que haya que cambiarlo a ints por el tema de borrar componentes y hacer copias
    erizo,//el erizo tiene un path definido
    seta,//la seta lo que hace es disparar al player
    spider//la aranya persigue al jugador dentro de un rango
};

enum AIActions{
    atack,
    def,
    move,
    look
};

//hay varios tipos de IA (fuzzy logic, behaviour tree... igual hay que darle mas vueltas a esto)
struct IAComponent_t : ComponentBase_t<IAComponent_t>{
    explicit IAComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    bool reposition {false};//esto para saber si a la spider le toca reposicionarse o no
    IAType type; 
    bool isActive{false};
    int disparos {0};//esto para controlar los disparos de la seta
    std::vector<std::pair<float,float>> patrol;//aqui van a ir las rutas de los erizos
    //para insertar en patrol seria algo tal que asi patrol.push_back(std::make_pair(50.0, 33.1));
    int rutaActual{0};//este int va a controlar la posicion del vector patrol, para saber donde ha de ir el erizo
    AIActions actions;//esto no se si tiene sentido, habra que verlo
    float time {0.25};//este valor define el tiempo en el que la IA con steering behaviour va a intentar llegar a su destino
    float radius {1.6};//define cuando el personaje va a considerar que ya ha llegado a su destino, puede variar para modificar el comportamiento de la IA
    float slowdistance {25.0};//define la distancia en la que el personaje empezara a frenar progresivamente, puede variar para modificar el comportamiento de la IA
};