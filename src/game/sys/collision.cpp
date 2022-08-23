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
#include "../../game/cmp/ItemComponent.hpp"
#include "../../game/cmp/HPComponent.hpp"
//#include "../../game/cmp/OBBComponent.hpp"
#include "../../game/cmp/PlayerComponent.hpp"
#include "../../EventManager/EventManager.hpp"
#include <numeric>
#include <vec3.hpp> // glm::vec3
#include <vec4.hpp> // glm::vec4
#include <mat3x3.hpp> // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <iostream>
#include <glfw3.h>


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

    auto inp = manager.getComponents<InputComponent_t>()[0];
    auto character = manager.getEntityByID(inp.getEntityID());

    if(character){
        auto direction = character->getComponent<DirecComponent_t>();
        auto physics = character->getComponent<PhysicsComponent_t>();
        auto posicionX = physics->x; auto posicionZ = physics->z;
        //std::cout << "Posicion x e z" << posicionX << " " << posicionZ << std::endl;
       if(direction && physics){
            if(direction->dirPrevia == 1){
            physics->x += 1;
        }else if(direction->dirPrevia == 2){
            physics->x -= 1;
        }else if(direction->dirPrevia == 3){
            physics->z += 1;
        }else if(direction->dirPrevia == 4){
            physics->z -= 1;
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
       }
    for(auto& col : manager.getComponents<CollisionComponent_t>()){
        auto* entity = manager.getEntityByID(col.getEntityID());
        auto nameEntity = entity->getName();
        if(nameEntity.compare(0,4,"zone") == 0 || nameEntity.compare(0,10,"Habitacion") == 0){
            //Si encontramos una entidad del tipo Zona comprobaremos si hay collision con ella
            //auto colbool = bullet_t->hasCollision(nameEntity);
                //Lanzar un evento para cambiar la posicion del personaje dependiendo de la direccion
                //Despues de hacer eso cambiar de zona.
                //Descubirmos la direccion a la que va para poder saber a la zona a la que se dirige
                    auto colbool = Collision(character,entity);
                    if(colbool){
                        auto* phyzone = entity->getComponent<PhysicsComponent_t>();
                        EventInfo info;
                        info.posX = phyzone->x; info.posZ = phyzone->z;
                        auto direc = character->getComponent<DirecComponent_t>();
                        if(direc){
                            auto numZona = splitPattern(nameEntity,"_");

                            if(numZona.size() > 0){
                                info.zona = numZona[0] + "_" + numZona[1];
                                //bullet_t->clearScene();
                                EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
                                EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
                                EventManager::getInstancia().addEvent(Event{EventType::Read_Level,info});//leo la nueva zona del json
                                EventManager::getInstancia().addEvent(Event{EventType::Change_zona,info});//leo la nueva zona del json
                                EventManager::getInstancia().addEvent(Event{EventType::NewZone,info});//borro todas las entidades del motor grafico
                                EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
                        }
                    }
                }
            }
        }
        physics->x = posicionX; physics->z = posicionZ;
    }

}

bool CollisionSystem_t::Collision(Entity_t* first,Entity_t* second){
    //Para saber si colisionan primero tenemos que obtener:
    //Posiciones y dimensiones de las entidades
    auto fD = first->getComponent<RenderComponent_t>();
    auto sD = second->getComponent<RenderComponent_t>();

    auto fP = first->getComponent<PhysicsComponent_t>();
    auto sP = second->getComponent<PhysicsComponent_t>();

    if(fD && sD && fP && sP){
        //Ahora que ya hemos comprobado que tiene tanto componente de Dimension como de Fisica hacemos:
        auto [fh,fw,fl] = fD->getData();
        auto [sh,sw,sl] = sD->getData();

        auto [rxf,ryf,rzf] = fP->getRotations();
        auto [rxs,rys,rzs] = sP->getRotations();


        //std::cout << "HEIGHT WIDTH LENGTH : " << fh << " " << fw << " " << fl << std::endl;
        //std::cout << "HEIGHT WIDTH LENGTH : " << sh << " " << sw << " " << sl << std::endl;
//
        //std::cout << "NOMBRE DE LA ENTIDAD :" << first->getName() << "Las rotaciones fP: " << rxf << " " << ryf << " " << rzf << " " << std::endl;
        //std::cout << "NOMBRE DE LA ENTIDAD :" << second->getName() << "Las rotaciones sP: " << rxs << " " << rys << " " << rzs << " " << std::endl;

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

                //std::cout << "fMinz : " << fMinz << std::endl;
                //std::cout << "fMaxz : " << fMaxz << std::endl;
//
                //std::cout << "sMinz : " << sMinz << std::endl;
                //std::cout << "sMaxz : " << sMaxz << std::endl;
                if(fMinz <= sMaxz && fMaxz >= sMinz){
                    //Colisionan
                    //std::cout << "COCOCOCOLISIONAAAA";
                    return true;
                }
            }
        }
    }
    return false;
}

