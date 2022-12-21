#include "RavenGraphics.hpp"
#include "../EventManager/EventManager.hpp"


// GLEW library
#define GLEW_STATIC
#include <glew.h>

// GLFW library
#include <glfw3.h>
#define GLFW_INCLUDE_NONE

#include "../game/cmp/RenderComponent.hpp"
#include "../game/cmp/PhysicsComponent.hpp"
#include "../game/cmp/InputComponent.hpp"
#include "../game/cmp/IAComponent.hpp"
#include "../game/cmp/DirecComponent.hpp"
#include "../game/cmp/CameraComponent.hpp"
#include "../game/cmp/ItemComponent.hpp"
#include "../game/cmp/ShootComponent.hpp"
#include "../facade/RavenSound.hpp"

#include <iostream>


RavenGraphics::RavenGraphics(){
    //rvMotor = std::make_unique<MotorRaven>(1920,1080,"Soul Mirror",true);
    device = new MotorRaven(1920,1080,"Soul Mirror",false);
    //ourShader = device->crearShader("src/Shaders/");
    then = device->getTime();
    now = device->getTime();
    device->beginScene();
    // build and compile shaders
    // -------------------------
    //ourShader = device->crearShader("src/Shaders/");
    device->addShader();

    //billboard
    //const char* fileBillBoard = "media/mrPinguin.png";
    //device->addBillboard(nullptr, 40, fileBillBoard, false, 720.0, 311.0);

    //SKYBOX
    device->addSkybox("media/skybox/right.jpg",
                        "media/skybox/left.jpg",
                        "media/skybox/top.jpg",
                        "media/skybox/bottom.jpg",
                        "media/skybox/front.jpg",
                        "media/skybox/back.jpg");
    //PONER LAS LUCES COMO COMPONENTE Y CREARLAS EN EL .MAX Y EXPORTALAS AL JSON
    device->crearLuzPuntual(120, nullptr, glm::vec3(0.f, 1000.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
    addEventListeners();
}


// Función para rotar la cámara pasada
// -----------------------------------
void RavenGraphics::rotateCamera(MotorRaven *dev, Nodo *camera, float fdt, float speed) {
    //std::cout << "Hola" << std::endl;

    float movementX = 0.f;
    float movementY = 0.f;

    if (dev->processInput(GLFW_KEY_LEFT))
    {
        //movementY = -(speed * fdt);
        movementY = -(speed * fdt) * 2;
        camera->rotar(glm::vec3(0.f, movementY, 0.f));
    }
    else if (dev->processInput(GLFW_KEY_RIGHT))
    {
        //movementZ = (speed * fdt);
        movementY = (speed * fdt) * 2;
        camera->rotar(glm::vec3(0.f, movementY, 0.f));
    }

    if (dev->processInput(GLFW_KEY_DOWN))
    {
        movementX = -(speed * fdt);
        camera->rotar(glm::vec3(movementX, 0.f, 0.f));
    }
    else if (dev->processInput(GLFW_KEY_UP))
    {
        movementX = (speed * fdt);
        camera->rotar(glm::vec3(movementX, 0.f, 0.f));
    }
}

void RavenGraphics::createWindow(){
    //Sobrecargar los parametros de entrada de la funcion
    device->createWindow(1920,1080,"Soul Mirror",true);
}

void RavenGraphics::beginScene() {
    //device->beginScene();
}

void RavenGraphics::endScene() {
    //device->endScene();
}

void RavenGraphics::drawInit(){


}

void RavenGraphics::drawCredits(){

}

bool moveModel(MotorRaven *dev, Nodo* object, float fdt, float speed) {
    bool move = false;
    
    float movementX = 0.f;
    float movementZ = 0.f;

    if (dev->processInput(GLFW_KEY_W))
    {
        //movementZ = -(speed * fdt);
        movementZ = -(speed * fdt) * 2;
        object->trasladar(glm::vec3(0.f, 0.f, movementZ));
        move = true;
    }
    else if (dev->processInput(GLFW_KEY_S))
    {
        //movementZ = (speed * fdt);
        movementZ = (speed * fdt) * 2;
        object->trasladar(glm::vec3(0.f, 0.f, movementZ));
        move = true;
    }

    if (dev->processInput(GLFW_KEY_A))
    {
        movementX = -(speed * fdt);
        object->trasladar(glm::vec3(movementX, 0.f, 0.f));
        move = true;
    }
    else if (dev->processInput(GLFW_KEY_D))
    {
        movementX = (speed * fdt);
        object->trasladar(glm::vec3(movementX, 0.f, 0.f));
        move = true;
    }
    
    return move;
}

void RavenGraphics::drawGame(){
// don't forget to enable shader before setting uniforms
        //ourShader->use();

        // Medición de tiempo
        // ------------------
        now = device->getTime();
        frameDeltaTime = (now - then) / 1000.f;
        then = now;

        // Actualización del viewport
        // --------------------------
        device->updateViewport();

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Mover modelo
        // ------------
        //bool move = moveModel(device, model, frameDeltaTime, 10000.f);
        
        // render the scene
        // ----------------
        //rotateCamera(ourCamera,frameDeltaTime, 10000.f);
        rotateCamera(device, ourCamera, frameDeltaTime, 10000.f);

        auto posPlayer = device->getSceneManager()->getNodoFromID(1)->getTraslacion();
        
        ourCamera->setTraslacion(posPlayer);

        //device->dibujarEscena(ourShader->ID);
        device->dibujarEscena();

        
        if (device->processInput(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(device->getWindow(), true);
        }

        // Medición de fps (frames per second)
        // ------------------
        device->updateFrames();
        fps = device->getFPS();

        // Si cambian los FPS los actualizamos
        if(lastFPS != fps)
        {
            // Display the frame count here any way you want.
            device->setTitle("SoulMirror FPS : " + std::to_string(fps) + ";");
            lastFPS = fps;
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(device->getWindow());
        glfwPollEvents();
}

void RavenGraphics::drawControls(){

}

void RavenGraphics::drawPause(){

}

//*************METODOS DE ACTUALIZACION
void RavenGraphics::cameraUpdate() {
    
}

void RavenGraphics::updateEntities() {
    glm::vec3 newPosition;
     for(auto& iacmp : manager->getComponents<IAComponent_t>()){
         //std::cout<<"ID de la IA: "<<iacmp.getEntityID()<<"\n";
        auto* e = manager->getEntityByID(iacmp.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->template getComponent<PhysicsComponent_t>();
            if(phycmp){
                newPosition.x = phycmp->x;
                newPosition.y = phycmp->y;
                newPosition.z = phycmp->z;
                
                if(device->getSceneManager()->getNodoFromID(e->getEntityID())){//hay que ver que el nodo existe, si no explota
                    //std::cout<<"La posicion del enemy es X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
                    device->getSceneManager()->getNodoFromID(e->getEntityID())->setTraslacion(newPosition);
                }
            }
            //delete phycmp;
        }
        //delete e;
    }

    int dirPrev = -1;
    auto& player = manager->getComponents<InputComponent_t>();
    auto* e = manager->getEntityByID(player[0].getEntityID());
    if(e && e->template getComponent<PhysicsComponent_t>()){
        auto* phycmp = e->template getComponent<PhysicsComponent_t>();
        if(phycmp){
            auto* ren = e->template getComponent<RenderComponent_t>();
            //auto posBulletCh = world->getCharacter()->getGhostObject()->getWorldTransform().getOrigin();
            newPosition.x = phycmp->x; 
            newPosition.y = ren->l/2;
            newPosition.z = phycmp->z; 
            auto dir = e->template getComponent<DirecComponent_t>();
            dirPrev = dir->dirPrevia;
            //std::cout << "Posicion del personaje X Y Z : " << newPosition.x << " " <<  newPosition.y << " " << newPosition.z << std::endl; 
            if(device->getSceneManager()->getNodoFromID(e->getEntityID())){
                device->getSceneManager()->getNodoFromID(e->getEntityID())->setTraslacion(newPosition);
            }
            //if(smgr->getSceneNodeFromId(e->getEntityID())){
            //    smgr->getSceneNodeFromId(e->getEntityID())->setPosition(newPosition);   
            //    //world->walkingCharacter(newPosition.X,newPosition.Y,newPosition.Z);
            //}//hay que ver que el nodo existe, si no explota{
            //std::cout<<"X: "<<newPosition.X<<" Z: "<<newPosition.Z<<"\n";
        }
        //delete phycmp;
    }
        //delete e;

    for(auto& bala : manager->getComponents<ShootComponent_t>()){
        auto* e = manager->getEntityByID(bala.getEntityID());
        if(e && e->template getComponent<PhysicsComponent_t>()){
            auto* phycmp = e->template getComponent<PhysicsComponent_t>();
            newPosition.x = (phycmp->x);
            newPosition.y = (phycmp->y);
            newPosition.z = (phycmp->z);
            std::cout << "Posicion de la bala X Y Z : " << newPosition.x << " " <<  newPosition.y << " " << newPosition.z << std::endl; 
            if(device->getSceneManager()->getNodoFromID(e->getEntityID()))//hay que ver que el nodo existe, si no explota
                device->getSceneManager()->getNodoFromID(e->getEntityID())->setTraslacion(newPosition);
        }
    }
}

//*************METODOS DE INPUT***************
void RavenGraphics::getInputInit(){
        EventInfo info;
        info.state_type = 4;
        EventManager::getInstancia().addEvent(Event{EventType::State_Change,info});
    
}

void RavenGraphics::getInputCredits(){

}

void RavenGraphics::getInputGame(){
        auto& inpcmp = manager->getComponents<InputComponent_t>();
        //con esto sacamos la entidad del jugador
        auto* e = manager->getEntityByID(inpcmp[0].getEntityID());
        EventInfo info;
        if(e){
            auto direc = e->getComponent<DirecComponent_t>();
            auto itemCmp = e->getComponent<ItemComponent_t>();
            //*************CAMBIOS DE ARMA**********
            if(device->processInput(GLFW_KEY_ENTER)){
                if(itemCmp->m_seleccionado != -1){
                    
                    auto* arma = manager->getEntityByID(itemCmp->m_seleccionado+2);
                    if(arma){
                        info.id = arma->getEntityID();
                        itemCmp->executeAction(info);
                        //int segundos = 0;
                        //clock_t tiempoDeInicio, tiempoAcual;    
                        //tiempoDeInicio = time(NULL); // Obtiene el tiempo a la hora de iniciar el cronometro - Variable de referencia
                        //while(1){
                        ///* Se inicia el cronometro */
                        //    tiempoAcual = time(NULL); // Obtiene el tiempo para ser comparado con la variable de refencia
                        //    segundos = (tiempoAcual-tiempoDeInicio); // Se obtiene la cantidad de segundos
//
                        //    if(segundos == 30){ //Comprueba que la cantidad de segundos sea menor a 60 segundos
                        //        std::cout << "ENTRA"<< std::endl;
                        //        break;
                        //    }
                        //}
                    }else{
                        std::cout << "Control de errores";
                        //Hacer que no se borre el arma cuando pasa de zona cambiar el valor del fore en vez de a 1 al tam del invenatario
                    }
                }else{
                    std::cout << "Ese arma no esta disponible,sorry";
                }
            }

            if(device->processInput(GLFW_KEY_1)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_1});
                itemCmp->m_seleccionado = Weapons_utilities::Espada;
                std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;
            }

            if(device->processInput(GLFW_KEY_2)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_2});
                itemCmp->m_seleccionado = Weapons_utilities::Escudo;
                std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;
            }

            if(device->processInput(GLFW_KEY_3)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_3});
                itemCmp->m_seleccionado = Weapons_utilities::Arco;
                std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;  
            }

            if(device->processInput(GLFW_KEY_4)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_4});
                itemCmp->m_seleccionado = Weapons_utilities::Bomba;
                std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;
            }

            if(device->processInput(GLFW_KEY_5)){
                EventManager::getInstancia().addEvent(Event{EventType::Input_5});
                itemCmp->m_seleccionado = Weapons_utilities::Pocion;
                std::cout << "Arma: " << itemCmp->m_seleccionado << std::endl;
            }

            //*************MOVIMIENTO*********
            if(device->processInput(GLFW_KEY_A)){
                //std::cout<<"me estoy moviendo\n";   
                info.direction = 1;
                direc->dirPrevia = 1;
                EventManager::getInstancia().addEvent(Event{EventType::Input_D, info});
                //derecha
            }
            if(device->processInput(GLFW_KEY_D)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 2;
                direc->dirPrevia = 2;
                EventManager::getInstancia().addEvent(Event{EventType::Input_A, info});
                //izquierda   
            } 
            if(device->processInput(GLFW_KEY_W)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 3;
                direc->dirPrevia = 3;
                EventManager::getInstancia().addEvent(Event{EventType::Input_W, info});
                //arriba
            }
            if(device->processInput(GLFW_KEY_S)){
                //std::cout<<"me estoy moviendo\n";
                info.direction = 4;
                direc->dirPrevia = 4;
                EventManager::getInstancia().addEvent(Event{EventType::Input_S, info});
                //abajo
            }
            if(device->processInput(GLFW_KEY_A) && device->processInput(GLFW_KEY_W)){
                info.direction = 5;
                direc->dirPrevia = 5;
                info.rotation = 30;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WD, info});
                // Dirección hacia derecha-arriba
            }
            else if(device->processInput(GLFW_KEY_D) && device->processInput(GLFW_KEY_W)){
                info.direction = 6;
                direc->dirPrevia = 6;
                EventManager::getInstancia().addEvent(Event{EventType::Input_WA, info});
                // Dirección hacia izquierda-arriba
            }
            else if(device->processInput(GLFW_KEY_A) && device->processInput(GLFW_KEY_S)){
                info.direction = 7;
                direc->dirPrevia = 7;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SD, info});
                // Dirección hacia derecha-abajo
            }
            else if(device->processInput(GLFW_KEY_D) && device->processInput(GLFW_KEY_S)){
                info.direction = 8;
                direc->dirPrevia = 8;
                EventManager::getInstancia().addEvent(Event{EventType::Input_SA, info});
                //Dirección hacia izquierda-abajo
            }
        }
}

