#include <game/sys/IAphysics.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/IAComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <ecs/man/entityManager.hpp>
#include <EventManager/EventManager.hpp>
#include <iostream>
#include <cmath>

void IAPhySystem_t::addManager(EntityManager_t& man){
    //manager = &man;
}

void IAPhySystem_t::meterRuta(Entity_t* e ) const{
    auto* iacmp = e->template getComponent<IAComponent_t>();
    iacmp->patrol.push_back(std::make_pair(-75, 201.4));
    iacmp->patrol.push_back(std::make_pair(-75, 287.2));
    iacmp->patrol.push_back(std::make_pair(20.117, 287.2));
    iacmp->patrol.push_back(std::make_pair(20.117, 201.388));

    prueba = true;
} 

void IAPhySystem_t::update() const{
    //recorro el array de componentes de IA, y dependiendo del tipo que sean, llamo a un metodo u otro, pasandole la entidad correspondiente
    for(auto& ia : manager.getComponents<IAComponent_t>()){
        auto* e = manager.getEntityByID(ia.getEntityID());
        auto* phycmp = e->getComponent<PhysicsComponent_t>();
        if(e){//cambiar esto para que compruebe que las entidades tienen physics component
            switch(ia.type){
                //el type es un enum, asi que se puede hacer un switch con valores numericos
                case 0:
                    if(!prueba)
                        meterRuta(e);
                        //SteeringCine(e);
                    updateSteering(e);
                    //Arrive(e);
                    Arrive(phycmp, &ia);
                break;

                case 1:
                    //seta(e);
                    seta(phycmp, &ia);
                break;

                case 2:
                    //Seek(e);
                    updateSteering(e);
                    Seek(phycmp, &ia);
                    //spider(e);
                    //spider(phycmp, &ia);
                break;
            }
        }
    }  
}

//METODOS AUXILIARES PARA CALCULOS DE STEERING
float IAPhySystem_t::calculateDistance(float myX, float myZ, float tarX, float tarZ) const{
    auto distX = myX - tarX;    auto distZ = myZ - tarZ;
    return std::sqrt(distX * distX + distZ * distZ);
}

float IAPhySystem_t::calculatePendiente(float myX, float myZ, float tarX, float tarZ) const{
    return (myZ - tarZ) / (myX - tarX);
}

float IAPhySystem_t::calculateAngle(float myX, float myZ, float tarX, float tarZ) const{
    //myX,myZ posicion de la entidad actual, tarX,tarZ posicion del punto de referencia
    auto angle = std::atan2((tarZ - myZ), (tarX - myX));
    if(angle < 0)
        angle += 2*M_PI;
    return angle;
}

float IAPhySystem_t::calculateOrientation(float tarAngle, float actualOri) const{
    //tarAngle es el angulo objetivo, actualOri es el angulo u orientacion actual
    auto vang = tarAngle - actualOri;
    if(vang > M_PI)
        vang -= 2*M_PI;
    else if(vang < -M_PI)
        vang += 2*M_PI;

    return vang;
}

float IAPhySystem_t::truncate(float velocity, float steering, float maxspeed) const {
    //este metodo no se usa de momento, igual hay que borrarlo si sigue sin uso
    if(std::abs(velocity + steering) > maxspeed)
        return maxspeed;
    else
        return velocity + steering;
}

float IAPhySystem_t::calculateAverageVelocity() const{
    std::vector<float> velocities;
    velocities.reserve(5);//el tamanyo de la reserva sera igual al numero de entidades con cmp flocking
    //for(auto& )
}

