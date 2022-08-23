#pragma once


#include <cstdint>
#include "Controller.hpp"
#include <irrlicht.h>

using VecEntities_t = Vec_t<Entity_t>;
struct EventInfo;


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
    void addEntity(EventInfo info);
    void addAnimations() override {};// crea todas las animaciones del juego
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
    std::vector<std::string> splitPattern(const std::string_view s,const char* delimiter);
    void checkColisions() override;
        
private:
    Input input;
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
