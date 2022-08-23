#pragma once


#include <cstdint>
#include <vector>
#include <string>
#include <string_view>
#include "../cmp/entity.hpp"
#include "../util/typealias.hpp"
#include "../man/componentstorage.hpp"

struct EventInfo;

struct EntityManager_t {
	static constexpr std::size_t kMAXENTITIES {1000};

	explicit EntityManager_t();
	~EntityManager_t();
	
	Entity_t& createEntity(std::string_view);
	
	template <typename CMP_t> 
	CMP_t& 	addComponent(Entity_t& e){
		CMP_t* cmp_ptr { e.getComponent<CMP_t>() };
		if(!cmp_ptr){
			auto& cmp = m_components.createComponent<CMP_t>(e.getEntityID());
			e.addComponent(cmp);
			cmp_ptr = &cmp;
		}
		
		return *cmp_ptr;
	}
	void addEventListeners();
	void createEntities();
	void deleteEntities(EventInfo);

	const Entity_t* getEntityByID(EntityID_t eid) const;
          Entity_t* getEntityByID(EntityID_t eid);

	const Vec_t<Entity_t>& getEntities() const {return m_Entities;}
	Vec_t<Entity_t>& getEntities()   {return m_Entities;}

	template <typename CMP_t>
	const Vec_t<CMP_t>&
	getComponents() const {
		return m_components.getComponents<CMP_t>();
	}

	template <typename CMP_t>
	Vec_t<CMP_t>&
	getComponents() {
		return m_components.getComponents<CMP_t>();
	}

	template <typename CMP_t>
	Entity_t* getEntityPointer(const CMP_t& cmp){
		return getEntityByID(cmp.getEntityID());
	}

	template <typename CMP_t>
	const Entity_t* getEntityPointer(const CMP_t& cmp) const {
		return getEntityByID(cmp.getEntityID());
	}

	template <typename CMP_t,typename CMPR_t>
	const CMPR_t& getRequiredComponent(const CMP_t& cmp) const {
		auto* e = getEntityPointer(cmp);
		if(e){
			return e->template getComponent<CMPR_t>();
		}
		return nullptr;
	}

	template <typename CMP_t,typename CMPR_t>
	CMPR_t& getRequiredComponent(const CMP_t& cmp) {
		const CMPR_t* rc = const_cast<const EntityManager_t*>(this)->getRequiredComponent(cmp);
		return const_cast<CMPR_t*>(rc);
	}

	template <typename CMP>
	void destroyCMPByID(EntityID_t eid){
		auto* entity =  getEntityByID(eid);
		if(!entity){
			return; //TODO Error Management
		}
		auto* cmpttr = m_components.deleteCmpByTypeID(CMP::getComponentTypeID(),eid);
	}

	bool IsEmpty();
	void updateEntitiesToBeDestroyed();
	void destroyEntityByID(EntityID_t eid);
	void destroyEntityECSMG(int id);


private:
	Vec_t<Entity_t> m_Entities{};
	ComponentStorage_t m_components{kMAXENTITIES};
};


