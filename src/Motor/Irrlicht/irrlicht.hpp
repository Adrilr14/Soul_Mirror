#pragma once

#include <irrlicht.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <facade/RavenSound.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <game/cmp/PhysicsComponent.hpp>
#include <game/cmp/InputComponent.hpp>
#include <game/cmp/StaticComponent.hpp>
#include <game/cmp/DirecComponent.hpp>
#include <game/cmp/IAComponent.hpp>
#include <ecs/util/typealias.hpp>


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


struct Irrlicht_t;
struct Entity_t;
struct EntityManager_t;


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
    //void moveEnemyPosIni(int died, irr::scene::ISceneNode* enemy, irr::core::vector3df posIni, irr::f32 MOVEMENT_SPEED_ENEMY, irr::f32 frameDeltaTime, std::vector<irr::scene::ISceneNode*> collideables);
	//bool moveCam(bool cam, irr::scene::ISceneNode *map);
    void moveDraggable(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* draggable, irr::f32 MOVEMENT_SPEED, irr::f32 frameDeltaTime, std::vector<irr::scene::ISceneNode*> collideables);
    void moveObject (irr::scene::ISceneNode* object, irr::f32 MOVEMENT_SPEED, irr::f32 frameDeltaTime, int direction);
    //void printXYZ(scene::ISceneNode *);


private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    bool LeftClickDown;
};


struct Irrlicht_t {

using VecEntities_t = Vec_t<Entity_t>;

private:
	RavenSound sound;
	irr::IrrlichtDevice *device;
	irr::video::IVideoDriver *driver;
	irr::scene::ISceneManager *smgr;
	irr::gui::IGUIEnvironment *guienv;
	irr::scene::IAnimatedMesh *mesh;
	irr::scene::IAnimatedMeshSceneNode *node;
	irr::scene::ISceneNode *object;

	// Vectores de objetos
	std::vector<irr::scene::ISceneNode*> collideables; // Array para toos los objetos con colisión
	// Vector para los enemigos
	std::vector<irr::scene::ISceneNode*> enemies;
	// Vector para el rango de los enemigos
	std::vector<irr::scene::ISceneNode*> ranges;
	// Vector para las posiciones iniciales de los enemigos
	std::vector<irr::core::vector3df> posIniEnemies;
	// Vector para las llaves
	std::vector<irr::scene::ISceneNode*> keys;
	// Vector para las puertas que se abren con llave
	std::vector<irr::scene::ISceneNode*> doors;
	// Vector para las puertas que se abren con mecanismos
	std::vector<irr::scene::ISceneNode*> gates;
	// Vector para las pociones
	std::vector<irr::scene::ISceneNode*> potions;
	// Vector para los objetos arrojables
	std::vector<irr::scene::ISceneNode*> barriles;
	// Vector para los objetos arrastrables
	std::vector<irr::scene::ISceneNode*> draggables;
	// Vector para los botones
	std::vector<irr::scene::ISceneNode*> buttons;
	// Vector para los cofres
	std::vector<irr::scene::ISceneNode*> chests;
	// Vector de zonas a las que se puede dirigir
	std::vector<irr::scene::ISceneNode*> zones;
	// Vector de npcs
	std::vector<irr::scene::ISceneNode*> npcs;
	// Vector de nombres para rellenar los vectores al cargar un nivel
	std::vector<std::string> names;

	irr::scene::ICameraSceneNode *camera;
	irr::scene::ICameraSceneNode *scamera;
	irr::scene::ISceneNodeAnimator *anim;
	//irr::core::vector3df save_pos;
	// Creamos el array de posiciones para la animación
    //irr::core::array<irr::core::vector3df> points;

