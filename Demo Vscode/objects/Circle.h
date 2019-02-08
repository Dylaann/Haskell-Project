#ifndef CIRCLE
#define CIRCLE

#include <SDL.h>
#include <SDL_stdinc.h>
#include <stdlib.h>
#include <iostream>

class Circle {

public:
	Circle(int x, int y, int radius, SDL_Color col);
	~Circle();

    void update();
    void render(SDL_Renderer* renderer);
    void setPosX();

private:
    SDL_Color m_color;
	int m_x;
    int m_y;
    int m_radius;
};



#endif // !Circle   