#include "BulletEngine.hpp"
#include "../../EventManager/EventManager.hpp"
#include <iostream>
//#include <btDefaultCollisionConfiguration.h>
//#include <btCollisionDispatcher.h>


void BulletEngine::createWolrdSystem(){
    config = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher = std::make_unique<btCollisionDispatcher>(config.get());
    btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
    bdInterface = std::make_unique<btDbvtBroadphase>();
    solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    world = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(),bdInterface.get(),solver.get(),config.get());
	world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
    
    //config = std::make_unique<btDefaultCollisionConfiguration>();
    //dispatcher = std::make_unique<btCollisionDispatcher>(config.get());
    //bdInterface = std::make_unique<btDbvtBroadphase>();
    //solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    //world = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(),bdInterface.get(),solver.get(),config.get());

    world->setGravity(btVector3(0,gravity,0));
}

void BulletEngine::clearScene(){
	for (int i=world->getNumCollisionObjects()-1; i>=0 ;i--){
		btCollisionObject* obj = world->getCollisionObjectArray()[i];
        if(obj != character->getGhostObject()){
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body && body->getMotionState())
            {
                delete body->getMotionState();
            }
            world->removeCollisionObject( obj );
            delete obj;   
        }
	}

	//delete collision shapes
    for( const auto& [key, value] : shapes ) {
        btCollisionShape* shape = key;
		delete shape;
    }
	shapes.clear();
}

bool BulletEngine::hasCollision(std::string_view name) {
	btManifoldArray manifoldArray;
	btBroadphasePairArray &p = character->getGhostObject()->getOverlappingPairCache()->getOverlappingPairArray();
	int numP = p.size();
	for(int i = 0; i < numP;i++) {

		manifoldArray.clear();

		const btBroadphasePair &pareja = p[i];

		btBroadphasePair *collisionPair = world->getPairCache()->findPair(pareja.m_pProxy0, pareja.m_pProxy1);
		if(!collisionPair){
            continue;
        }

		if(collisionPair->m_algorithm) {
			collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);
		}

		for(int j = 0; j <manifoldArray.size();j++) {
			btPersistentManifold *manifold = manifoldArray[j];
			for(int k = 0;k < manifold->getNumContacts();k++) {
                auto isFirstBody = manifold->getBody1()->getCollisionShape();
                for( const auto& [key, value] : shapes ) {
                    if(key == isFirstBody){
                        if(value == name.data()){
                            std::cout << "Colisiona " << value << " " << name.data() << std::endl; 
                            return true;
                        }
                    }
                }
                //return true;
			}
		}
	}
	return false;
}

void BulletEngine::updateCollisionEngine(){
    //std::cout << "Linea velocity" << character->getL 
    //auto velocity = character->getLinearVelocity();
    //std::cout << "Velocidad en X Y Z : " << velocity.getX() << " " << velocity.getY() << " " << velocity.getZ() << " " << std::endl;
    //auto colision = hasCollision("Valla");
    //std::cout << "Colisiona : "  << colision << std::endl;
    world->stepSimulation(0.1);
}


void BulletEngine::createCharacter(btScalar posX,btScalar posY,btScalar posZ){

    btTransform startTransform;
    startTransform.setIdentity ();
    startTransform.setOrigin (btVector3(posX,posY,posZ));

    //m_ghostObject = new btPairCachingGhostObject();
    m_ghostObject = std::make_unique<btPairCachingGhostObject>();
	m_ghostObject->setWorldTransform(startTransform);
    bdInterface->getOverlappingPairCache()->setInternalGhostPairCallback( new btGhostPairCallback());
    btScalar characterHeight= heightCh;   
	btScalar characterWidth = widthCh;   
    btConvexShape* capsule = new btBoxShape(btVector3(characterWidth,characterHeight,lengthCh));
    
    m_ghostObject->setCollisionShape (capsule);
	m_ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);
    
    btScalar stepHeight = btScalar(0.35);
    character = std::make_unique<btKinematicCharacterController>(m_ghostObject.get(),capsule,stepHeight);
	//character = new btKinematicCharacterController (m_ghostObject.get(),capsule,stepHeight);
    character->setGravity(btVector3(0,gravity,0));
    world->addCollisionObject(m_ghostObject.get(),btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
    world->addAction(character.get());
    //character->setLinearVelocity(btVector3(-1,0,0));  
}


//Definir una función que cree objetos estaticos que solo tengan una colision como las paredes, pero que no interactuar con el entorno
//Es decir que solo sean objetos con los que te puedes chocar y ya
void BulletEngine::createObjects(float posX,float posY,float posZ,float w,float h,float l,bool staticE,std::string_view name){
    //std::unique_ptr<btCollisionShape> colShape = std::make_unique<btBoxShape>(btVector3(5,5,5));
    btCollisionShape* colShape = new btBoxShape(btVector3(w/2,h/2,l/2));
    
    if(staticE == false){ //Esta linea define si ese Objeto va a tener una interacción de algun tipo(no solo colisiona)
        if(name != "Enemy"){
            shapes.emplace(colShape,name.data());
        }
    }

    btTransform startTransform;
    startTransform.setIdentity();

    btScalar tMass(0.0f);
    bool isDynamic = (tMass != 0.f);

    btVector3 localInertia(0,0,0);
    if (isDynamic)
        colShape->calculateLocalInertia(tMass,localInertia);

    startTransform.setOrigin(btVector3(posX,posY,posZ));
    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    auto info = btRigidBody::btRigidBodyConstructionInfo(tMass,motionState,colShape,localInertia);
    btRigidBody* body = new btRigidBody(tMass,motionState,colShape,localInertia);
    
    
    world->addRigidBody(body);
    world->setInternalTickCallback(BulletEngine::myTickCallback);
}


void BulletEngine::moveKinematicObject(float x,float y, float z) {
	btTransform t = character->getGhostObject()->getWorldTransform();
	btVector3 origin = t.getOrigin() + btVector3(x,y,z);
	t.setOrigin(origin);
	character->getGhostObject()->setWorldTransform(t);
}


void BulletEngine::walkingCharacter(float posX,float posY,float posZ){
    //Antes de cambiar la posicion tengo que comprobar que no se choque con ningun elemento
    //moveKinematicObject(character->getGhostObject(),btVector3(posX,posY,posZ));
    character->setLinearVelocity(btVector3(posX,posY,posZ));
}


void BulletEngine::myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
    int numManifolds = world->getDispatcher()->getNumManifolds();
    //printf("numManifolds = %d\n",numManifolds);
}

void BulletEngine::addEventListeners(){

}


btKinematicCharacterController* BulletEngine::getCharacter(){
    return character.get();
}

btDiscreteDynamicsWorld* BulletEngine::getWorld(){
    return world.get();
}
//Ahora tenemos que crear un callBack que recoja cuando se produzca una collision