void RavenGraphics::getInputControls(){
    
}

void RavenGraphics::getInputPause(){
    
}

//*************METODOS DE ANYADIR Y BORRAR ENTIDADES****
void RavenGraphics::Addcamera() {
    //device->crearCamara(50, nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(-60.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), false, -50.0, 50.0, -37.5, 37.5, -1000.0, 1000.0);
    auto posicion = device->getSceneManager()->getNodoFromID(1)->getTraslacion();
    auto camcmp = manager->getComponents<CameraComponent_t>();
    ourCamera = device->crearCamara(camcmp[0].getEntityID(), nullptr, glm::vec3(posicion.x, posicion.y, posicion.z), glm::vec3(45.f, 180.f, 0.f), glm::vec3(1.f, 1.f, 1.f), false, -50.0, 50.0, -37.5, 37.5, -1000.0, 1000.0);
    //ourCamera = device->crearCamara(camcmp[0].getEntityID(), nullptr, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), false, -50.0, 50.0, -37.5, 37.5, -1000.0, 1000.0);
}

void RavenGraphics::addEntities(EventInfo info) { 
    
    for(auto& ren : manager->getComponents<RenderComponent_t>()){
        auto* ent = manager->getEntityByID(ren.getEntityID());
        if(ent){
            auto phy = ent->getComponent<PhysicsComponent_t>();
            if(phy && ren.isVisible == true){
                std::cout << "Nombre e ID : "  << ent->getName() << " : " << ent->getEntityID() << std::endl;
                auto texture = device->crearTextura(ren.texturePath.data());
                std::cout << "ROTACION X Y Z :  " << phy->rx << " " << phy->ry << " " << phy->rz << " " << std::endl;
                auto ourModel = device->crearModelo(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(phy->rx,phy->ry,phy->rz), glm::vec3(1.f, 1.f, 1.f), ren.modelPath.data(), texture);
                //if(ent->getName() == "Casa") {ourModel->setVisibilidad(false);}
                //auto ourModel = device->crearModelo(ent->getEntityID(), nullptr, glm::vec3(phy->x,phy->y,phy->z), glm::vec3(0.f,0.0,0.f), glm::vec3(1.f, 1.f, 1.f), ren.modelPath.data(), texture);
            }
        }
    }
    Addcamera();

    /*auto posicion = device->getSceneManager()->getNodoFromID(1)->getTraslacion();
    auto texture = device->crearTextura("media/Texturas/Bosque/Cofre/Cofre");
    ourCofre = device->crearModelo(-1, nullptr, glm::vec3(posicion.x, posicion.y + 2.f, posicion.z), glm::vec3(0.f,0.f,0.f), glm::vec3(1.f, 1.f, 1.f), "media/obj/Bosque/Cofre.obj", texture);
    ourCofre->setVisibilidad(false);*/
}