//METODOS PARA LOS STEERING BEHAVIOURS
void IAPhySystem_t::updateSteering(Entity_t* e) const{
    auto* iacmp  = e->template getComponent<IAComponent_t>();
    if(iacmp->isActive){
        auto* phycmp = e->template getComponent<PhysicsComponent_t>();
        //std::cout<<phycmp->x << " "<<phycmp->z<<"\n";
        //actualizo la orientacion y compruebo que tenga unos valores adecuados
        //si en algun momento la vangular o algo de angulos se desfasa, comentar las 5 lineas de abajo
        //basicamente quitar hasta phycmp->vx...
        phycmp->orientation += dt*phycmp->vangular;
        if(phycmp->orientation > 2*M_PI)
            phycmp->orientation -= 2*M_PI;
        else if(phycmp->orientation < 0)
            phycmp->orientation += 2*M_PI;

        //actualizo la velocidad en cada eje de acuerdo a la vlineal
        //la vlinea empieza valiendo 0 y se actualiza con la aceleracion que se calcula en el metodo erizo
        phycmp->vx = phycmp->vlineal * std::cos(phycmp->orientation);
        phycmp->vz = phycmp->vlineal * std::sin(phycmp->orientation);
        //std::cout<<"vx: "<<phycmp->vx<<"\n";
        //std::cout<<"vz: "<<phycmp->vz<<"\n";
        //actualizo la posicion
        phycmp->x += dt * phycmp->vx;
        phycmp->z += dt * phycmp->vz;
        //v = at
        //la velocidad se actualiza teniendo en cuenta los valores de la aceleracion
        phycmp->vlineal += dt * phycmp->aclineal;
        phycmp->vlineal = std::clamp(phycmp->vlineal, -phycmp->MAXVlin, phycmp->MAXVlin);
        //std::cout<<"vlineal: "<<phycmp->vlineal<<"\n";
        //comprobar que estas 2 lineas de abajo no sirven para nada en vd
        //phycmp->vangular += dt * phycmp->acangular;
        //phycmp->vangular = std::clamp(phycmp->acangular, -phycmp->MAXAcng, phycmp->MAXAcng);
        //aplicamos rozamiento
        auto roza = dt * std::fabs(phycmp->vlineal) * phycmp->Rozamiento;
        if(phycmp->vlineal > 0)
            phycmp->vlineal -= roza;
        else
            phycmp->vlineal += roza;
    }
}

void IAPhySystem_t::Seek(PhysicsComponent_t* phycmp, IAComponent_t* iacmp) const{
    auto& inpcmp = manager.getComponents<InputComponent_t>()[0];
    auto* player = manager.getEntityByID(inpcmp.getEntityID());
    auto* playerphy = player->template getComponent<PhysicsComponent_t>();
    phycmp->vangular = phycmp->aclineal = 0;
    auto distance = calculateDistance(phycmp->x, phycmp->z, playerphy->x, playerphy->z);//distancia entre el enemigo y el player
    auto backDistance = calculateDistance(phycmp->x, phycmp->z, phycmp->initx, phycmp->initz);//distancia entre la posicion actual del enemigo y la original
    //en lugar de hacer el if este con < 30 u otro valor, deberia tener un rango de activacion predefinido
    //if(distance > iacmp->radius && distance < 30 && backDistance < 30)
    //    iacmp->isActive = true;
    //else
    //    iacmp->isActive = false;

    if(distance > iacmp->radius && distance < 30 && backDistance < 30){
        iacmp->isActive = true;
        //auto pendiente = calculatePendiente(phycmp->x, phycmp->z, playerphy->x, playerphy->z);
        //auto torien = calculateAngle(phycmp->x,phycmp->z,playerphy->x,playerphy->z,);
        auto torien = calculateAngle(phycmp->x, phycmp->z, playerphy->x, playerphy->z);
        //std::cout<<"orientacion: "<<torien<<"\n";
        //if(torien < 0)
        //    torien += 2*M_PI;
        //if(playerphy->x < phycmp->x)
        //    torien += M_PI;
        
        auto angular_dist = calculateOrientation(torien, phycmp->orientation);
        //std::cout<<"distancia angular antes de los if: "<<angular_dist<<"\n";
        /*if(angular_dist > M_PI)
            angular_dist -= 2*M_PI;
        else if(angular_dist < -M_PI)
            angular_dist += 2*M_PI;*/
        //std::cout<<"distancia angular: "<<angular_dist<<"\n";
        //std::cout<<"tiempo de IA: "<<iacmp->time<<"\n";
        auto angular_vel = angular_dist/iacmp->time;
        //std::cout<<"velocidad angular: "<<angular_vel<<"\n";
        phycmp->vangular = std::clamp(angular_vel, -phycmp->MAXVang, phycmp->MAXVang);
        angular_vel = std::fabs(angular_vel);
        auto aceler = phycmp->MAXVlin/(1+ angular_vel);
        phycmp->aclineal = std::clamp(aceler/iacmp->time, -phycmp->MAXAcl, phycmp->MAXAcl);
    }
    else{//igual es interesante que la aranya inteligente te persiga hasta que la mates
        //si no esta activo lo ponemos todo a 0 para que cuando se reactive no tenga unos valores incorrectos
        //iacmp->isActive = false;
        //phycmp->vangular = phycmp->vlineal = 0;
        //phycmp->acangular = phycmp->aclineal = 0;
        //phycmp->orientation = 0;
        //if(backDistance >= 30)
        //    Arrive(phycmp, iacmp, phycmp->initx, phycmp->initz);
    }
}

