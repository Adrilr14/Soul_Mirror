#include "physics.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/DirecComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../../ecs/man/entityManager.hpp"
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
    if(!iswalking){
        iswalking = true;
        now = std::chrono::steady_clock::now();
    }
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
    auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
    auto* dircmp = e->template getComponent<DirecComponent_t>();
    dircmp->dir = info.direction;
    //delete e;
    //delete dircmp;
}

void PhysicsSystem_t::physicsUpdate() const{
     //cojo la primera entidad, que es el personaje
    //std::cout<<"Direccion actual:"<<e.direcc->dir<<std::endl;
    //std::cout<<"Velocidad actual X:"<<e.physics->vx<<" Velocidad actual Z:"<<e.physics->vz<<std::endl;
    //compruebo que ni la direccion ni el physics sean nullptr
    //1:derecha 2:izquierda 3:arriba 4:abajo 5:arriba derecha 6:arriba izquierda 7:abajo derecha 8:abajo izquierda
     
    for(auto& phy : manager.getComponents<PhysicsComponent_t>()){
        //std::cout<<"ID de la entity: "<<phy.getEntityID();
        auto* e = manager.getEntityByID(phy.getEntityID());
        if(e && e->template getComponent<DirecComponent_t>()){  
            auto* dircmp = e->template getComponent<DirecComponent_t>();
            switch(e->template getComponent<DirecComponent_t>()->dir){
            //de 1 a la 4 direcciones en un solo eje
            case 1://derecha
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.x += phy.vx;
                }
                
                //bullet_t->walkingCharacter(phy.vx,0.0,0.0);
                //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
                break;

            case 2://izquierda
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.x -= phy.vx;
                }
                
                //bullet_t->walkingCharacter(-phy.vx,0.0,0.0);
                //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
                break;

            case 3://arriba
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.z += phy.vz;
                }
                
                //bullet_t->walkingCharacter(0.0,0.0,phy.vz);
                break;

            case 4://abajo
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.z -= phy.vz;
                }

                //bullet_t->walkingCharacter(0.0,0.0,-phy.vz);
                break;
            //movimientos en diagonal
            case 5://arriba derecha
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.z += phy.vz;
                    phy.x += phy.vx;
                }
                
                //bullet_t->walkingCharacter(phy.vx,0.0,phy.vz);
                break;

            case 6://arriba izquierda
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.z += phy.vz;
                    phy.x -= phy.vx; 
                }
                
                //bullet_t->walkingCharacter(-phy.vx,0.0,phy.vz);
                break;

            case 7://abajo derecha
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.z -= phy.vz;
                    phy.x += phy.vx; 
                }
                
                //bullet_t->walkingCharacter(phy.vx,0.0,-phy.vz);
                break;

            case 8://abajo izquierda
                if(dircmp->dirCollision != dircmp->dirPrevia){
                    phy.z -= phy.vz;
                    phy.x -= phy.vx;
                }
                //bullet_t->walkingCharacter(-phy.vx,0.0,-phy.vz);
                break;
            default:
                //bullet_t->walkingCharacter(0.0,0.0,0.0);
                break;
            }
            //std::cout<<"Posicion en X: "<<phy.x<<" Posicion en Z: "<<phy.z<<"\n";
            dircmp->dir = -1;
            if(iswalking){
                auto end = std::chrono::steady_clock::now();
                double elapsed = double(std::chrono::duration_cast<std::chrono::milliseconds> (end-now).count());
                if(elapsed >= 200){
                    EventManager::getInstancia().addEvent(Event{EventType::Stop_Walking});
                    iswalking = false;
                }
            }
            //delete e;
            //delete dircmp;
        }
    }
}

void PhysicsSystem_t::positionChangeZone(EventInfo info){
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
        if(e){
            auto phy = e->getComponent<PhysicsComponent_t>();
            auto direc = e->getComponent<DirecComponent_t>();
            if(phy && direc){
                //Hay q cambiar la posicion del bullet no esta
                switch (direc->dirPrevia){
                case 1:
                    phy->x += 5;
                    //bullet_t->moveKinematicObject(5,0.0,0.0);
                    break;
                case 2:
                    phy->x -= 5;
                    //bullet_t->moveKinematicObject(-5,0.0,0.0);
                    break;
                case 3:
                    phy->z += 5;
                    //bullet_t->moveKinematicObject(0.0,0.0,5);
                    break;
                case 4:
                    phy->z -= 5;
                    //bullet_t->moveKinematicObject(0.0,0.0,-5);
                    break;
                default: //Si es -1 va al default que no debe realizar nada
                    break;
                }
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
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::NewZone,std::bind(&PhysicsSystem_t::positionChangeZone,this,std::placeholders::_1)));
}