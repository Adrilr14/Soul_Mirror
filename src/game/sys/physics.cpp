#include <game/sys/physics.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <ecs/man/entityManager.hpp>
#include <iostream>
//#include <EventManager/EventManager.hpp>


void PhysicsSystem_t::addManager(EntityManager_t& man){
    //manager = &man;
}

void PhysicsSystem_t::physicsInit() const{
    //ControllerMan::p().controller().physicsInit();
}

void PhysicsSystem_t::probando(EventInfo info){
    //std::cout<<"Estoy en el physics system y el size del vector es de: "<<manager.getEntities().size()<<"\n";
}

void PhysicsSystem_t::switchDirection(EventInfo info){
    //std::cout<<"entro en el switch direcion\n";
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
    auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
    auto* dircmp = e->template getComponent<DirecComponent_t>();
    dircmp->dir = info.direction;
    //delete e;
    //delete dircmp;
}

void PhysicsSystem_t::physicsUpdate() const{
    //std::cout<<"entro al physics";
     //cojo la primera entidad, que es el personaje
    //std::cout<<"Direccion actual:"<<e.direcc->dir<<std::endl;
    //std::cout<<"Velocidad actual X:"<<e.physics->vx<<" Velocidad actual Z:"<<e.physics->vz<<std::endl;
    //compruebo que ni la direccion ni el physics sean nullptr
    //1:derecha 2:izquierda 3:arriba 4:abajo 5:arriba derecha 6:arriba izquierda 7:abajo derecha 8:abajo izquierda
     
    for(auto& phy : manager.getComponents<PhysicsComponent_t>()){
        auto* e = manager.getEntityByID(phy.getEntityID());
        if(e && e->template getComponent<DirecComponent_t>()){  
            auto* dircmp = e->template getComponent<DirecComponent_t>();
            switch(e->template getComponent<DirecComponent_t>()->dir){
            //de 1 a la 4 direcciones en un solo eje
            case 1://derecha
                phy.x += phy.vx;
                //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
                break;

            case 2://izquierda
                phy.x -= phy.vx;
                //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
                break;

            case 3://arriba
                phy.z += phy.vz;
                break;

            case 4://abajo
                phy.z -= phy.vz;
                break;
            //movimientos en diagonal
            case 5://arriba derecha
                phy.z += phy.vz;
                phy.x += phy.vx;
                break;

            case 6://arriba izquierda
                phy.z += phy.vz;
                phy.x -= phy.vx;
                break;

            case 7://abajo derecha
                phy.z -= phy.vz;
                phy.x += phy.vx;
                break;

            case 8://abajo izquierda
                phy.z -= phy.vz;
                phy.x -= phy.vx;
                break;
            }
            //std::cout<<"Posicion en X: "<<phy.x<<" Posicion en Z: "<<phy.z<<"\n";
            dircmp->dir = -1;
            //delete e;
            //delete dircmp;
        }
    }
    
}

void PhysicsSystem_t::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Probando,std::bind(&PhysicsSystem_t::probando,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_W,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_A,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_S,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_D,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WD,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WA,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SD,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SA,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
}