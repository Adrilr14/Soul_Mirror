#include <ecs/man/entityManager.hpp>
#include <algorithm>
#include <string_view>
#include <game/cmp/IAComponent.hpp>	
#include <game/cmp/RenderComponent.hpp>
#include <game/cmp/CameraComponent.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/StaticComponent.hpp>
#include <game/cmp/HPComponent.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <EventManager/EventManager.hpp>
#include <iostream>

EntityManager_t::EntityManager_t(){
	m_Entities.reserve(kMAXENTITIES);
	addEventListeners();
}

void EntityManager_t::addEventListeners(){
	std::cout<<"estoy en el addlisteners del entitymanager\n";
	EventManager::getInstancia().AddEventToListener(EventListener(EventType::Delete_Entities_Manager,std::bind(&EntityManager_t::deleteEntities,this,std::placeholders::_1)));
}

EntityManager_t::~EntityManager_t(){

}

Entity_t& EntityManager_t::createEntity(std::string_view n){
	std::cout<<"Estoy en el entity manager y entro al createEntity\n";
	std::cout<<"Estoy en el entity manager y este es el size actual del vector: "<<m_Entities.size()<<"\n";
	//m_Entities.clear();
	//std::cout<<"Estoy en el entity manager y este es el size actual del vector despues de hacer otro clear: "<<m_Entities.size()<<"\n";
	return m_Entities.emplace_back(n);
}


void EntityManager_t::createEntities(){

}

bool EntityManager_t::IsEmpty(){
	return m_Entities.empty();
}

const Entity_t* EntityManager_t::getEntityByID(EntityID_t eid) const{
	auto ent = std::find_if(m_Entities.begin(),m_Entities.end(),
	[&eid](const Entity_t& e) {return e.getEntityID() == eid;});

	if(ent == m_Entities.end()){
		return nullptr;
	}
	return ent.base();
}

//Falta el drawEntities que esta por los videos 37 o asi !!!!! TENERLO EN CUENTA PARA HACER LO EN EL IRRLICHT

Entity_t* EntityManager_t::getEntityByID(EntityID_t eid){
	auto ent = const_cast<const EntityManager_t*>(this)->getEntityByID(eid);
	return const_cast<Entity_t*>(ent);
}

void EntityManager_t::deleteEntities(EventInfo info){
	std::cout<<"Estoy en el entity manager y entro al delete entities\n";
	//este metodo borra las entidades cada vez que se cambia de zona, excepto el player que siempre estara en la primera posicion del array
	//m_Entities.erase(m_Entities.begin(), m_Entities.end());
	m_components.clearAll();
	m_Entities.clear();
	std::cout<<"Estoy en el entity manager y este es el size del mcomponents: "<<m_components.size()<<"\n";
	
	std::cout<<m_Entities.size()<<" "<<m_Entities.capacity()<<"\n";
	std::cout<<"Size del mcomponents despues de hacer un clear: "<<m_components.size()<<"\n";
	//m_Entities.reserve(100);
	std::cout<<"Estoy en el entity manager y sigo aqui despues de sacar el size y el capacity\n";
	//EventManager::getInstancia().addEvent(Event{EventType::Change_Zone,info});
	//m_Entities.shrink_to_fit();
	//obviamente despues de borrar las entitys del array, debo vaciar tambien los arrays de componentes
	//iavec.shrink_to_fit();;
	//renvec.clear();
	//renvec.shrink_to_fit();
}