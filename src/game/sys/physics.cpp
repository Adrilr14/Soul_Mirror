#include "physics.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../cmp/DirecComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/ItemComponent.hpp"
#include "../cmp/PlayerComponent.hpp"
#include "../cmp/CollisionComponent.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../../HPA/NavMesh.hpp"
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
     
    for(auto& dircmp : manager.getComponents<DirecComponent_t>()){
        //std::cout<<"ID de la entity: "<<phy.getEntityID();
        auto* e = manager.getEntityByID(dircmp.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){  
            auto* phy = e->template getComponent<PhysicsComponent_t>();
            Vector3D valueDirection = dircmp.getValuesDirection(dircmp.dir);
           
            if(dircmp.dirCollision != dircmp.dirPrevia){
                phy->x += valueDirection.m_x*phy->vx;
                phy->y += valueDirection.m_y*phy->vy;
                phy->z += valueDirection.m_z*phy->vz;
            }
            Vector3D dirPreviaAngle = dircmp.getValuesDirection(dircmp.dirPrevia);
            phy->ry = dirPreviaAngle.angle;
            //switch(e->template getComponent<DirecComponent_t>()->dir){
            ////de 1 a la 4 direcciones en un solo eje
            //case 1://derecha
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy->x += phy->vx;
            //    }
            //    phy->ry = 90;
            //    
            //    //bullet_t->walkingCharacter(phy.vx,0.0,0.0);
            //    //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
            //    break;
//
            //case 2://izquierda
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy->x -= phy->vx;
            //    }
            //    phy->ry = -90;
            //    
            //    //bullet_t->walkingCharacter(-phy.vx,0.0,0.0);
            //    //std::cout<<"Voy a la derecha pos x: "<<phy.x<<"\n";
            //    break;
//
            //case 3://arriba
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy->z += phy->vz;
            //    }
            //    phy->ry = 0; 
            //    
            //    //bullet_t->walkingCharacter(0.0,0.0,phy.vz);
            //    break;
//
            //case 4://abajo
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy->z -= phy->vz;
            //    }
            //    phy->ry = 180;
//
            //    //bullet_t->walkingCharacter(0.0,0.0,-phy.vz);
            //    break;
            ////movimientos en diagonal
            //case 5://arriba derecha
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy->z += phy->vz;
            //        phy->x += phy->vx;
            //    }
            //    phy->ry = 30;
            //    
            //    //bullet_t->walkingCharacter(phy.vx,0.0,phy.vz);
            //    break;
//
            //case 6://arriba izquierda
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy->z += phy->vz;
            //        phy->x -= phy->vx; 
            //    }
            //    phy->ry = -30;
            //    
            //    //bullet_t->walkingCharacter(-phy.vx,0.0,phy.vz);
            //    break;
//
            //case 7://abajo derecha
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy->z -= phy->vz;
            //        phy->x += phy->vx; 
            //    }
            //    phy->ry = 150;
            //    
            //    //bullet_t->walkingCharacter(phy.vx,0.0,-phy.vz);
            //    break;
//
            //case 8://abajo izquierda
            //    if(dircmp.dirCollision != dircmp.dirPrevia){
            //        phy-> z -= phy->vz;
            //        phy-> x -= phy->vx;
            //    }
            //     phy->ry = -150;
            //    //bullet_t->walkingCharacter(-phy.vx,0.0,-phy.vz);
            //    break;
            //default:
            //    //bullet_t->walkingCharacter(0.0,0.0,0.0);
            //    break;
            //}
            //std::cout<<"Posicion en X: "<<phy.x<<" Posicion en Z: "<<phy.z<<"\n";
            dircmp.dir = -1;
            updateChildsPlayer();
            RunningTren();
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

void PhysicsSystem_t::updateChildsPlayer() const{

    auto player = manager.getComponents<PlayerComponent_t>()[0];
    auto entidadPl = manager.getEntityByID(player.getEntityID());
    auto* inpPlayer = entidadPl->getComponent<InputComponent_t>();
    //He actualizado el childs temporal
    if(entidadPl){
        auto phyPl = entidadPl->getComponent<PhysicsComponent_t>(); //Física del player
        auto dirPl = entidadPl->getComponent<DirecComponent_t>(); //Direccion del personaje
        auto items = entidadPl->getComponent<ItemComponent_t>(); //Items del personaje
        auto entidadCh = manager.getEntityByID(player.temporal);
        if(entidadCh && player.temporal != 0){
            auto phyCh = entidadCh->getComponent<PhysicsComponent_t>();
            phyCh->x = phyPl->x;
            phyCh->y = phyPl->y + phyCh->inity;
            phyCh->z = phyPl->z;
            //std::cout << "Donde estaba: " << phyCh->x << " " << phyCh->y << " " << phyCh->z << " " << std::endl;
            //Si hay un temporal tenemos que cambiar el estado de arma antes
            //auto entidadArma = manager.getEntityByID(items->m_seleccionado);
            //if(entidadArma){
            //    auto renArma = entidadArma->getComponent<RenderComponent_t>();
            //    renArma->isVisible = false;
            //}        
        }
        //Sacamos el arma que tiene seleccionada el personaje
        auto entidadArma = manager.getEntityByID(2);
        auto phyArma = entidadArma->getComponent<PhysicsComponent_t>();
        if(entidadArma && items->m_seleccionado != Weapons_utilities::Pocion && inpPlayer->leftclick == true){
            auto renArma = entidadArma->getComponent<RenderComponent_t>();
            phyArma->x = phyPl->x;
            phyArma->y = phyPl->y;
            phyArma->z = phyPl->z;
            if(dirPl->dirPrevia == 1){
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = -90; 
            }else if(dirPl->dirPrevia == 2){
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = 90; 
            }else if(dirPl->dirPrevia == 3){
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = 0; 
            }else if(dirPl->dirPrevia == 4){
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = 180; 
            }else if(dirPl->dirPrevia == 5){
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = -45; 
            }else if(dirPl->dirPrevia == 6){
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = 45; 
            }else if(dirPl->dirPrevia == 7){
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = 225; 
            }else{
                phyArma->rx = 90; phyArma->ry = 0; phyArma->rz = 135; 
            }
        }
    }

}

void PhysicsSystem_t::positionChangePlayer(EventInfo info) {
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
        if(e){
            auto phy = e->getComponent<PhysicsComponent_t>();
            auto direc = e->getComponent<DirecComponent_t>();
            if(phy && direc){
                //Hay q cambiar la posicion del bullet no esta
                switch (direc->dirPrevia){
                case 1:
                    phy->x -= 2;
                    //bullet_t->moveKinematicObject(5,0.0,0.0);
                    break;
                case 2:
                    phy->x += 2;
                    //bullet_t->moveKinematicObject(-5,0.0,0.0);
                    break;
                case 3:
                    phy->z -= 2;
                    //bullet_t->moveKinematicObject(0.0,0.0,5);
                    break;
                case 4:
                    phy->z += 2;
                    //bullet_t->moveKinematicObject(0.0,0.0,-5);
                    break;
                default: //Si es -1 va al default que no debe realizar nada
                    break;
                }
            }
        }
}

void PhysicsSystem_t::teleport(EventInfo) const{
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
    auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
    if(e && e->template getComponent<PhysicsComponent_t>()){
        auto* phycmp = e->template getComponent<PhysicsComponent_t>();
        phycmp->x = 0.9;  phycmp->z = 920.5;
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
                    phy->x = info.posX + 12;
                    phy->zonex = info.posX + 12;
                    break;
                case 2:
                    phy->x = info.posX - 12;
                    phy->zonex = info.posX - 12;
                    break;
                case 3:
                    phy->z = info.posZ + 12;
                    phy->zonez = info.posZ + 12;
                    break;
                case 4:
                    phy->z = info.posZ - 12;
                    phy->zonez = info.posZ - 12;
                    break;
                case 5:
                    phy->z = info.posZ + 12;
                    phy->x = info.posX + 12;
                    phy->zonez = info.posZ + 12;
                    phy->zonex = info.posX + 12;
                    break;
                case 6:
                    phy->z = info.posZ + 12;
                    phy->x = info.posX - 12; 
                    phy->zonez = info.posZ + 12;
                    phy->zonex = info.posX - 12;
                    break;
                case 7:
                    phy->z = info.posZ - 12;
                    phy->x = info.posX + 12;
                    phy->zonez = info.posZ - 12;
                    phy->zonex = info.posX + 12;
                    break;
                case 8:
                    phy-> z = info.posZ - 12;
                    phy-> x = info.posX - 12;
                    phy->zonez = info.posZ - 12;
                    phy->zonex = info.posX - 12;
                    break;
                default: //Si es -1 va al default que no debe realizar nada
                    break;
                }
                phy->initx = phy->x;
                phy->inity = phy->y;
                phy->initz = phy->z;
            }
        }
}

