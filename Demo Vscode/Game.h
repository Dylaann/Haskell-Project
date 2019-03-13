#ifndef GAME
#define GAME

#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "objects/Circle.h"
#include "objects/RectangleObj.h"
#include "Haskell/Move_stub.h"

using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update();
	void render();
	
	void setUpFont();
	TTF_Font* Arial;

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };
	vector<Circle*> objs;
	RectangleObj* m_ground;

	bool m_exitGame = false;

	float result = 0;
};



#endif // !GAME
