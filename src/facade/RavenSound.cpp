#include "RavenSound.hpp"
#include "../EventManager/EventManager.hpp"

RavenSound& RavenSound::getInstance(){
    static RavenSound instance;
    return instance;
}

void RavenSound::loadBanks(const std::string& bankName){
    sonido.loadBanks(bankName,FMOD_STUDIO_LOAD_BANK_NORMAL);
    addEventListeners();
}

void RavenSound::loadEvent(const std::string& eventName){
    sonido.loadEvent(eventName);
}

void RavenSound::playEvent(const std::string& eventName){
    sonido.playEvent(eventName);
}

void RavenSound::playEvent(const std::string& eventName,const std::string& eventParam,float changeParam){
    sonido.playEvent(eventName,eventParam,changeParam);
}

void RavenSound::stopEvent(const std::string& eventName){
    sonido.stopEvent(eventName,false);
}

void RavenSound::stopMusic(EventInfo info){
    sonido.stopEvent(info.ruta,false);
}

void RavenSound::studioUpdate(){
    sonido.studioUpdate();
}

void RavenSound::audioClose(){
    sonido.audioClose();
}

void RavenSound::walking(EventInfo info){
    if(aux == 0)
        playEvent("event:/Efectos/caminar","Terreno",1.0);
    ++aux;    
}

void RavenSound::stopwalking(EventInfo){
    aux = 0;
    stopEvent("event:/Efectos/caminar");
}

void RavenSound::espada(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",0);
}

void RavenSound::escudo(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",3);
}

void RavenSound::bomba(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",2);
}

void RavenSound::arco(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",1);
}

void RavenSound::pocion(EventInfo){
    playEvent("event:/Efectos/cambio_arma/desenfundar","Arma",4);
}

void RavenSound::correr(EventInfo){
    playEvent("event:/Efectos/correr");
}

void RavenSound::beber(EventInfo){
    playEvent("event:/Efectos/ataque/beber");
}

void RavenSound::cortar(EventInfo){
    playEvent("event:/Efectos/colisiones/corte");
}

void RavenSound::colisionEscudo(EventInfo){
    playEvent("event:/Efectos/colisiones/escudo");
}

void RavenSound::nocolisionEspada(EventInfo){
    playEvent("event:/Efectos/ataque/Espada_sin_colision");
}

void RavenSound::explosion(EventInfo){
    playEvent("event:/Efectos/ataque/explosion");
}

void RavenSound::fuego(EventInfo){
    playEvent("event:/Efectos/fuego");
}

void RavenSound::colisionesHerida(EventInfo){
    playEvent("event:/Efectos/colisiones/herida");
}

void RavenSound::AmbienteIndustrial(EventInfo){
    playEvent("event:/Ambientes/industrial");
}

void RavenSound::AmbienteNieve(EventInfo){
    playEvent("event:/Ambientes/Nieve");
}

void RavenSound::soltarFlecha(EventInfo){
    playEvent("event:/Efectos/ataque/soltar_flecha");
}

void RavenSound::soltarObjeto(EventInfo){
    playEvent("event:/Efectos/ataque/soltar_objeto");
}

void RavenSound::muerte(EventInfo){
    playEvent("event:/Efectos/colisiones/muerte");
}

void RavenSound::flecha(EventInfo){
    playEvent("event:/Efectos/colisiones/flecha");
}

void RavenSound::objeto(EventInfo){
    playEvent("event:/Efectos/colisiones/objeto");
}

void RavenSound::abrirPuerta(EventInfo){
    playEvent("event:/Efectos/abrir_puerta");
}

void RavenSound::arrastrar(EventInfo){
    playEvent("event:/Efectos/arrastrar");
}

void RavenSound::mecanismo(EventInfo){
    playEvent("event:/Efectos/mecanismo");
}

void RavenSound::coger(EventInfo){
    playEvent("event:/Efectos/coger");
}

void RavenSound::AmbienteBosque(EventInfo){
    playEvent("event:/Ambientes/Bosque");
}

//EFECTOS SONIDO MENU
void RavenSound::menuBack(EventInfo){
    playEvent("event:/Menús/back");
}

void RavenSound::menuCambio(EventInfo){
    playEvent("event:/Menús/cambio");
}

void RavenSound::menuSelect(EventInfo){
    playEvent("event:/Menús/select");
}

void RavenSound::addEventListeners(){
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_W,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_A,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_S,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_D,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WD,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_WA,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SD,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_SA,std::bind(&RavenSound::walking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Stop_Walking,std::bind(&RavenSound::stopwalking,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_1,std::bind(&RavenSound::espada,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_2,std::bind(&RavenSound::escudo,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_3,std::bind(&RavenSound::pocion,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_4,std::bind(&RavenSound::arco,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Input_5,std::bind(&RavenSound::bomba,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Beber,std::bind(&RavenSound::beber,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Correr,std::bind(&RavenSound::correr,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Corte,std::bind(&RavenSound::cortar,this,std::placeholders::_1)));
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Desierto,std::bind(&RavenSound::desierto,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Colision_Escudo,std::bind(&RavenSound::colisionEscudo,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Espada_No_Colision,std::bind(&RavenSound::nocolisionEspada,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Explosion,std::bind(&RavenSound::explosion,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Fuego,std::bind(&RavenSound::fuego,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Herida,std::bind(&RavenSound::colisionesHerida,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Industrial,std::bind(&RavenSound::AmbienteIndustrial,this,std::placeholders::_1)));
    //EventManager::getInstancia().AddEventToListener(EventListener(EventType::Nieve,std::bind(&RavenSound::beber,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Soltar_Flecha,std::bind(&RavenSound::soltarFlecha,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Soltar_Objeto,std::bind(&RavenSound::soltarObjeto,this,std::placeholders::_1))); //Lanzar el barril
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Muerte,std::bind(&RavenSound::muerte,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Objeto,std::bind(&RavenSound::objeto,this,std::placeholders::_1))); //Cuando choca el barril con un objeto 
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Abrir_Puerta,std::bind(&RavenSound::abrirPuerta,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Arrastrar,std::bind(&RavenSound::arrastrar,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Mecanismo,std::bind(&RavenSound::mecanismo,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Coger,std::bind(&RavenSound::coger,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Bosque,std::bind(&RavenSound::AmbienteBosque,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Menu_Back,std::bind(&RavenSound::menuBack,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Menu_Change,std::bind(&RavenSound::menuCambio,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Menu_Select,std::bind(&RavenSound::menuSelect,this,std::placeholders::_1)));
    EventManager::getInstancia().AddEventToListener(EventListener(EventType::Stop_Music,std::bind(&RavenSound::stopMusic,this,std::placeholders::_1)));
}