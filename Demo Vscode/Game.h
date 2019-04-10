#ifndef GAME
#define GAME

#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_syswm.h>
#include <windows.h>
#include <psapi.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include "objects/Circle.h"
#include "objects/RectangleObj.h"
#include "Haskell/Physics_stub.h"
#include "NativePhysics/NativePhysics.h"

using namespace std;

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

/*
* Game class
* Game object is created, updates and renders objects
*/
class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void nativeUpdate();
	void haskellUpdate();
	void render();
	void printData();
	void createObjs();
	
	// Fonts
	void setUpFont();
	TTF_Font* Arial;

	// Window & Renderer
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	// Objects & SDL_COLOURS
	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };
	SDL_Color green = { 0, 255, 0, 255 };
	vector<Circle*> objs;
	RectangleObj* m_ground;
	RectangleObj* m_left;
	RectangleObj* m_right;
	RectangleObj* m_top;
	RectangleObj* m_spawn;

	bool m_exitGame = false;

	float result = 0;

	// Timers
	Uint32 old_time, current_time;
	float ftime;

	// SDL image
	SDL_Surface * m_image;
	SDL_Texture * m_texture;

	// Physics
	bool m_haskell = false;
	NativePhysics m_physics;
	int operations = 0;
	bool collided = false;

	// Profiling
	bool profiling = false;
	void initChecks();
	double getCurrentVal();
	double getRam();
	bool operChecks[100];
	std::ofstream myfile;
	int row = 1;
};



#endif // !GAME
