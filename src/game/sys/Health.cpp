#include "Health.hpp"
#include "../cmp/HPComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "../../ecs/man/entityManager.hpp"
#include "../../Game.hpp"
#include "../../EventManager/EventManager.hpp"

void HealthSystem_t::Update() const{
    //primero saco el player por separado, ya que el player si se queda a 0 de vida no se destruye la entidad, es otro comportamiento
    auto& input = manager.getComponents<InputComponent_t>();
    auto* player = manager.getEntityByID(input[0].getEntityID());
    if(player && player->getComponent<HPComponent_t>()){
        auto* playerHealth = player->getComponent<HPComponent_t>();
        if(playerHealth->life <= 0){
            //se lanza un evento
            EventManager::getInstancia().addEvent(Event{EventType::Muerte});
            EventManager::getInstancia().addEvent(Event{EventType::dead_Animation});
            Game::GetInstance()->setPlayerDead(true);
        }
    }
    //ahora sacamos el resto de entidades con HPComponent
    for(auto& hpcmp : manager.getComponents<HPComponent_t>()){
        if(hpcmp.getEntityID() != player->getEntityID()){
            if(hpcmp.life <= 0){
                auto* entity = manager.getEntityByID(hpcmp.getEntityID());
                entity->SetEntityToDestroy();
            }
        }
    }
}