void PhysicsSystem_t::isRunning(EventInfo){
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
    auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
    if(e && e->template getComponent<PhysicsComponent_t>()){
        auto* phycmp = e->template getComponent<PhysicsComponent_t>();
        phycmp->vx = phycmp->vz = 0.75;
    }
}

void PhysicsSystem_t::notRunning(EventInfo){
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
    auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
    if(e && e->template getComponent<PhysicsComponent_t>()){
        auto* phycmp = e->template getComponent<PhysicsComponent_t>();
        phycmp->vx = phycmp->vz = 0.45;
    }
}

float distanceObjTutorial(PhysicsComponent_t& obj){
    //auto phyCmp = entidad->getComponent<PhysicsComponent_t>();
    auto distance = [](PhysicsComponent_t& a, PhysicsComponent_t& b){
        return sqrtf((a.x - b.initx)*(a.x - b.initx)
            + (a.y - b.inity)*(a.y - b.inity) 
            + (a.z - b.initz)*(a.z - b.initz));
    };
    return distance(obj,obj);
}

void PhysicsSystem_t::RunningTren() const{
    Entity_t* entidad { nullptr };
    for(auto& phycmp : manager.getComponents<PhysicsComponent_t>()){
            entidad = manager.getEntityByID(phycmp.getEntityID());
            if(entidad && entidad->getName().compare(0,4,"tren") == 0){
                phycmp.vx = -2;
                phycmp.x += phycmp.vx;
                auto distancia = distanceObjTutorial(phycmp);
                if(distancia >= 250){
                    phycmp.x = phycmp.initx;
                    phycmp.y = phycmp.inity;
                    phycmp.z = phycmp.initz; 
                }
            }else if (entidad && entidad->getName().compare(0,9,"engranaje") == 0){
                if(phycmp.pendulo){
                    if(phycmp.x <= -60){
                        phycmp.pendulo = false;
                    }
                    phycmp.vx = -1;
                }else{
                    if(phycmp.x >= 40){
                        phycmp.pendulo = true;
                    }
                    phycmp.vx = 1;
                }
                phycmp.rx = 90;
                phycmp.rz = 90;
                phycmp.x += phycmp.vx;
            }else if (entidad && entidad->getName().compare(0,4,"seta") == 0){
                if(read == false){
                    NavMesh_t navmesh;
                    navmesh.Load("src/NavmeshZona_1.obj");
                    AStar astar(navmesh,1,3);
                    astar.SearchAStar();
                    auto resultado = astar.getPosicionRes();
                    for(unsigned int i = 0; i < resultado.size(); i++){
                        //std::cout << "Resultado : " << resultado[i].m_x << " " <<  resultado[i].m_y << " " <<  resultado[i].m_z << std::endl;
                    }
                    read = true;
                }
            }
    }
  
    //auto distancia = distance(phyCmp,phyCmp);
}

