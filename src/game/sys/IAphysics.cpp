#include "IAphysics.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/IAComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../../EventManager/EventManager.hpp"
#include <iostream>

double PI = 3.14159265359;

void IAPhySystem_t::addManager(EntityManager_t& man){
    //manager = &man;
}

void IAPhySystem_t::meterRuta(IAComponent_t* iacmp ) const{
    switch(iacmp->erizotype){
        case 1:
            iacmp->patrol.push_back(std::make_pair(-41, 159));
            iacmp->patrol.push_back(std::make_pair(12.5, 159));
            iacmp->patrol.push_back(std::make_pair(-12.5, 191.5));
            iacmp->patrol.push_back(std::make_pair(-41, 191.5));
        break;

        case 2:
            iacmp->patrol.push_back(std::make_pair(11.4, 206.5));
            iacmp->patrol.push_back(std::make_pair(-55.5, 206.5));
            iacmp->patrol.push_back(std::make_pair(-55.5, 273.5));
            iacmp->patrol.push_back(std::make_pair(11.4, 273.5));
        break;

        case 3:
            iacmp->patrol.push_back(std::make_pair(-70.6, 212));
            iacmp->patrol.push_back(std::make_pair(-70.6, 260.5));
            iacmp->patrol.push_back(std::make_pair(-92.5, 260.5));
            iacmp->patrol.push_back(std::make_pair(-92.5, 212));
        break;

        case 4:
            iacmp->patrol.push_back(std::make_pair(-41.3, 319.5));
            iacmp->patrol.push_back(std::make_pair(29, 319.5));
            iacmp->patrol.push_back(std::make_pair(29, 282));
            iacmp->patrol.push_back(std::make_pair(-41.3, 282));
        break;

        case 5:
            iacmp->patrol.push_back(std::make_pair(-205.0, 260.0));
            iacmp->patrol.push_back(std::make_pair(-205.0, 216.0));
        break;

        case 6:
            iacmp->patrol.push_back(std::make_pair(-239.0, 216.0));
            iacmp->patrol.push_back(std::make_pair(-239.0, 260.0));
        break;

        case 7:
            iacmp->patrol.push_back(std::make_pair(-247.0, 561.0));
            iacmp->patrol.push_back(std::make_pair(-247.0, 520.0));
            iacmp->patrol.push_back(std::make_pair(-220.0, 520.0));
            iacmp->patrol.push_back(std::make_pair(-220.0, 561.0));
        break;

        case 8:
            iacmp->patrol.push_back(std::make_pair(-284.0, 561.0));
            iacmp->patrol.push_back(std::make_pair(-314.0, 561.0));
            iacmp->patrol.push_back(std::make_pair(-314.0, 520.0));
            iacmp->patrol.push_back(std::make_pair(-284.0, 520.0));
        break;

        case 9:
            iacmp->patrol.push_back(std::make_pair(451.0, 415.0));
            iacmp->patrol.push_back(std::make_pair(485.0, 415.0));
        break;

        case 10:
            iacmp->patrol.push_back(std::make_pair(485.0, 444.0));
            iacmp->patrol.push_back(std::make_pair(451.0, 444.0));
        break;

        case 11:
            iacmp->patrol.push_back(std::make_pair(485.0, 384.0));
            iacmp->patrol.push_back(std::make_pair(451.0, 384.0));
        break;

        case 12:
            iacmp->patrol.push_back(std::make_pair(494.0, 342.0));
            iacmp->patrol.push_back(std::make_pair(442.0, 342.0));
        break;

        case 13:
            iacmp->patrol.push_back(std::make_pair(442.0, 301.0));
            iacmp->patrol.push_back(std::make_pair(494.0, 301.0));
        break;
    }
}