	int zone;			// Número para conocer la zona en la que nos encontramos
	irr::core::vector3df posInicio; // Guardamos la posición inicial para restaurar al jugador por si muere
	bool SwitchCam;
	//bool colisiona;
	int  hit_points;	// Puntos de salud (HP) del jugador
	int  max_hp;		// Puntos de salud (HP) máximos del jugador
	// ---------------------------------------------------------
	int  direction;		// 1 --> derecha; 2 --> izquierda; 3 --> arriba; 4 --> abajo; 
	int throw_direction;// 5 --> derecha-arriba; 6 --> izquierda-arribs; 7 --> derecha-abajo; 8 --> izquierda-abajo;
	// --------------------------------------------------------- 
	int weapon;			// 0 --> Sin arma; 1 --> espada; 2 --> escudo; 3 --> arco; 4 --> bomba; 5 --> pociones;
	// ---------------------------------------------------------
	int shield;			// 0 --> Sin proteger; 1 --> Proteger;
	// ---------------------------------------------------------
	int  died; 			// 0 --> normal; 1 --> golpeado; 2 --> muerto o parado; 3 --> Bebiendo poción; 4 --> Abriendo cofre
	// ---------------------------------------------------------
	int catched;		// 0 --> Sin coger; 1 --> Cogido; 2 --> Lanzado; 3 --> Arrastrable cogido; 4 --> Flecha disparada
	// ---------------------------------------------------------
	int bomb;			// 0 --> Sin poner; 1 --> Puesta;
	// ---------------------------------------------------------
	bool isPressed; 	// Comprobar si se sigue pulsando una tecla
	int  arrows;		// Número de flechas
	int  key_gotcha;	// Número de llaves
	int  potion_gotcha; // Número de pociones


	int lastFPS = -1;
	irr::u32 then;
	irr::f32 MOVEMENT_SPEED;
	irr::f32 MOVEMENT_SPEED_ENEMY = 10.0f;



	irr::gui::IGUIFont* font;
	irr::core::vector3df posPlayer;
	irr::core::vector3df scale;
	irr::core::vector3df rotation;
	std::string zoneAux;
	const char* zoneToChange;
	int pos_object = 0;
    bool colBomba = false;
    int contFPS = 0;
    bool zoneChange = true;
	bool updateHearts = true;
	bool open = false;
	bool fin = false;
	Input input;
	int menu = 0;
	bool pause = false;
	irr::f32 frameDeltaTime;

	irr::gui::IGUIButton *btn;
    //irr::gui::IGUIWindow* win;
	irr::gui::IGUITreeView * treeWindow;
	irr::gui::IGUITabControl* tabctrl;
	const wchar_t* text;
	irr::video::ITexture* img;
	//irr::gui::IGUIButton *startButton;
	irr::gui::IGUIButton *resumeButton;
	//irr::gui::IGUIButton *saveButton;
	irr::gui::IGUIButton *loadButton;
	irr::gui::IGUIButton *exitButton;
	

public:
	Irrlicht_t(){};
	void createWindow(uint32_t, uint32_t);
	void createEntities(const VecEntities_t&);
	void createWindow(uint32_t w, uint32_t h,const VecEntities_t& entities);
	void physicsInit();
	void renderInit();
	void run();
	void drop();
	void saveGame();
	bool loadGame();
	void loadZone();
	void fillVectors();
	void drawZone(const char* z, int pos_object);
	void comproveHP(irr::core::vector3df cubePosition, bool colBomba);
	void beginScene();
	void endScene();
	void NodeLoadMaterial();
	void addCamera();
	void cameraTrack(Entity_t*);
	void checkTeclado(Entity_t*);
    //Funciones colisiones
    static bool checkCollision(irr::scene::ISceneNode* one, irr::scene::ISceneNode* two);
    static bool checkCollisionCollideables(irr::scene::ISceneNode* one, std::vector<irr::scene::ISceneNode*> collideables);
    static bool checkCollisionOneEnemy(irr::scene::ISceneNode* one, irr::scene::ISceneNode* enemy);
    static bool checkCollisionObject(irr::scene::ISceneNode* cube_player, irr::scene::ISceneNode* object);
	static int checkCollisionZone(irr::scene::ISceneNode* cube_player, irr::scene::ISceneNode* zone);
    static bool checkCollisionEspada(irr::scene::ISceneNode* sword, irr::scene::ISceneNode* enemy, int direction);
    static bool checkPressedButton(irr::scene::ISceneNode* player, irr::scene::ISceneNode* draggable, std::vector<irr::scene::ISceneNode*> buttons);
    static bool checkCollisionBomba(irr::scene::ISceneNode* bomba, irr::scene::ISceneNode* enemy);
    static bool checkCollisionPlayerBomb(irr::scene::ISceneNode* bomba, irr::scene::ISceneNode* cube_player);
	static bool checkCollisionEnemiesPlayer(irr::scene::ISceneNode* range, irr::scene::ISceneNode* cube_player);
    //Funciones render
    void render();
	void renderUpdate(EntityManager_t&);

	bool getDeviceRun() const;
	irr::IrrlichtDevice* getDevice();
	irr::scene::IAnimatedMesh* getMesh();
	irr::scene::IAnimatedMeshSceneNode* getNode();
	irr::scene::ISceneNode* getCube();
};

