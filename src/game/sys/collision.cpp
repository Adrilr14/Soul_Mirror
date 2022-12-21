#include "collision.hpp"
#include "../../game/cmp/DimensionsComponent.hpp"
#include "../../game/cmp/PhysicsComponent.hpp"
#include "../../game/cmp/CollisionComponent.hpp"
#include "../../game/cmp/InputComponent.hpp"
#include "iostream"

bool CollisionSystem_t::Collision(Entity_t& first,Entity_t& second){
    //Para saber si colisionan primero tenemos que obtener:
    //Posiciones y dimensiones de las entidades
    auto fD = first.getComponent<DimensionsComponent_t>();
    auto sD = second.getComponent<DimensionsComponent_t>();

    auto fP = first.getComponent<PhysicsComponent_t>();
    auto sP = second.getComponent<PhysicsComponent_t>();
     
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
                    std::cout << "Colisiona";
                    return true;
                }
            }
        }
    }
    return false;
}


void CollisionSystem_t::update(){
    for(auto& inp : manager.getComponents<InputComponent_t>()){
        for(auto& col : manager.getComponents<CollisionComponent_t>()){
            auto* character = manager.getEntityByID(inp.getEntityID());    
            if(character && character->getComponent<CollisionComponent_t>() 
                         && character->getComponent<DimensionsComponent_t>()
                         && character->getComponent<PhysicsComponent_t>())
            {
                //Si se compone del personaje y tiene todos esos componentes entonces
                auto* objcollider = manager.getEntityByID(col.getEntityID());
                if(objcollider && objcollider->getComponent<PhysicsComponent_t>()
                               && objcollider->getComponent<DimensionsComponent_t>())
                {
                    if(character->getEntityID() != objcollider->getEntityID()){
                        CollisionSystem_t::Collision(*character,*objcollider);
                    }
                }
            }
        }
    }    
}