int CollisionSystem_t::IntersectionOBBOBB(Entity_t* first,Entity_t* second) const {
//    auto obbFirst = first->getComponent<OBBComponent_t>();
//    auto obbSecond = second->getComponent<OBBComponent_t>();
//
//    auto physicsFirst = first->getComponent<PhysicsComponent_t>();
//    auto physicsSecond = second->getComponent<PhysicsComponent_t>();
//
//    if(obbFirst && obbSecond && physicsFirst && physicsSecond){
//        float ra,rb;
//        glm::mat3x3 R,AbsR;
//
//        glm::vec3 firstU = glm::vec3(physicsFirst->x,physicsFirst->y,physicsFirst->z);
//        glm::vec3 secondU = glm::vec3(physicsSecond->x,physicsSecond->y,physicsSecond->z);
//
//
//        //Compute rotation matrix expressing b in a's coordinate frame
//        for(unsigned int i = 0; i < 3; i++){
//            for(unsigned int j = 0; j < 3; j++){
//                R[i][j] = firstU[i]*secondU[j];
//            }
//        }
//
//        //Compute traslation vector t
//        //Son points que son double
//        auto t = obbSecond->c - obbFirst->c;
//        //Bring traslation into a's coordeinate frame
//
//        t = glm::vec3(t*firstU[0],t*firstU[2],t*firstU[2]); //No se pq hay 2 doses ahi
//
//        for(unsigned int i = 0; i < 3; i++){
//            for(unsigned int j = 0; j < 3; j++){
//                AbsR[i][j] = abs(R[i][j]) + FLT_EPSILON;
//            }
//        }
//
//        //Test axes L = A0, L = A1, L = A2
//        for(unsigned int i = 0; i < 3; i++){
//            ra = obbFirst->e[i];
//            rb = obbSecond->e[0] * AbsR[i][0] + obbSecond
//        }
//
//    }
}


