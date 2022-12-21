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

void EventManager::onEvent(const Event& evt){
    //Lo primero que vamos a hacer es registrar los eventos nuevos que se produzcan en orden de preferencia
    //Comprobamos si hay mas de un elemento en el vector de eventos

    //for random insert/remove : use std::list (if data size very small (< 64b on my computer), use std::vector)
    //(?) Preguntar a Fran que es mejor utilizar list o vector segun lo que vi es mejor list dependiendo del tamaño de datos
    
    if(eventos.size() > 0){
        //Como hay mas de 1 elemento tenemos que ver en que posicion de prioridad se encuentra
        for (unsigned int i = 0; i < eventos.size(); i++){
            if(evt.getEventType() <= eventos[i].getEventType()){
                eventos[i] = evt;
                i++;
                break;
            }
        }
    }else{
        //Si no hay directamente añadimos el nuevo eventos al principio
        eventos.push_back(evt);
    }
}

void EventManager::AddEventToListener(const Event::EventType& type,callBack callParam){
    std::cout << "entra en el addListener" << std::endl;
    //Como vamos a añadir 
    auto it = listener.find(type);
//
    if(it != listener.end()){
        for ( auto& callbk : it->second){
            if(callbk.target_type().hash_code() != callParam.target_type().hash_code()){
                if( type <= it->first ){
                    break;
                }
            }else{
                return;
            }
        }
    }

    listener[type].emplace_back(callParam);
}

void EventManager::update(){
    //Ahora lo que procederemos es a actualizar y ejecutar todas las 
    //funciones que se encuentran en el vector de eventos y en el listener
    while( eventos.size() != 0){
        auto copy = eventos[0];
        eventos.erase(eventos.begin());

        //Ahora comprobamos que en el listener hay un evento de este tipo
        auto it = listener.find(copy.getEventType());
        if(it != listener.end()){
             for (auto& callback : it->second){
                callback(copy);
            }
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
        std::cout << "Listener first " << it->first << "\n";
        std::cout << "Listener second " << it->second.data() << "\n";
    }
}

//void WindowT::update(){
//    EventManager::AddEventToListener(Event::EventType::WindowResize,std::bind(&WindowT::WindowResized, this, std::placeholders::_1));
//}
//
//void WindowT::WindowResized(Event& e){
//       std::cout << "Se ejecuta WindowResized" << std::endl;
//        if (e.getEventType() == Event::EventType::WindowResize){
//            WindowResizedEvent e = reinterpret_cast<WindowResizedEvent&>(e);
//            windowWidth = e.width;
//            windowHeight = e.height;
//        }
//}