#include <ecs/man/entityManager.hpp>
#include <algorithm>
#include <string_view>

EntityManager_t::EntityManager_t(){
	m_Entities.reserve(kMAXENTITIES);
}

EntityManager_t::~EntityManager_t(){

}

Entity_t& EntityManager_t::createEntity(std::string_view n){
	return m_Entities.emplace_back(n);
}


//Entity_t& EntityManager_t::createEntity(float whd,int32_t ax,int32_t ay,int32_t az,int type,const std::string_view nombre,const std::string_view ruta){
//	//auto& e = m_Entities.emplace_back(ax,ay,az);
//	
//	auto& e  = m_Entities.emplace_back(type);
//	auto& ph = m_components.createComponent<PhysicsComponent_t>(e.getEntityID());
//	auto& rn = m_components.createComponent<RenderComponent_t>(e.getEntityID());
//	rn.loadFilesNames(nombre,ruta);
//	if(type == 1 || type == 2){ //si es 1 significa que la entidad es mi personaje principal
//		ph.vx = 0.015;
//		ph.vz = 0.015;
//		ph.x = ax; ph.y = ay; ph.z = az;
//		//std::cout<<whd<<std::endl;
//		e.addComponent(ph);
//		e.addComponent(rn);
//		//ph.vy = 1.0;
//		auto& direccion = m_components.createComponent<DirecComponent_t>(e.getEntityID());
//		direccion.dir = 4;
//		e.addComponent(direccion);
//	}
//	return e;
//}
//
//void EntityManager_t::addInputComponent(Entity_t& e){
//	if(!e.getComponent<RenderComponent_t>()){
//		auto& in = m_components.createComponent<InputComponent_t>(e.getEntityID());
//		e.addComponent(in);
//	}
//}
//
void EntityManager_t::createEntities(){

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