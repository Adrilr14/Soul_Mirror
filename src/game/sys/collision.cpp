#include "collision.hpp"
#include "../../game/cmp/RenderComponent.hpp"
#include "../../game/cmp/PhysicsComponent.hpp"
#include "../../game/cmp/CollisionComponent.hpp"
#include "../../game/cmp/InputComponent.hpp"
#include "../../game/cmp/DirecComponent.hpp"
#include "../../game/cmp/ShootComponent.hpp"
#include "../../game/cmp/IAComponent.hpp"
#include "../../game/cmp/StaticComponent.hpp"
#include "../../game/cmp/EnemyComponent.hpp"
#include "../../EventManager/EventManager.hpp"
#include <iostream>



std::vector<std::string> splitPattern(const std::string_view s,const char* delimiter){
    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> resultados;

    while(posFound >= 0){
        posFound = s.find(delimiter, posInit);
        splitted = s.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        resultados.push_back(splitted);
    }

    return resultados;
}

void CollisionSystem_t::collisionZone(){
    for(auto& col : manager.getComponents<CollisionComponent_t>()){
        auto* entity = manager.getEntityByID(col.getEntityID());
        auto nameEntity = entity->getName();

        if(nameEntity.compare(0,4,"zone") == 0){
            //Si encontramos una entidad del tipo Zona comprobaremos si hay collision con ella
            //auto colbool = bullet_t->hasCollision(nameEntity);
                //Lanzar un evento para cambiar la posicion del personaje dependiendo de la direccion
                //Despues de hacer eso cambiar de zona.
                //Descubirmos la direccion a la que va para poder saber a la zona a la que se dirige
                auto inp = manager.getComponents<InputComponent_t>()[0];
                auto character = manager.getEntityByID(inp.getEntityID());
                if(character){
                    auto colbool = Collision(character,entity);
                    if(colbool){
                        auto direc = character->getComponent<DirecComponent_t>();
                        if(direc){
                            std::string numZona = "";
                            if(direc->dirPrevia == 3){
                                numZona = splitPattern(nameEntity,"_")[1];
                            }else if(direc->dirPrevia == 2){
                                numZona = splitPattern(nameEntity,"_")[1];
                            }else{
                                numZona = splitPattern(nameEntity,"_")[2];
                            }

                            if(numZona != ""){
                                std::cout << "COLICHIONA \n";
                                EventInfo info;
                                info.zone = std::stoi(numZona);
                                //bullet_t->clearScene();
                                EventManager::getInstancia().addEvent(Event{EventType::NewZone});//borro todas las entidades del motor grafico
                                EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
                                EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
                                EventManager::getInstancia().addEvent(Event{EventType::Change_Zone,info});//leo la nueva zona del json
                                EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
                        }
                    }
                }
            }
        }
    }
}

bool CollisionSystem_t::Collision(Entity_t* first,Entity_t* second){
    //Para saber si colisionan primero tenemos que obtener:
    //Posiciones y dimensiones de las entidades
    auto fD = first->getComponent<RenderComponent_t>();
    auto sD = second->getComponent<RenderComponent_t>();

    auto fP = first->getComponent<PhysicsComponent_t>();
    auto sP = second->getComponent<PhysicsComponent_t>();

    std::cout << " La posicion que me llega :  " << fP->x << "  " << fP->z << std::endl;

    if(fD && sD && fP && sP){
        //Ahora que ya hemos comprobado que tiene tanto componente de Dimension como de Fisica hacemos:
        auto [fh,fw,fl] = fD->getData();
        auto [sh,sw,sl] = sD->getData();

        //Ejes en X
        auto fMinx = fP->x - (fw/2);
        auto fMaxx = fP->x + (fw/2);

        auto sMinx = sP->x - (sw/2);
        auto sMaxx = sP->x + (sw/2);

        //Ahora hacemos un if comprobando si colisionan en x; Si colisiona seguimos comprobando
        //Si no paramos porque para que vamos a seguir haciendo calculos innecesarios

        if(fMinx <= sMaxx && fMaxx >= sMinx){

            //Ejes en Y
            auto fMiny = fP->y - (fh/2);
            auto fMaxy = fP->y + (fh/2);

            auto sMiny = sP->y - (sh/2);
            auto sMaxy = sP->y + (sh/2);

            if(fMiny <= sMaxy && fMaxy >= sMiny){

                //Ejes en Z
                auto fMinz = fP->z - (fl/2);
                auto fMaxz = fP->z + (fl/2);

                auto sMinz = sP->z - (sl/2);
                auto sMaxz = sP->z + (sl/2);

                if(fMinz <= sMaxz && fMaxz >= sMinz){
                    //Colisionan
                    std::cout << "COCOCOCOLISIONAAAA";
                    return true;
                }
            }
        }
    }
    return false;
}

