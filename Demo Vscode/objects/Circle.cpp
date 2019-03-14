#include "Circle.h"

// Circle Constructor function implementation
Circle::Circle(float x, float y, bool isStatic, int radius, SDL_Color col) {
	m_position.first = x;
	m_position.second = y;
	m_static = isStatic;
	m_radius = radius;
	m_color = col;
	m_velocity = { 0.0f, 0.0f };
}

// Deconstructor
Circle::~Circle() {

}

// Update Implementation
void Circle::update() {

}

// Render a circle
void Circle::render(SDL_Renderer* rend) {
    
    SDL_SetRenderDrawColor(rend, m_color.r, m_color.g, m_color.b, m_color.a);

		int point_x = 0;
		int point_y = 0;
		int temp = m_radius;

		while (temp > 0)
		{
			for (int t = 0; t < 360; t++)
			{
				point_x = m_position.first + (m_radius * SDL_cos(t));
				point_y = 	m_position.second + (m_radius * SDL_sin(t));
				SDL_RenderDrawPoint(rend, point_x, point_y);
			}
			temp--;
		}
}

// Set X position
void Circle::setPosX(float x){
	m_position.first = x;
}

// Set Y position
void Circle::setPosY(float y){
	m_position.second = y;
}

// Set X velocity
void Circle::setVel(std::pair<float, float> vel){
	if(vel.first < m_maxVel) {
		m_velocity.first = vel.first;
	}
	else {
		m_velocity.first = m_maxVel;
	}

	if(vel.second < m_maxVel) {
	m_velocity.second = vel.second;
	}
	else {
			m_velocity.second = m_maxVel;
	}

}

// Set X position
void Circle::setPos(std::pair<float, float> pos){
	m_position = pos;
}