void RavenGraphics::addEntity(EventInfo info){
    //Esta funcion deberia cambiarsele el nombre porque va a ser para crear 
    //Creamos un shoot
    
    auto texture = device->crearTextura("media/Texturas/Bosque/flecha/flecha");
    device->crearModelo(info.id, nullptr, glm::vec3(info.posX,4.55872,info.posZ), glm::vec3(0.f,0.f,0.f), glm::vec3(1.f, 1.f, 1.f), "media/obj/Bosque/flecha.obj", texture);
    
}

void RavenGraphics::setPositionWeapons(EventInfo info){
    auto nodoWeapon = device->getSceneManager()->getNodoFromID(info.id); 
    nodoWeapon->setTraslacion(glm::vec3(info.posX,info.posY,info.posZ));
    auto [rx,ry,rz] = info.rotationAxis;
    nodoWeapon->setRotacion(glm::vec3(rx,ry,rz));
    nodoWeapon->setVisibilidad(true);
}

void RavenGraphics::removeEntities(EventInfo info){
    //Destruimos todas las entidades menos la del personaje
    device->endScene();
    device->beginScene();
}

void RavenGraphics::removeEntity(EventInfo info){
    device->borrarNodo(device->getSceneManager()->getNodoFromID(info.id));
}

//*************OTROS METODOS******
bool RavenGraphics::run() {
    return !glfwWindowShouldClose(device->getWindow());
}

void RavenGraphics::renderScene() {

}

void RavenGraphics::shutEngine(){

}

void RavenGraphics::addManager(EntityManager_t& mg){
    manager = &mg;
}

void RavenGraphics::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Render_Change_Zone,std::bind(&RavenGraphics::addEntities,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Delete_Entities_Render,std::bind(&RavenGraphics::removeEntities,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Create_Shot_MG,std::bind(&RavenGraphics::addEntity,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Remove_Entity_MG,std::bind(&RavenGraphics::removeEntity,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::setWeaponsPos,std::bind(&RavenGraphics::setPositionWeapons,this,std::placeholders::_1)));
}

void RavenGraphics::worldPhysics(std::shared_ptr<BulletEngine> w){
    if(w != nullptr){
        world = w;
    }
}

void RavenGraphics::checkColisions(){
    
}