void CollisionSystem_t::collisionStatics(){
    auto& inpCmp = manager.getComponents<InputComponent_t>()[0];
    auto* player = manager.getEntityByID(inpCmp.getEntityID());
    if(player){
        //Sacamos el componente de físicas y guardamos sus valores en una varible temporal
        auto direction = player->getComponent<DirecComponent_t>();
        auto physics = player->getComponent<PhysicsComponent_t>();
        auto posicionX = physics->x; auto posicionZ = physics->z;
        //Aumentamos su rango para saber si va a colisionar con algo estatico
        //Luego se lo restablecemos
        //Tenemos que ver en que direccion va para sumarle 2 por ejemplo en esa direccion
        if(direction->dirPrevia == 1){
            physics->x += 1;
        }else if(direction->dirPrevia == 2){
            physics->x -= 1;
        }else if(direction->dirPrevia == 3){
            physics->z += 1;
        }else if(direction->dirPrevia == 4){
            physics->x -= 1;
        }else if(direction->dirPrevia == 5){
            physics->x += 1;
            physics->z += 1;
        }else if(direction->dirPrevia == 6){
            physics->x -= 1;
            physics->z += 1;
        }else if(direction->dirPrevia == 7){
            physics->x += 1;
            physics->z -= 1;
        }else{
            physics->x -= 1;
            physics->z -= 1;
        }
        std::cout << " La posicion que le pongo :  " << physics->x << "  " << physics->z << std::endl;


        //std::cout << "El dir COL ESTE ES : " << direction->dirCollision << std::endl;
        for(auto& statics : manager.getComponents<StaticComponent_t>()){
            auto* entSt = manager.getEntityByID(statics.getEntityID());
            if(entSt){
                bool col = Collision(player,entSt);
                if(col){
                    //Si colisiona ponemos la variable dirCollision al valor de la varible dirPrevia
                    direction->dirCollision = direction->dirPrevia;
                    break;
                }else{
                    direction->dirCollision = -1;
                }
            }
        }
        physics->x = posicionX; physics->z = posicionZ; 
    }
}

void CollisionSystem_t::update(){
    CollisionSystem_t::collisionZone();
    collisionStatics();
    //CollisionSystem_t::collisionStatics();
    for(auto& shoots : manager.getComponents<ShootComponent_t>()){
        auto* fshoot = manager.getEntityByID(shoots.getEntityID());
        if(fshoot){
            for(auto& ia : manager.getComponents<IAComponent_t>()){
                auto* iaent = manager.getEntityByID(ia.getEntityID());
                if(iaent){
                    bool colisiona = CollisionSystem_t::Collision(fshoot,iaent);
                    if(colisiona){
                        //Borramos la entidad 
                        std::cout << "Borramos la entidad" << std::endl;
                        manager.destroyEntityByID(iaent->getEntityID());
                        EventInfo info;
                        info.id = iaent->getEntityID();
                        EventManager::getInstancia().addEvent(Event{EventType::Remove_Entity_MG});
                    }
                }
            }
        }
    }
    //for(auto& inp : manager.getComponents<InputComponent_t>()){
    //    for(auto& col : manager.getComponents<CollisionComponent_t>()){
    //        auto* character = manager.getEntityByID(inp.getEntityID());    
    //        if(character && character->getComponent<CollisionComponent_t>() 
    //                     && character->getComponent<DimensionsComponent_t>()
    //                     && character->getComponent<PhysicsComponent_t>())
    //        {
    //            //Si se compone del personaje y tiene todos esos componentes entonces
    //            
    //            auto* objcollider = manager.getEntityByID(col.getEntityID());
    //            if(objcollider && objcollider->getComponent<PhysicsComponent_t>()
    //                           && objcollider->getComponent<DimensionsComponent_t>())
    //            {           
    //                if(character->getEntityID() != objcollider->getEntityID()){
    //                    CollisionSystem_t::Collision(*character,*objcollider);
    //                }
    //            }
    //        }
    //    }
    //}    
}

//Accion: Espadazo attatck
void CollisionSystem_t::SwordAttack(EventInfo info){
    //Primero comprobamos cogemos la entidad de la espada que le hemos pasado por parametro
    std::cout << "Colision ataq" << std::endl;
    auto* espada = manager.getEntityByID(info.id); //Entidad del arma
    if(espada){
        for(auto& enemies : manager.getComponents<EnemyComponent_t>()){
            auto* enemy = manager.getEntityByID(enemies.getEntityID());
            std::cout << "Entro";
            bool colision = CollisionSystem_t::Collision(espada,enemy);
            if(colision){
                std::cout << "Se produce una colision \n";
            }
        }
    }
}

void CollisionSystem_t::ShieldDefense(EventInfo info){
    //El escudo se encargara de parar tanto balas como a los enemigos que se acerquen
    //IMPLEMENTAR QUE LOS ENEMIGOS SE DETENGAN
    auto* escudo = manager.getEntityByID(info.id);
    if(escudo){
        for(auto& shoots : manager.getComponents<ShootComponent_t>()){
            auto* shoot = manager.getEntityByID(shoots.getEntityID());
            bool colision = CollisionSystem_t::Collision(escudo,shoot);
            if(colision){
                //Borramos la entiedad del shoot pq el escudo ha protegido al jugador
                //DEBERIAMOS DE MARCAR LA ENTIDAD PARA BORRAR AL FINAL
                manager.destroyEntityByID(shoot->getEntityID());
            }
        }
    }
}

void CollisionSystem_t::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Collision_Sword,std::bind(&CollisionSystem_t::SwordAttack,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Collision_Shield,std::bind(&CollisionSystem_t::ShieldDefense,this,std::placeholders::_1)));
}