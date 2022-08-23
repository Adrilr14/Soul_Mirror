#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "../../ecs/cmp/component.hpp"

struct PlayerComponent_t : ComponentBase_t<PlayerComponent_t>{
    explicit PlayerComponent_t(EntityID_t eid)
    :   ComponentBase_t(eid)
    {};

    void addChildsPermanent(std::size_t id){
        childsPermanent.push_back(id);
    }

    void addTemporal(std::size_t id){ 
        temporal = id;
    }

    void removeTemporal(){
        temporal = 0;
    }

    bool inmunity { false };
    //Aquí agregamos los ids de los objetos que seran los hijos
    //que iran junto con el personaje como por ejemplo la espada,el escudo...
    std::vector<std::size_t> childsPermanent;
    std::size_t temporal { 0 };
    std::unordered_map<std::string,std::string> lista; //Lista de elementos que ya se han completado y que no van a aparecer mas
    std::string zona_player;
    std::string ruta_player;
    bool endgame { false };
};