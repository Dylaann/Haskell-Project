#include "Circle.h"

Circle::Circle(int x, int y, int radius, SDL_Color col) {
	m_x = x;
	m_y = y;
	m_radius = radius;
	m_color = col;
}

Circle::~Circle() {

}

void Circle::update() {

}

void Circle::render(SDL_Renderer* rend) {
    
    SDL_SetRenderDrawColor(rend, m_color.r, m_color.g, m_color.b, m_color.a);

		int point_x = 0;
		int point_y = 0;
		int temp = m_radius;

		while (temp > 0)
		{
			for (int t = 0; t < 360; t++)
			{
				point_x = m_x + (m_radius * SDL_cos(t));
				point_y = m_y + (m_radius * SDL_sin(t));
				SDL_RenderDrawPoint(rend, point_x, point_y);
			}
			temp--;
		}
}

void Circle::setPosX(){
	m_x += 10;
}