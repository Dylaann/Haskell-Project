#ifndef GAME
#define GAME

#include <SDL.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "objects/Circle.h"

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

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	vector<Circle*> objs;

	bool m_exitGame = false;
};



#endif // !GAME
