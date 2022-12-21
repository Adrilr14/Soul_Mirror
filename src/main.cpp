
#include <ecs/man/entityManager.hpp>
#include <facade/ControllerMan.hpp>
#include <EventManager/EventManager.hpp>
#include <game/util/gameobjectfactory.hpp>
#include "Game.hpp"



int main(){

    Game* game = Game::GetInstance();
    game->InitGame();
    game->MainLoop();
    
    return 0;
}

