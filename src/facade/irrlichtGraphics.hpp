#pragma once


#include <cstdint>
#include "Controller.hpp"
#include <irrlicht.h>

using VecEntities_t = Vec_t<Entity_t>;
struct EventInfo;

class DebugDraw : public btIDebugDraw {
private:

   int mode;
   irr::video::IVideoDriver* const driver;
   irr::ILogger* logger;

public:

   DebugDraw(irr::IrrlichtDevice* const device) :
      mode(DBG_NoDebug), driver(device->getVideoDriver()), logger(device->getLogger())
   {

   }

   void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
   {
      irr::video::SColor newColor(255, color[0]*255.0, color[1]*255.0, color[2]*255.0);

      this->driver->draw3DLine(
         irr::core::vector3df(from[0], from[1], from[2]),
         irr::core::vector3df(to[0], to[1], to[2]),
         newColor);
   }

   void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
   {
      static const irr::video::SColor CONTACTPOINT_COLOR(255, 255, 255, 0);

      const btVector3 to(PointOnB + normalOnB*distance);

      this->driver->draw3DLine(
         irr::core::vector3df(PointOnB[0], PointOnB[1], PointOnB[2]),
         irr::core::vector3df(to[0], to[1], to[2]),
         CONTACTPOINT_COLOR);
   }

   void reportErrorWarning(const char* text) {
      this->logger->log(text, irr::ELOG_LEVEL::ELL_ERROR);
   }

   void draw3dText(const btVector3& location, const char* text) { }
   void setDebugMode(int mode) { this->mode = mode; }
   int getDebugMode() const { return this->mode; }
};


class Input : public irr::IEventReceiver
{
public:
    Input();
    // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent& event);
    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
    // This is used to check the left clck (mouse)
    virtual bool IsLeftClickDown() const;
    irr::core::vector3df comproveMovement(irr::scene::ISceneManager* smgr, irr::f32 speed, irr::f32 frame, irr::scene::ISceneNode* one,std::vector<irr::scene::ISceneNode*> collideables, bool died, irr::video::IVideoDriver* driver);
	void moveEnemy(int died, irr::scene::ISceneNode* enemy, irr::core::vector3df pos, irr::f32 MOVEMENT_SPEED_ENEMY, irr::f32 frameDeltaTime, std::vector<irr::scene::ISceneNode*> collideables);   
    void moveDraggable(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* draggable, irr::f32 MOVEMENT_SPEED, irr::f32 frameDeltaTime, std::vector<irr::scene::ISceneNode*> collideables);
    void moveObject (irr::scene::ISceneNode* object, irr::f32 MOVEMENT_SPEED, irr::f32 frameDeltaTime, int direction);

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    bool LeftClickDown;
};



struct irrlichtGraphics : public Controller_t{
    irrlichtGraphics();
    virtual ~irrlichtGraphics();
    //Funciones para el motor de Irrlicht
    void createWindow() override;
    void beginScene() override;
    void getInputInit() override;
    void getInputCredits() override;
    void getInputGame() override;
    void getInputControls() override;
    void getInputPause() override;//la pausa como tal no es un estado, pero hay que recibir su input igualmente
    void updateEntities() override;
    bool run() override;
    void Addcamera() override;
    void cameraUpdate() override;
    void addEntities(EventInfo) override;
    void renderScene() override;
    void endScene() override;
    void shutEngine() override;
    void addManager(EntityManager_t&) override;
    void worldPhysics(std::shared_ptr<BulletEngine> w) override;
    void addEntity(EventInfo info);
    void removeEntity(EventInfo info);
    void probando();
    void addEventListeners();
    void removeEntities(EventInfo);
    void removeEntity(std::size_t);
    void addEntities2();
    void drawInit() override;//dibujado del init state
    void drawCredits() override;//dibujado del credits state
    void drawGame() override;//dibujado del juego
    void drawControls() override;//dibujado del controls state
    void drawPause() override;//la pausa no es un estado como tal, pero hay que dibujar cosas
    int getDirection();
    btDiscreteDynamicsWorld* setWorld();
    std::vector<std::string> splitPattern(const std::string_view s,const char* delimiter);
    void checkColisions() override;
        
private:
    Input input;
    DebugDraw* dbDraw;
    std::shared_ptr<BulletEngine> world;
    irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::gui::IGUIEnvironment *guienv;
	irr::scene::IAnimatedMesh *mesh;
	irr::scene::IAnimatedMeshSceneNode *node;
    irr::scene::ICameraSceneNode *camera;
	irr::scene::ISceneNode *object;
    irr::scene::ISceneNode *object2;
};