void IAPhySystem_t::Arrive(PhysicsComponent_t* phycmp, IAComponent_t* iacmp) const {
    auto tarX = iacmp->patrol[iacmp->rutaActual].first;
    auto tarZ = iacmp->patrol[iacmp->rutaActual].second;
    auto distance = calculateDistance(phycmp->x, phycmp->z, tarX, tarZ);
    if(distance < iacmp->radius){
        iacmp->isActive = false;
        phycmp->vlineal = phycmp->orientation = 0;
        //si entra significa que ha llegado
        if(iacmp->rutaActual == iacmp->patrol.size() - 1)
            iacmp->rutaActual = 0;
        else
            iacmp->rutaActual++;
        return;
    }
    else
        iacmp->isActive = true;

    if(distance > iacmp->slowdistance)
        phycmp->vlineal = phycmp->MAXVlin;
          
    else{
        //sabiendo la distancia y el tiempo de llegada, puedo calcular la velocidad porque v= e/t
        
        auto velocity = std::clamp(distance/iacmp->time, -phycmp->MAXVlin, phycmp->MAXVlin);
        //sabiendo la velocidad a la que debo llegar, debo tener en cuenta la aceleracion
        //si resto la velocidad tvelocity(la objetivo), menos la velocidad que ya llevo, obtengo la diferencia entre ellas y esa va a ser mi aceleracion
        phycmp->aclineal = std::clamp((velocity - phycmp->vlineal)/ iacmp->time, -phycmp->MAXAcl, phycmp->MAXAcl); 
    }
    
    //ahora pasamos a calcular el angulo
    auto pendiente = (tarZ - phycmp->z) / (tarX - phycmp->x);
    //si en algun momento se desfasa los angulos, descomentar las 3 lineas de abajo
    //y comentar desde auto torien hasta el final
    //****estas 3 lineas de aqui estan bien
    //phycmp->orientation = std::atan(pendiente);
    //if(vtx < phycmp->x)
    //    phycmp->orientation += M_PI;
    //auto penZ = vtz - phycmp->z;    auto penX = vtx - phycmp->x;
    auto torien = calculateAngle(phycmp->x, phycmp->z, tarX, tarZ);
    //if(torien < 0)
    //    torien += 2*M_PI;
    //if(vtx < phycmp->x)
    //   torien += M_PI;
    auto vang = calculateOrientation(torien, phycmp->orientation);
    /*if(vang > M_PI)
        vang -= 2*M_PI;
    else if(vang < -M_PI)
        vang += 2*M_PI;*/
    phycmp->vangular = std::clamp(vang/iacmp->time, -phycmp->MAXVang, phycmp->MAXVang);
}