bool CollisionSystem_t::Collision(Entity_t* first,Entity_t* second, int direc){
    //Para saber si colisionan primero tenemos que obtener:
    //Posiciones y dimensiones de las entidades
    //std::cout<<"entro aqui joder\n";
    //std::cout<<"los valores: "<<sumaDimensionX<<" "<<sumaDimensionZ<<"\n";
    auto fD = first->getComponent<RenderComponent_t>();
    auto sD = second->getComponent<RenderComponent_t>();

    auto fP = first->getComponent<PhysicsComponent_t>();
    auto sP = second->getComponent<PhysicsComponent_t>();

    if(fD && sD && fP && sP){
        //Ahora que ya hemos comprobado que tiene tanto componente de Dimension como de Fisica hacemos:
        auto [fh,fw,fl] = fD->getData();
        auto [sh,sw,sl] = sD->getData();

        auto [rxf,ryf,rzf] = fP->getRotations();
        auto [rxs,rys,rzs] = sP->getRotations();
        float fMinx, fMaxx, fMinz, fMaxz;
        fMinx = fMaxx = fMinz = fMaxz = 0;
        //Ejes en X
        if(direc == 1 || direc == 5 || direc == 7){
            fMinx = (fP->x + 1) - (fw/2);
            fMaxx = (fP->x + 1) + (fw/2);
        }
        else if(direc == 2 || direc == 6 || direc == 8){
            fMinx = (fP->x - 1) - (fw/2);
            fMaxx = (fP->x - 1) + (fw/2);
        }
        else{
            fMinx = fP->x - (fw/2);
            fMaxx = fP->x + (fw/2);
        }
        //auto fMinx = fP->x - (fw/2);
        //auto fMaxx = fP->x + (fw/2);

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
                if(direc == 3 || direc == 5 || direc == 6){
                    fMinz = (fP->z + 1) - (fl/2);
                    fMaxz = (fP->z + 1) + (fl/2);
                }
                else if(direc == 4 || direc == 7 || direc == 8){
                    fMinz = (fP->z - 1) - (fl/2);
                    fMaxz = (fP->z - 1) + (fl/2);
                }
                else{
                    fMinz = fP->z - (fl/2);
                    fMaxz = fP->z + (fl/2);
                }
                //auto fMinz = fP->z - (fl/2);
                //auto fMaxz = fP->z + (fl/2);

                auto sMinz = sP->z - (sl/2);
                auto sMaxz = sP->z + (sl/2);

                if(fMinz <= sMaxz && fMaxz >= sMinz)
                    return true;

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
        Vector3D directionValues = direction->getValuesDirection(direction->dirPrevia);
        physics->x += directionValues.m_x;
        physics->z += directionValues.m_z;


        //std::cout << "El dir COL ESTE ES : " << direction->dirCollision << std::endl;
        for(auto& statics : manager.getComponents<StaticComponent_t>()){
            auto* entSt = manager.getEntityByID(statics.getEntityID());
            if(entSt){
                bool col = Collision(player,entSt);
                if(col){
                    //std::cout << "Colisiona la entidad -> " << player->getName() << std::endl;
                    //std::cout << "Con -> " << entSt->getName() << std::endl;
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

void CollisionSystem_t::collisionEnemy(){

    auto player = manager.getComponents<InputComponent_t>()[0];
    auto* ent = manager.getEntityByID(player.getEntityID()); //Entidad del player
    auto* phyplayer = ent->getComponent<PhysicsComponent_t>(); //Física del player
    auto* phycmp = ent->getComponent<PlayerComponent_t>(); //Componente player

    auto* entidadCube = manager.getEntityByID(2);
    double now = glfwGetTime();

    if(phycmp && phycmp->inmunity == false){
        double now = glfwGetTime();
            if(ent){
                //std::cout << "Entra 2 " << std::endl;
                for(auto& enemys : manager.getComponents<EnemyComponent_t>()){
                    auto entEnemy = manager.getEntityByID(enemys.getEntityID());
                    if(entEnemy){
                        auto* itemscmp = ent->getComponent<ItemComponent_t>();
                        if(CollisionSystem_t::Collision(entEnemy,entidadCube)){
                            break;
                        }
                        bool col = CollisionSystem_t::Collision(entEnemy,ent); //Entidad del enemigo y del player
                        if(col){
                            //std::cout<<"colisiono con la aranya bitch\n";
                            phycmp->inmunity = true;
                            auto* iacmp = entEnemy->getComponent<IAComponent_t>();
                            if(iacmp){
                                if(iacmp->type == 2){
                                    EventManager::getInstancia().addEvent(Event{EventType::Enemy_Spider});
                                    auto* phyenemy = entEnemy->getComponent<PhysicsComponent_t>();
                                    if(phyenemy->x < phyplayer->x)
                                        phyenemy->x -= 3;
                                    else
                                        phyenemy->x += 3;
                                    if(phyenemy->z < phyplayer->z)
                                        phyenemy->z -= 3;
                                    else
                                        phyenemy->z += 3;
                                }
                            }
                            //std::cout << "Entra 4 " << std::endl;
                            //Sacamos el Componente de HP del personaje
                            auto hpPlayer = ent->getComponent<HPComponent_t>();
                            if(hpPlayer){
                                //Le resto a la vida que tiene el daño que le inflige el enemigo en concreto
                                hpPlayer->life -= enemys.damage;
                                //std::cout << "Vida  : " << hpPlayer->life << std::endl;
                                if(hpPlayer->life < 0){
                                    hpPlayer->life = 0;
                                }
                                EventManager::getInstancia().addEvent(Event{EventType::Herida});
                                EventManager::getInstancia().addEvent(Event{EventType::herida_Animation});
                                //Lanzamos un evento para cambiar la posicion del personaje porque sino estará
                                //colisionando todo el rato y el personaje morirá enseguida
                                //EventManager::getInstancia().addEvent(Event{EventType::Change_Position_Attacked});//borro todas las entidades del motor grafico
                                //std::cout << "Colisiona con el enemigo" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    if(now - before >= 1.0){
        before = now;
        phycmp->inmunity = false;
    }
}


void CollisionSystem_t::collisionBalas(){
    bool control = false;
    double now = glfwGetTime();
    for(auto& shoots : manager.getComponents<ShootComponent_t>()){
        auto* fshoot = manager.getEntityByID(shoots.getEntityID());
        if(fshoot){
            switch(shoots.type){
                case Balatype::playershot :
                    for(auto& enemys : manager.getComponents<EnemyComponent_t>()){
                        auto* enemyent = manager.getEntityByID(enemys.getEntityID());
                        if(enemyent){
                            auto col = Collision(fshoot,enemyent);
                            if(col){
                                EventManager::getInstancia().addEvent(Event{EventType::Colision_Flecha});
                                fshoot->SetEntityToDestroy();
                                auto* hp = enemyent->getComponent<HPComponent_t>();
                                auto* ia = enemyent->getComponent<IAComponent_t>();
                                if(hp && ia && ia->type != IAType::erizo){
                                    enemyent->getComponent<RenderComponent_t>()->texturePathDamage = "media/Texturas/Personaje/Damage/Damage";
                                    hp->life -= shoots.baseDamage;
                                }
                                control = true;
                                break;
                            }
                        }
                    }
                    if(!control){
                    //ahora con el resto de cosas del entorno (las static)
                        for(auto& statics : manager.getComponents<StaticComponent_t>()){
                            auto* staticent = manager.getEntityByID(statics.getEntityID());
                            if(staticent){
                                auto col = Collision(fshoot,staticent);
                                if(col && fshoot->getEntityID() != staticent->getEntityID()){
                                    EventManager::getInstancia().addEvent(Event{EventType::Colision_Flecha});
                                    fshoot->SetEntityToDestroy();
                                    break;
                                }
                            }
                        }
                    }
                break;

                case Balatype::enemyshot:
                    //std::cout<<"balas tipo2\n";
                    for(auto& player : manager.getComponents<PlayerComponent_t>()){
                        auto* playerent = manager.getEntityByID(player.getEntityID());
                        if(playerent && player.inmunity == false){
                            auto col = Collision(fshoot, playerent);
                            if(col){
                                player.inmunity = true;
                                auto* hp = playerent->getComponent<HPComponent_t>();
                                hp->life -= shoots.baseDamage;
                                fshoot->SetEntityToDestroy();
                                EventManager::getInstancia().addEvent(Event{EventType::Herida});
                                EventManager::getInstancia().addEvent(Event{EventType::herida_Animation});
                                control = true;
                                break;
                            }
                        }
                    }
                    if(!control){
                        for(auto& sta : manager.getComponents<StaticComponent_t>()){
                            auto* staticent = manager.getEntityByID(sta.getEntityID());
                            if(staticent && staticent->getComponent<EnemyComponent_t>() == nullptr){
                                if(fshoot->getEntityID() != staticent->getEntityID()){
                                    bool colisiona = Collision(fshoot,staticent);
                                    if(colisiona){
                                        fshoot->SetEntityToDestroy();
                                        break;
                                    }
                                }
                            }
                        }
                    }
                break;
            }
        }
    }
    if(now - beforeBalas >= 1.0){
        beforeBalas = now;
        for(auto& player : manager.getComponents<PlayerComponent_t>()){
            player.inmunity = false;
        }
    }
}


void CollisionSystem_t::update(){
    CollisionSystem_t::collisionZone();
    CollisionSystem_t::collisionEnemy();
    CollisionSystem_t::DynamicsObjects();
    CollisionSystem_t::collisionStatics();
    CollisionSystem_t::collisionBalas();
}

//Accion: Espadazo attatck
void CollisionSystem_t::SwordAttack(EventInfo info){
    //Primero comprobamos cogemos la entidad de la espada que le hemos pasado por parametro
    //std::cout << "Colision ataq" << std::endl;
    auto* espada = manager.getEntityByID(info.id); //Entidad del arma
    if(espada){
        for(auto& enemies : manager.getComponents<EnemyComponent_t>()){
            auto* enemy = manager.getEntityByID(enemies.getEntityID());
            //std::cout << "Entro";
            bool colision = CollisionSystem_t::Collision(espada,enemy);
            if(colision){
                //Cogemos el component de vida del enemigo
                auto* hpEnemy = enemy->getComponent<HPComponent_t>();
                //Ahora necesitamos al player para coger el ataque de la espada
                auto& player = manager.getComponents<InputComponent_t>()[0];
                auto* entidadPlayer = manager.getEntityByID(player.getEntityID());
                if(hpEnemy && entidadPlayer){
                    auto* items = entidadPlayer->getComponent<ItemComponent_t>();
                    auto* ia = enemy->getComponent<IAComponent_t>();
                    if(items && ia && ia->type != IAType::erizo){
                        //std::cout << "HP enemy " << hpEnemy->life << std::endl;
                        //std::cout << "HDaño espada " << items->sword.damage << std::endl;
                        hpEnemy->life -= items->sword.damage;
                        enemy->getComponent<RenderComponent_t>()->texturePathDamage = "media/Texturas/Personaje/Damage/Damage";
                        if(hpEnemy->life <= 0.0){
                        //manager.destroyEntityECSMG(enemy->getEntityID());
                        enemy->SetEntityToDestroy();	                }
                        //    std::cout << "Me he cargado al enemgigoooooooooooooooooooooooooo" << std::endl;
                        }
                    }
                    EventManager::getInstancia().addEvent(Event{EventType::Corte});
                }
            }
        }
    }

void CollisionSystem_t::ShieldDefense(EventInfo info){
    //El escudo se encargara de parar tanto balas como a los enemigos que se acerquen
    //IMPLEMENTAR QUE LOS ENEMIGOS SE DETENGAN
    //std::cout << "Intento ver si colisiona con el personaje " << std::endl;
    auto* escudo = manager.getEntityByID(info.id);
    if(escudo){
        //std::cout << "Entro aqui " << escudo->getName() << std::endl;
        for(auto& shoots : manager.getComponents<ShootComponent_t>()){
            auto* shoot = manager.getEntityByID(shoots.getEntityID());
            if(shoots.type = Balatype::enemyshot){
                bool colision = CollisionSystem_t::Collision(escudo,shoot);
                if(colision){
                    //Borramos la entiedad del shoot pq el escudo ha protegido al jugador
                    //DEBERIAMOS DE MARCAR LA ENTIDAD PARA BORRAR AL FINAL
                    EventManager::getInstancia().addEvent(Event{EventType::Colision_Escudo});
                    //std::cout << "Colisiona con un flecha" << std::endl;
                    shoot->SetEntityToDestroy();
                }
            }
        }
    }
}

void CollisionSystem_t::DynamicsObjects(){

    auto player = manager.getComponents<PlayerComponent_t>()[0];
    auto* entidadPlayer = manager.getEntityByID(player.getEntityID());
    if(entidadPlayer){
        //Ahora que tenemos el player recorremos los dynamic Objects

        //Le sacamos al player el componente direccion y el de physics
        auto* dirPlayer = entidadPlayer->getComponent<DirecComponent_t>();
        auto* phyPlayer = entidadPlayer->getComponent<PhysicsComponent_t>();
        if(dirPlayer && phyPlayer){
            auto posicionX = phyPlayer->x; auto posicionZ = phyPlayer->z;

            if(dirPlayer->dirPrevia == 1){
                phyPlayer->x += 1;
            }else if(dirPlayer->dirPrevia == 2){
                phyPlayer->x -= 1;
            }else if(dirPlayer->dirPrevia == 3){
                phyPlayer->z += 1;
            }else if(dirPlayer->dirPrevia == 4){
                phyPlayer->z -= 1;
            }else if(dirPlayer->dirPrevia == 5){
                phyPlayer->x += 1;
                phyPlayer->z += 1;
            }else if(dirPlayer->dirPrevia == 6){
                phyPlayer->x -= 1;
                phyPlayer->z += 1;
            }else if(dirPlayer->dirPrevia == 7){
                phyPlayer->x += 1;
                phyPlayer->z -= 1;
            }else{
                phyPlayer->x -= 1;
                phyPlayer->z -= 1;
            }
            for(auto& dy : manager.getComponents<CollisionComponent_t>()){
                //Miramos si el jugador colisiona con alguno de estos objetos
                auto* entidadDy = manager.getEntityByID(dy.getEntityID());
                if(entidadDy){
                    if(Collision(entidadPlayer,entidadDy)){
                        //std::cout << "Colisiona la entidad -> " << entidadPlayer->getName() << std::endl;
                        //std::cout << "Con -> " << entidadDy->getName() << std::endl;

                        //Lo primero es identificar si se trata de una llave,puerta,cofre,etc...
                        auto splitted = splitPattern(entidadDy->getName(),"_");

                        if(splitted.size() > 1){
                                auto playerCmp = entidadPlayer->getComponent<PlayerComponent_t>();
                                if(splitted[1].compare(0,6,"bosque") == 0 && playerCmp->endgame == false){
                                    EventInfo info;
                                    info.ruta = "Zonas/Bosque/";
                                    info.zona = "zone_1";
                                    auto* playerCmp = entidadPlayer->getComponent<PhysicsComponent_t>();

                                    //EventManager::getInstancia().addEvent(Event{EventType::NewZone});//borro todas las entidades del motor grafico
                                    EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
                                    EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
                                    EventManager::getInstancia().addEvent(Event{EventType::Change_ruta,info});
                                    EventManager::getInstancia().addEvent(Event{EventType::Change_zona,info});
                                    EventManager::getInstancia().addEvent(Event{EventType::Read_Level,info});//leo la nueva zona del json
                                    EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
                                    //EventManager::getInstancia().addEvent(Event{EventType::Read_Level,info});
                                    info.ruta = "event:/Ambientes/industrial";
                                    EventManager::getInstancia().addEvent(Event{EventType::Stop_Music,info});
                                    EventManager::getInstancia().addEvent(Event{EventType::Bosque,info});
                                }else if(splitted[1].compare(0,6,"mirror") == 0){

                                    EventInfo info;
                                    info.ruta = "Zonas/Tutorial/";
                                    info.zona = "Habitacion_2";

                                    EventManager::getInstancia().addEvent(Event{EventType::Teleport});
                                    EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Render});//borro todas las entidades del motor grafico
                                    EventManager::getInstancia().addEvent(Event{EventType::Delete_Entities_Manager});//vacio el array de entitys y de cmps
                                    EventManager::getInstancia().addEvent(Event{EventType::Change_ruta,info});
                                    EventManager::getInstancia().addEvent(Event{EventType::Change_zona,info});
                                    EventManager::getInstancia().addEvent(Event{EventType::Read_Level,info});//leo la nueva zona del json
                                    EventManager::getInstancia().addEvent(Event{EventType::Render_Change_Zone});
                                }else if(splitted[0].compare(0,4,"door") ==  0 && splitted[1].compare(0,4,"arco") == 0){
                                    auto* items = entidadPlayer->getComponent<ItemComponent_t>();
                                    if(items->weapons[Weapons_utilities::Arco] == true){
                                        entidadDy->SetEntityToDestroy();
                                    }
                                }else if(splitted[0].compare(0,4,"door") ==  0 && splitted[1].compare(0,6,"muerte") == 0){
                                    if(manager.getComponents<EnemyComponent_t>().size() <= 2){
                                        entidadDy->SetEntityToDestroy();
                                    }
                                }
                                //else if(splitted[0].compare(0,4,"Caja") == 0){
                                //std::cout << "Entro 1 . 6\n";
                                //auto physicsDy = entidadDy->getComponent<PhysicsComponent_t>();
                                ////Nos guardamos la posicion para poder ponersela despues
                                //auto posX = physicsDy->x; auto posY = physicsDy->y; auto posZ = physicsDy->z;
                                ////Ahora que ya tenemos guardada la posicion lo que tenemos que hacer es mover la caja
                                ////Necesito la direccion del personaje
                                //std::cout << "Posicion con la que llega : " << posX << " " << posY << " " << posZ << std::endl;
                                //auto direcComponent = entidadPlayer->getComponent<DirecComponent_t>();
                                //Vector3D directionValue = direcComponent->getValuesDirection(direcComponent->dir);
                                //physicsDy->x += directionValue.m_x* 10;
                                //physicsDy->z += directionValue.m_z* 10;
                                //std::cout << "Posicion que se le asigna : " << physicsDy->x << " " << physicsDy->y << " " << physicsDy->z << std::endl;
                                ////Ahora comprobamos si colisiona
                                //bool colisiona = false;
                                //for(auto& statics : manager.getComponents<StaticComponent_t>()){
                                //    auto entidadStatic = manager.getEntityByID(statics.getEntityID());
                                //    if(entidadDy->getEntityID() != entidadStatic->getEntityID() && CollisionSystem_t::Collision(entidadDy,entidadStatic)){
                                //        std::cout << "Colisiona " << entidadDy->getName() << " con " <<  entidadStatic->getName() << std::endl;
                                //        colisiona = true;
                                //        break;
                                //    }
                                //}
                                //if(colisiona){
                                //    //Si colisiona dejamos la posicion en la posicion original
                                //        physicsDy->x = posX;
                                //        physicsDy->z = posZ;
                                //
                                //}else{
                                //    std::cout << "BBBBBBBBBB";
                                //}
                                //std::cout << "Posicion con la q se va : " << physicsDy->x << " " << physicsDy->y << " " << physicsDy->z << std::endl;
                            //}
                        }else{
                            auto* items = entidadPlayer->getComponent<ItemComponent_t>();
                            auto inpCmp = entidadPlayer->getComponent<InputComponent_t>();
                            auto playerCmp = entidadPlayer->getComponent<PlayerComponent_t>();
                            auto aux = playerCmp->zona_player;
                            //std::cout << "Zona_player : " << playerCmp->zona_player << std::endl;
                            if(items && inpCmp){
                                if(splitted[0].compare(0,5,"llave") == 0){
                                    //std::cout << "Entro 1 . 1\n";
                                    //Ahora sacamos los items del personaje
                                    items->keys.addKey();
                                    playerCmp->lista.insert(
                                        std::make_pair<std::string,std::string>(entidadDy->getName(),std::forward<std::string>(aux))
                                    );
                                    EventManager::getInstancia().addEvent(Event{EventType::Coger});
                                    manager.destroyEntityECSMG(entidadDy->getEntityID());
                                }
                                else if(entidadDy->getName().compare(0,6,"Pocion") == 0){
                                    //std::cout << "Entro 1 . 5\n";
                                    items->potion.numberPotions++;
                                    playerCmp->lista.insert(
                                        std::make_pair<std::string,std::string>(entidadDy->getName(),std::forward<std::string>(aux))
                                    );
                                    EventManager::getInstancia().addEvent(Event{EventType::Coger});
                                    entidadDy->SetEntityToDestroy();
                                }else if(entidadDy->getName().compare(0,5,"Cofre") == 0){
                                    if(inpCmp->keySpace){
                                        playerCmp->lista.insert(
                                                std::make_pair<std::string,std::string>(entidadDy->getName(),std::forward<std::string>(aux))
                                        );
                                        manager.destroyEntityECSMG(entidadDy->getEntityID());
                                    }
                                }else if(entidadDy->getName().compare(0,6,"barril") == 0){
                                    //std::cout << "Entro 1 . 4\n";
                                    /*Para el barril lo que deberia pasar es que cuando este colisionando
                                    con uno deberia salir en la pantalla informandote qe puedes pulsar una tecla
                                    . Si la pulsa entonces se pone en marcha todo el mecanismo.*/

                                    //EL BARRIL NO PUEDE ESTAR AQUI PORQUE SE ELIMINA LA ENTIDAD AL FINAL Y
                                    //SE PONE LA VISIBILIDAD EN FALSO CAMBIARLO DE SITIO!!
                                    //if(player.keyActivated){
                                        //Comprobamos que se ha presionado la tecla
                                        //Ahora tenemos que cambiarle la posicion del barril a la del personaje
                                        //Y sumarle +5 en el eje (y) para que este encima del persona
                                        if(inpCmp->keySpace){
                                            auto physicsDy = entidadDy->getComponent<PhysicsComponent_t>();
                                            auto physicsPlayer = entidadPlayer->getComponent<PhysicsComponent_t>();
                                            auto itemsPlayer = entidadPlayer->getComponent<ItemComponent_t>();
                                            auto playerChilds = entidadPlayer->getComponent<PlayerComponent_t>();
                                            //std::cout << "El temporal " <<  playerChilds->temporal << std::endl;
                                            if(physicsDy && physicsPlayer && playerChilds->temporal == 0){
                                                physicsDy->inity = 10;
                                                entidadPlayer->getComponent<PlayerComponent_t>()->addTemporal(entidadDy->getEntityID());
                                                EventManager::getInstancia().addEvent(Event{EventType::Coger});
                                            }
                                        }
                                    //}
                                }else if(entidadDy->getName().compare(0,4,"door") == 0){
                                    if(items->keys.Looking()){
                                        EventManager::getInstancia().addEvent(Event{EventType::Abrir_Puerta});
                                        playerCmp->lista.insert(
                                            std::make_pair<std::string,std::string>(entidadDy->getName(),std::forward<std::string>(aux))
                                        );
                                        entidadDy->SetEntityToDestroy();
                                    }
                                }else if(entidadDy->getName().compare(0,4,"arco") == 0){
                                    if(inpCmp->keySpace){
                                        items->weapons[Weapons_utilities::Arco] = true;
                                        EventManager::getInstancia().addEvent(Event{EventType::Coger});
                                        playerCmp->lista.insert(
                                            std::make_pair<std::string,std::string>(entidadDy->getName(),std::forward<std::string>(aux))
                                        );
                                        entidadDy->SetEntityToDestroy();
                                    }
                                }else if(entidadDy->getName().compare(0,9,"escalones") == 0){
                                    for(auto& col : manager.getComponents<CollisionComponent_t>()){
                                        auto* entidadKeyBosq = manager.getEntityByID(col.getEntityID());
                                        if(entidadKeyBosq->getName().compare(0,9,"keyBosque") == 0){
                                            entidadKeyBosq->SetEntityToDestroy();
                                        }
                                    }
                                    entidadDy->SetEntityToDestroy();
                                    EventManager::getInstancia().addEvent(Event{EventType::create_Espejo});
                                }
                                else if(entidadDy->getName().compare(0,10,"plataforma") == 0){
                                    auto& playercmp = manager.getComponents<PlayerComponent_t>();
                                    auto* player = manager.getEntityByID(playercmp[0].getEntityID());
                                    if(playercmp[0].endgame)
                                        EventManager::getInstancia().addEvent(Event{EventType::create_Deku});
                                }
                            }
                        }

                        //No hago un else if con el cofre porque lo unico que hara es desaparecer
                        //Faltan los power-ups

                        //Al final cambiamos la visibilidad del objeto a false
                        //Y finalmente destruimos la entidad para que no colisione todo el rato
                    }
                }
            }
            phyPlayer->x = posicionX; phyPlayer->z = posicionZ;
        }
    }
}

void CollisionSystem_t::collisionCaja(EventInfo){

    bool oumama { false };//si cuando acabe el metodo esto es true, MOVEREMOS EL OBJETO
    auto& direccmp = manager.getComponents<DirecComponent_t>()[0];
    auto* entityplayer = manager.getEntityByID(direccmp.getEntityID());
    if(entityplayer && entityplayer->getComponent<PhysicsComponent_t>()){
        auto* playerphy = entityplayer->getComponent<PhysicsComponent_t>();
        //una vez que tenemos el player, vamos a sacar la cajita
        for(auto& dy : manager.getComponents<CollisionComponent_t>()){
            //Miramos si el jugador colisiona con alguno de estos objetos
            auto* entidadDy = manager.getEntityByID(dy.getEntityID());
            //Entity_t* entidadPuerta { nullptr };
            //if(entidadDy->getName().compare(0,6,"Puerta") == 0){
            //    entidadPuerta =  entidadDy;
            //}
            if(entidadDy && entidadDy->getName().compare(0,4,"Caja") == 0){
                if(entidadDy && entidadDy->getComponent<PhysicsComponent_t>()){
                    auto collidefirst = Collision(entityplayer,entidadDy,direccmp.dirPrevia);
                    if(collidefirst){
                        //Comprobamos si colisiona con el Pedestal
                        //std::cout<<"entro aqui\n";
                        auto* cajitaphy = entidadDy->getComponent<PhysicsComponent_t>();
                        for(auto& staticent : manager.getComponents<StaticComponent_t>()){
                            auto* staticentity = manager.getEntityByID(staticent.getEntityID());
                            if(staticentity){
                                if(entidadDy->getEntityID() != staticentity->getEntityID()){
                                    auto collide = Collision(entidadDy,staticentity,direccmp.dirPrevia);
                                     if(collide){
                                        if(staticentity->getName().compare(0,5,"boton") == 0){
                                                auto phyCaja = entidadDy->getComponent<PhysicsComponent_t>();
                                                auto phyPede = staticentity->getComponent<PhysicsComponent_t>();
                                                phyCaja->x = phyPede->x; phyCaja->y = phyPede->y; phyCaja->z = phyPede->z;
                                                manager.destroyCMPByID<CollisionComponent_t>(entidadDy->getEntityID());
                                                EventManager::getInstancia().addEvent(Event{EventType::Mecanismo});
                                                colisionados++;
                                                for(auto& dyDoor : manager.getComponents<CollisionComponent_t>()){
                                                    auto* entidadDoor = manager.getEntityByID(dyDoor.getEntityID());
                                                    if(entidadDoor->getName().compare(0,7,"bloqueo") == 0){
                                                        auto splitted = splitPattern(entidadDoor->getName(),"_");
                                                        //std::cout << "Splitted 1 " << std::stoi(splitted[1]) << " colisionados " << colisionados;
                                                        if(std::stoi(splitted[1]) == colisionados){
                                                            colisionados = 0;
                                                            auto cmpPlayer = entityplayer->getComponent<PlayerComponent_t>();
                                                            auto aux = cmpPlayer->zona_player;
                                                            cmpPlayer->lista.insert(
                                                                std::make_pair<std::string,std::string>(entidadDoor->getName(),std::forward<std::string>(aux))
                                                            );
                                                            entidadDoor->SetEntityToDestroy();
                                                            return;
                                                        }
                                                }
                                            }
                                        }
                                        oumama = false;
                                        break;
                                    }
                                    else
                                        oumama = true;
                                }
                            }
                        }
                        moverCaja(cajitaphy,direccmp.dirPrevia,oumama);
                    }
                }
            }
        }
    }
}

void CollisionSystem_t::moverCaja(PhysicsComponent_t* cajitaphy, int direc, bool control){
    //std::cout<<"valor de la previa: "<<direc<<"\n";
    if(control){
        //std::cout<<"entro al movercaja\n";
        EventManager::getInstancia().addEvent(Event{EventType::empujar_Animation});
        if(direc == 1 || direc == 5 || direc == 7)
            cajitaphy->x += 0.45;
        else if(direc == 2 || direc == 6 || direc == 8)
            cajitaphy->x -= 0.45;

        //ahora eje Z
        if(direc == 3 || direc == 5 || direc == 6)
            cajitaphy->z += 0.45;
        else if(direc == 4 || direc == 7 || direc == 8){
            //std::cout<<"vamos pabajo nn\n";
            cajitaphy->z -= 0.45;
        }
    }
}


void CollisionSystem_t::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Collision_Sword,std::bind(&CollisionSystem_t::SwordAttack,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Collision_Shield,std::bind(&CollisionSystem_t::ShieldDefense,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_Space,std::bind(&CollisionSystem_t::collisionCaja,this,std::placeholders::_1)));

}
