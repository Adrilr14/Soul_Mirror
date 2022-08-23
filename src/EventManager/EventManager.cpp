#include "EventManager.hpp"
#include <algorithm>


//destructor of the class
EventManager::~EventManager(){
    EventManager::clearListener();
}


EventManager& EventManager::getInstancia(){
    static EventManager instancia;
    return instancia;
}

void EventManager::addEvent(const Event& evt){//se inserta un evento en el vector que luego se procesara
    //Lo primero que vamos a hacer es registrar los eventos nuevos que se produzcan en orden de preferencia
    //Comprobamos si hay mas de un elemento en el vector de eventos

    //for random insert/remove : use std::list (if data size very small (< 64b on my computer), use std::vector)
    //(?) Preguntar a Fran que es mejor utilizar list o vector segun lo que vi es mejor list dependiendo del tamaño de datos
    //std::cout<<"estoy en el addevent del eventmanager y el size del vector es de: "<<eventos.size()<<"\n";
    
    if(eventos.size() > 0){
        //Como hay mas de 1 elemento tenemos que ver en que posicion de prioridad se encuentra
        //hay que usar un iterador para poder emplear el metodo insert, que inserta en una posicion y desplaza los demas
        //si se hace eventos[i] = x; lo que habia anteriormente en la posicion i se pierde, por lo que el vector de eventos siempre tendra 1 solo evento
        std::vector<Event>::iterator it;
        for (it = eventos.begin(); it != eventos.end() ;it++){
            if(evt.type <= it->type){
                break;
            }
        }
        eventos.insert(it,evt);
    }
    else
        //Si no hay directamente añadimos el nuevo eventos al principio
        eventos.push_back(evt);
        //std::cout<<"estoy en el addevent del eventmanager y el size del vector es de: "<<eventos.size()<<"\n";
}

void EventManager::AddEventToListener(const EventListener& listen){//se vincula un tipo de evento a un listener, que tiene la funcion
    //std::cout << "entra en el addListener\n";
    if(eventos.capacity() < 50)
        eventos.reserve(50);
    //Hay que ver si ese evento ya esta registrado
    auto it = listener.find(listen.listenerType);
    //si entra en este if significa que no lo estaba, lo creamos
    if(it == listener.end()){
        VecLis listener2;
        it = listener.insert(std::pair<EventType,VecLis>(listen.listenerType,listener2)).first;
    }

    it->second.push_back(listen);
    
}

void EventManager::update(){
    //std::cout<<"Entro al update del event\n";
    //Ahora lo que procederemos es a actualizar y ejecutar todas las 
    //funciones que se encuentran en el vector de eventos y en el listener
    while( eventos.size() != 0){
        auto copy = eventos[0];
        eventos.erase(eventos.begin());
        //Ahora comprobamos que en el listener hay un evento de este tipo
        auto it = listener.find(copy.type);
        if(it != listener.end()){
            auto functionEvent = it->second;
            for(EventListener& listen : functionEvent)
                listen.callback(copy.info);
        }
    }   
}

void EventManager::clearListener(){
    listener.clear();
}

void EventManager::showListener(){
    //En esta función vamos a imprimir el Listener que es el que guarda los eventos

    //Obtenemos el iterador y con begin para empezar 
    //No hace falta comprobar si el listener esta vacio pq se comprueba en el bucle
    for ( auto it = listener.begin(); it != listener.end();  it++){
        //std::cout << "Listener first " << it->first << "\n";
        //std::cout << "Listener second " << it->second.data() << "\n";
    }
}