//METODOS ENTIDADES SIN IA
void IAPhySystem_t::spider(PhysicsComponent_t* phycmp, IAComponent_t* iacmp) const{
    //voy a sacar primero la posicion del player
    /*puedo usar el inputcomponent porque en principio solo lo va a tener el player, si esto cambiara
    se puede hacer un componente que sea player, y asi no hay ninguna duda*/
    auto& inpcmp = manager.getComponents<InputComponent_t>()[0];
    auto* player = manager.getEntityByID(inpcmp.getEntityID());
    auto* playerphy = player->template getComponent<PhysicsComponent_t>();
    //voy a calcular la distancia en los ejes X-Z entre el jugador y el enemigo
    //hay que tener en cuenta los 4 casos posibles: izquierda arriba, izquierda abajo, derecha arriba y derecha abajo
    //miro primero en el eje X
    bool& repos = iacmp->reposition;
    float rangex = std::abs(phycmp->x - playerphy->x);
    float rangez = std::abs(phycmp->z - playerphy->z);
    if(rangex <= 15 && rangez <= 15 && !repos){
        if(playerphy->x < phycmp->x)
            phycmp->x -= 0.2;
        else if(playerphy->x > phycmp->x)//si entra aqui significa que el player esta a la derecha del enemigo
            phycmp->x += 0.2;
        if(playerphy->z < phycmp->z)//si entra aqui significa que el player esta abajo del enemigo
            phycmp->z -= 0.2;
        else if(playerphy->z > phycmp->z)
            phycmp->z += 0.2; 
    }
        //ahora tengo que tratar de reposicionarlo
    float disx = std::abs(phycmp->x - phycmp->initx);
    float disz = std::abs(phycmp->z - phycmp->initz);
    if(disx >=15 || disz >= 15)
        repos = true;
    
    if(repos){
        if(phycmp->x < phycmp->initx)
            phycmp->x += 0.2;
        else if(phycmp->x > phycmp->initx)
            phycmp->x -= 0.2;
        if(phycmp->z < phycmp->initz)
            phycmp->z += 0.2;
        else if(phycmp->z > phycmp->initz)
            phycmp->z -= 0.2; 
        
        if(phycmp->x == phycmp->initx && phycmp->z == phycmp->initz)
            repos = false;
    }
}

void IAPhySystem_t::seta(PhysicsComponent_t* phycmp, IAComponent_t* iacmp) const{
    //std::cout<<"entro a la seta\n";
    int& disparos = iacmp->disparos;
    //saco ahora la posicion del player
    auto& inpcmp = manager.getComponents<InputComponent_t>()[0];
    auto* player = manager.getEntityByID(inpcmp.getEntityID());
    auto* playerphy = player->template getComponent<PhysicsComponent_t>();
    //calculo la distancia que los separa en cada eje
    float rangex = std::abs(phycmp->x - playerphy->x);
    float rangez = std::abs(phycmp->z - playerphy->z);
    //si entra en rango de disparo, hago cosas
    if(rangex <= 35 && rangez <= 35 && disparos < 3){
        if(!cadenciaCheck){
            cadencia = std::chrono::steady_clock::now();
            cadenciaCheck = true;
        }
        auto end = std::chrono::steady_clock::now();
        double elapsed = double(std::chrono::duration_cast<std::chrono::milliseconds> (end-cadencia).count());
        if(elapsed >= 300){//si el tiempo es mayor o igual a 300 milisegundos = 0.3
            EventInfo info;
            //bool right = false;
            //if(x < x2)
            //right = true;
            //aqui si estaba a la derecha no se le suma nada al angulo, si esta a la izquierda se le suma 180 grados. Con atan2 esto no hace falta, lo dejo escrito por
            //si acaso
            auto angle = calculateAngle(phycmp->x,phycmp->z,playerphy->x,playerphy->z);
            phycmp->ry = angle * 180 / M_PI;
            //if(phycmp->x > playerphy->x)
            //    phycmp->ry += 180;
            disparos++;
            info.posX = phycmp->x; info.posZ = phycmp->z; info.angle = angle;
            EventManager::getInstancia().addEvent(Event{EventType::Create_Shot, info});
            cadenciaCheck = false;
        }
    }
    //cuando llega a 3 disparos, activo el reloj del reload
    if(disparos >= 3 && !reloadCheck){
        reload = std::chrono::steady_clock::now();
        reloadCheck = true;
    }
    //ahora uso un reloj propio del metodo y voy restando los intervalos hasta tener 1s o mas
    if(reloadCheck){
        auto end = std::chrono::steady_clock::now();
        int elapsed = int(std::chrono::duration_cast<std::chrono::seconds> (end-reload).count());
        if(elapsed >= 1){
            disparos = 0;
            reloadCheck = false;
        }
    }
}

    
