#include <game/sys/physics.hpp>
#include <facade/ControllerMan.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <iostream>

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsInit() const{
    ControllerMan::p().controller().physicsInit();
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsUpdate(GameCTX_t& g) const{
     //cojo la primera entidad, que es el personaje
    //std::cout<<"Direccion actual:"<<e.direcc->dir<<std::endl;
    //std::cout<<"Velocidad actual X:"<<e.physics->vx<<" Velocidad actual Z:"<<e.physics->vz<<std::endl;
    //compruebo que ni la direccion ni el physics sean nullptr
    //1:derecha 2:izquierda 3:arriba 4:abajo 5:arriba derecha 6:arriba izquierda 7:abajo derecha 8:abajo izquierda
     
     for(auto& phy : g.template getComponents<PhysicsComponent_t>()){
        auto* e = g.getEntityByID(phy.getEntityID());
        if(e && e->template getComponent<DirecComponent_t>()){  
            auto* dircmp = e->template getComponent<DirecComponent_t>();
            switch(e->template getComponent<DirecComponent_t>()->dir){
            //de 1 a la 4 direcciones en un solo eje
            case 1:
                phy.x += phy.vx;
                break;

            case 2:
                phy.x -= phy.vx;
                break;

            case 3:
                phy.z += phy.vz;
                break;

            case 4:
                phy.z -= phy.vz;
                break;
            //movimientos en diagonal
            case 5:
                phy.z += phy.vz;
                phy.x += phy.vx;
                break;

            case 6:
                phy.z += phy.vz;
                phy.x -= phy.vx;
                break;

            case 7:
                phy.z -= phy.vz;
                phy.x += phy.vx;
                break;

            case 8:
                phy.z -= phy.vz;
                phy.x -= phy.vx;
                break;
            }
            //std::cout<<"Posicion en X: "<<phy.x<<" Posicion en Z: "<<phy.z<<"\n";
            dircmp->dir = -1;
        }
        
      
            //if(ms_keyboard.isKeyPressed(inp.key_left)){
            //    std::cout << "toca la left" << std::endl;
            //}
    }
    //ControllerMan::p().controller().physicsUpdate(g.getEntities());
}
  
    
    //e.direcc->dir = 4;
    //paso la entidad para que se actualice la posicion del cubo y la pongo a 4 para que se pare
    //ir.updateNodeFromEntity(e);