void PhysicsSystem_t::playerDead(EventInfo) const{
    auto& inpcmp = manager.getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
    auto* e = manager.getEntityByID(inpcmp[0].getEntityID());
    EventInfo info;
    auto* cmpPlayer = e->getComponent<PlayerComponent_t>();
    if(cmpPlayer->ruta_player == "Zonas/Bosque/"){
        info.ruta = "Zonas/Bosque/";
        info.zona = "zone_1";
    }else{
        info.ruta = "Zonas/Tutorial/";
        info.zona = "Habitacion_1";
    }

    EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
    EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
    EventManager::getInstancia().addEvent(Event{EventType::Change_ruta,info});
    EventManager::getInstancia().addEvent(Event{EventType::Change_zona,info});
    EventManager::getInstancia().addEvent(Event{EventType::Read_Level,info});//leo la nueva zona del json
    EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
}

void PhysicsSystem_t::addEventListeners(){
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Probando,std::bind(&PhysicsSystem_t::probando,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_W,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_A,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_S,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_D,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WD,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WA,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SD,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SA,std::bind(&PhysicsSystem_t::switchDirection,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::NewZone,std::bind(&PhysicsSystem_t::positionChangeZone,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Change_Position_Attacked,std::bind(&PhysicsSystem_t::positionChangePlayer,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_Shift,std::bind(&PhysicsSystem_t::isRunning,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Release_Shift,std::bind(&PhysicsSystem_t::notRunning,this,std::placeholders::_1)));    
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Player_Dead,std::bind(&PhysicsSystem_t::playerDead,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Teleport,std::bind(&PhysicsSystem_t::teleport,this,std::placeholders::_1)));
}