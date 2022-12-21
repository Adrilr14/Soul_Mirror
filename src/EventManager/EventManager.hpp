#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <map>
#include "Event.hpp"
#include <ecs/util/typealias.hpp>
#include <iostream>

//using callBack = std::function<void(Event&)>;
//using EventType = Event::EventType;


struct EventManager {

public:
    ~EventManager();
    EventManager(const EventManager&)           = delete;
    EventManager(EventManager&&)                = delete;
    EventManager& operator=(const EventManager) = delete;
    EventManager& operator=(EventManager&&)     = delete;
   
    static EventManager& getInstancia();
    void addEvent(const Event& e);
    void AddEventToListener(const EventListener&);
    void showListener();
    void update();
    void clearListener();    

private:
    EventManager() = default;   
    std::vector<Event> eventos;
    std::map<EventType,VecLis> listener;
    //Necesitamos tener un vector de eventos para poder hacer un update que sea automatico
    //Pq si lo hacemos con el triggerEvent tendriamos que pasarle el evento entonces no
    //se haria de forma que respetara un orden de prioridad como decia en el libro de Wisdom

    //static std::list<EventManagerData> managerList;
    //static std::map<std::pair<Event,Event::EventType>,std::vector<callBack>> listener;
};

/*#pragma once

#include <functional>
#include <vector>
#include <map>
#include "Event.hpp"
#include <ecs/util/typealias.hpp>
#include <iostream>

using callBack = std::function<void(Event&)>;
using EventType = Event::EventType;


struct EventManager {

public:
    ~EventManager();
    EventManager(const EventManager&)           = delete;
    EventManager(EventManager&&)                = delete;
    EventManager& operator=(const EventManager) = delete;
    EventManager& operator=(EventManager&&)     = delete;
   
    static EventManager& getInstancia();
    void onEvent(const Event& e);
    void AddEventToListener(const Event::EventType& type,callBack callParam);
    void showListener();
    void update();
    void clearListener();    

    template <typename T>
    static void TriggerEvent(Event& event){
        std::cout << "entra en el trigger \n";
        auto it = listener.find(event.getEventType());

        if (it != listener.end()){
            for (auto& callback : it->second){
                callback(static_cast<T&>(event));
            }
        }
    }
private:
    EventManager() = default;   
    inline static std::vector<Event> eventos {};
    inline static std::map<EventType,std::vector<callBack>> listener {};
    //Necesitamos tener un vector de eventos para poder hacer un update que sea automatico
    //Pq si lo hacemos con el triggerEvent tendriamos que pasarle el evento entonces no
    //se haria de forma que respetara un orden de prioridad como decia en el libro de Wisdom

    //static std::list<EventManagerData> managerList;
    //static std::map<std::pair<Event,Event::EventType>,std::vector<callBack>> listener;
};
*/