void IAPhySystem_t::update() const{
    //recorro el array de componentes de IA, y dependiendo del tipo que sean, llamo a un metodo u otro, pasandole la entidad correspondiente
    for(auto& ia : manager.getComponents<IAComponent_t>()){
        auto* e = manager.getEntityByID(ia.getEntityID());
        if(e && e->getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->getComponent<PhysicsComponent_t>();
            //cambiar esto para que compruebe que las entidades tienen physics component
            switch(ia.type){
                //el type es un enum, asi que se puede hacer un switch con valores numericos
                case 0:
                    if(ia.patrol.size() == 0)
                        meterRuta(&ia);
                        Arrive(phycmp, &ia);
                        HearingSense(phycmp);
                        
                break;
                case 1:
                    seta(phycmp, &ia);
                break;
                case 2:
                    Seek(phycmp, &ia);
                break;
            }
            if(ia.type != 1)
                updateSteering(e);
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
    //if(angle < 0)
    //    angle += 2*PI;
    return angle;
}

float IAPhySystem_t::calculateOrientation(float tarAngle, float actualOri) const{
    //tarAngle es el angulo objetivo, actualOri es el angulo u orientacion actual
    auto vang = tarAngle - actualOri;
    if(vang > PI)
        vang -= 2*PI;
    else if(vang < -PI)
        vang += 2*PI;

    return vang;
}

float IAPhySystem_t::calculateTargetAngleEnemy(float angulo) const{
    float angletransformed = angulo * 180 / PI;//convierto de radianes a grados
    //std::cout<<"angulo transformado: "<<angletransformed<<"\n";
    //phycmp->ry = angletransformed;
    float aux = std::fabs(angletransformed);
    float aux1 = aux - 90;
    float aux2 = 90 - aux1;
    if(angletransformed < 0)
        aux2 = -aux2;
    return aux2;
}

float IAPhySystem_t::truncate(float velocity, float steering, float maxspeed) const {
    //este metodo no se usa de momento, igual hay que borrarlo si sigue sin uso
    if(std::abs(velocity + steering) > maxspeed)
        return maxspeed;
    else
        return velocity + steering;
}
//METODOS PARA LOS STEERING BEHAVIOURS
void IAPhySystem_t::updateSteering(Entity_t* e) const{
    auto* iacmp  = e->template getComponent<IAComponent_t>();
    //if(iacmp->isActive){
        auto* phycmp = e->template getComponent<PhysicsComponent_t>();
        //std::cout<<phycmp->x << " "<<phycmp->z<<"\n";
        //actualizo la orientacion y compruebo que tenga unos valores adecuados
        //si en algun momento la vangular o algo de angulos se desfasa, comentar las 5 lineas de abajo
        //basicamente quitar hasta phycmp->vx...
        phycmp->orientation += dt*phycmp->vangular;
        if(phycmp->orientation > 2*PI)
            phycmp->orientation -= 2*PI;
        else if(phycmp->orientation < 0)
            phycmp->orientation += 2*PI;

        //phycmp->ry += dt * phycmp->acangular;
        //phycmp->ry = std::clamp(phycmp->ry, -phycmp->targetAngle, phycmp->targetAngle);
        /*phycmp->ry += dt*phycmp->vangular;
        if(phycmp->ry > phycmp->targetAngle)
            phycmp->ry = phycmp->targetAngle;*/
        //phycmp->ry = phycmp->ry * 180 / PI;
        //std::cout<<"el angulo es: "<<phycmp->ry<<"\n";
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
    //}
}

void IAPhySystem_t::Seek(PhysicsComponent_t* phycmp, IAComponent_t* iacmp) const{
    for(auto& inpcmp : manager.getComponents<InputComponent_t>()){
        auto* e = manager.getEntityByID(inpcmp.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* playerphy = e->template getComponent<PhysicsComponent_t>();
            phycmp->vangular = phycmp->aclineal = 0;
            //if(try1 == 1)
                //std::cout<<"playerx en seek: "<<playerphy->x<<" playerz en seek: "<<playerphy->z<<"\n";
            auto distance = calculateDistance(phycmp->x, phycmp->z, playerphy->x, playerphy->z);//distancia entre el enemigo y el player
            auto backDistance = calculateDistance(phycmp->x, phycmp->z, phycmp->initx, phycmp->initz);//distancia entre la posicion actual del enemigo y la original
            //std::cout<<"Distancia de vuelta: "<<backDistance<<"\n";
            if(distance > iacmp->radius && distance < 50.0){
                iacmp->isActive = true;
                auto torien = calculateAngle(phycmp->x, phycmp->z, playerphy->x, playerphy->z);
                
                phycmp->ry = calculateTargetAngleEnemy(torien);
                if(torien < 0)
                    torien += 2*PI;
            

                auto angular_dist = calculateOrientation(torien, phycmp->orientation);
                //std::cout<<"distancia angular antes de los if: "<<angular_dist<<"\n";
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
                iacmp->isActive = false;
                phycmp->vangular = phycmp->vlineal = 0;
                phycmp->acangular = phycmp->aclineal = 0;
                phycmp->orientation = 0;
        //if(backDistance >= 30)
        //    Arrive(phycmp, iacmp, phycmp->initx, phycmp->initz);
            }
        }
    }
}

void IAPhySystem_t::Arrive(PhysicsComponent_t* phycmp, IAComponent_t* iacmp) const {
    if(phycmp && iacmp && iacmp->patrol.size() > 0){
        auto tarX = iacmp->patrol[iacmp->rutaActual].first;
        auto tarZ = iacmp->patrol[iacmp->rutaActual].second;
        auto distance = calculateDistance(phycmp->x, phycmp->z, tarX, tarZ);
        auto torien = calculateAngle(phycmp->x, phycmp->z, tarX, tarZ);
        //std::cout<<"angulo en radianes: "<<torien<<"\n";
        if(!iacmp->InitTarAngle){
            phycmp->targetAngle = calculateTargetAngleEnemy(torien);
            iacmp->InitTarAngle = true;
        }
        //phycmp->ry != phycmp->targetAngle
        /*if(std::fabs(phycmp->ry - phycmp->targetAngle) <= iacmp->radius){

        }*/
        //es posible que nunca llegue exacto, por tanto un boolean u otro metodo de control para que cuando se aproxime bastante, se salga
        if(std::fabs(phycmp->ry - phycmp->targetAngle) > 0.3){
            iacmp->isActive = false;    //iacmp->InitTarAngle = false;
            phycmp->vlineal = phycmp->orientation = 0;
            auto angulardistance = phycmp->targetAngle - phycmp->ry;
            //std::cout<<"la distancia angular es: "<<angulardistance<<"\n";
            phycmp->acangular = std::clamp(angulardistance/iacmp->time, -phycmp->MAXAcng, phycmp->MAXAcng);
            //std::cout<<"la aceleracion angular es: "<<phycmp->acangular<<"\n";
            phycmp->ry += dt * phycmp->acangular;
            //std::cout<<"el angulo tras sumar es: "<<phycmp->ry<<"\n";
            if(phycmp->targetAngle < 0)
                phycmp->ry = std::clamp(phycmp->ry, phycmp->targetAngle, -phycmp->targetAngle);
            else
                phycmp->ry = std::clamp(phycmp->ry, -phycmp->targetAngle, phycmp->targetAngle);
            //std::cout<<"el angulo tras el clamp es: "<<phycmp->ry<<"\n";
        }
        else{
            if(distance < iacmp->radius){
                iacmp->isActive = false;    iacmp->InitTarAngle = false;
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
            //ahora pasamos a calcular el angulo
            //si en algun momento se desfasa los angulos, descomentar las 3 lineas de abajo
            //y comentar desde auto torien hasta el final
            //****estas 3 lineas de aqui estan bien
            //phycmp->orientation = std::atan(pendiente);
            //if(vtx < phycmp->x)
            //    phycmp->orientation += PI;
            //calcular el angulo me sirve para determinar mi orientacion, vangular y el angulo objetivo al que debe llegar el enemigo
            //phycmp->ry = 90 - angletransformed;
            if(torien < 0)
                torien += 2*PI;
            auto vang = calculateOrientation(torien, phycmp->orientation);
            phycmp->vangular = std::clamp(vang/iacmp->time, -phycmp->MAXVang, phycmp->MAXVang);

            if(distance > iacmp->slowdistance)
                phycmp->vlineal = phycmp->MAXVlin;
                
            else{
                //sabiendo la distancia y el tiempo de llegada, puedo calcular la velocidad porque v= e/t
                auto velocity = std::clamp(distance/iacmp->time, -phycmp->MAXVlin, phycmp->MAXVlin);
                //sabiendo la velocidad a la que debo llegar, debo tener en cuenta la aceleracion
                //si resto la velocidad tvelocity(la objetivo), menos la velocidad que ya llevo, obtengo la diferencia entre ellas y esa va a ser mi aceleracion
                phycmp->aclineal = std::clamp((velocity - phycmp->vlineal)/ iacmp->time, -phycmp->MAXAcl, phycmp->MAXAcl); 
            }
        }
    }
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
        if(!iacmp->cadenciaCheck){
            iacmp->cadencia = std::chrono::steady_clock::now();
            iacmp->cadenciaCheck = true;
        }
        auto end = std::chrono::steady_clock::now();
        double elapsed = double(std::chrono::duration_cast<std::chrono::milliseconds> (end - iacmp->cadencia).count());
        if(elapsed >= 300){//si el tiempo es mayor o igual a 300 milisegundos = 0.3
            EventInfo info;
            //aqui si estaba a la derecha no se le suma nada al angulo, si esta a la izquierda se le suma 180 grados. Con atan2 esto no hace falta, lo dejo escrito por
            //si acaso
            auto angle = calculateAngle(phycmp->x,phycmp->z,playerphy->x,playerphy->z);
            auto angletransformed = angle * 180 / PI;//convierto de radianes a grados
            //std::cout<<"angulo transformado: "<<angletransformed<<"\n";
            auto aux = std::fabs(angletransformed);
            auto aux1 = aux - 90;
            auto aux2 = 90 - aux1;
            if(angletransformed < 0)
                aux2 = -aux2;
            phycmp->ry = calculateTargetAngleEnemy(angle);            
            disparos++;
            info.posX = phycmp->x; info.posZ = phycmp->z; info.angle = angle; info.shottype = 1;
            EventManager::getInstancia().addEvent(Event{EventType::Create_Shot, info});
            EventManager::getInstancia().addEvent(Event{EventType::Enemy_Seta});//evento sonoro
            iacmp->cadenciaCheck = false;
        }
    }
    //cuando llega a 3 disparos, activo el reloj del reload
    if(disparos >= 3 && !iacmp->reloadCheck){
        iacmp->reload = std::chrono::steady_clock::now();
        iacmp->reloadCheck = true;
    }
    //ahora uso un reloj propio del metodo y voy restando los intervalos hasta tener 1s o mas
    if(iacmp->reloadCheck){
        auto end = std::chrono::steady_clock::now();
        int elapsed = int(std::chrono::duration_cast<std::chrono::seconds> (end - iacmp->reload).count());
        if(elapsed >= 1){
            disparos = 0;
            iacmp->reloadCheck = false;
        }
    }
}

void IAPhySystem_t::HearingSense(PhysicsComponent_t* phycmp) const{
    //sacamos al player ya que es el que nos influye
    auto& inpcmp = manager.getComponents<InputComponent_t>();
    auto* player = manager.getEntityByID(inpcmp[0].getEntityID());
    if(player && player->template getComponent<PhysicsComponent_t>()){
        auto* playerphy = player->template getComponent<PhysicsComponent_t>();
        //una vez que tenemos el player, sacamos la distancia entre ambos
        auto distance = calculateDistance(phycmp->x,phycmp->z,playerphy->x,playerphy->z);
        if(distance <= 100.0){//si entra aqui, pasamos a ir aumentando la velocidad del erizo progresivamente
            //tenemos que calcular la intensidad del sonido que le llega al erizo.
            //la fuerza de la senyal sera mayor si el player esta corriendo, mientras que si esta andando normal, sera menor
            int signalStrength {0};
            if(playerphy->vx >= 0.75)
                signalStrength = 50;//si entra aqui es que esta corriendo, por lo que la intensidad sube
            else
                signalStrength = 30;
            
            auto intensidad = signalStrength * std::pow(0.8, distance);
            //vamos a aumentar la velocidad lineal maxima del erizo en base al resultado de la intensidad
            //pero teniendo cierto control, porque pueden dar valores increiblemente pequenyos o increiblemente grandes
            if(intensidad <= 10.0)
                intensidad = 10.0;
            if(intensidad >= 30)
                intensidad = 30.0;
            //una vez tratada la intensidad para no pasarnos, modificamos la vlineal
            phycmp->MAXVlin = intensidad;
        }
    }
}