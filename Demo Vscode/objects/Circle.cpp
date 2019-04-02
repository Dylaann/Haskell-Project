#include "Circle.h"

// Circle Constructor function implementation
Circle::Circle(int id, float x, float y, bool isStatic, int radius, SDL_Color col, SDL_Texture * texture) {
	m_position.first = x;
	m_position.second = y;
	m_static = isStatic;
	m_radius = radius;
	m_color = col;
	m_velocity = { 0.0f, 0.0f };
	m_id = id;
	m_texture = texture;

	m_drawRect.x = x - radius;
	m_drawRect.y = y - radius;
	m_drawRect.w = radius * 2;
	m_drawRect.h = radius * 2;

}

// Deconstructor
Circle::~Circle() {

}

// Update Implementation
void Circle::update() {
		m_drawRect.x = m_position.first - m_radius;
		m_drawRect.y = m_position.second - m_radius;
}

// Render a circle
void Circle::render(SDL_Renderer* rend) {

		SDL_RenderCopy(rend, m_texture, NULL, &m_drawRect);
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

	if(vel.first < m_maxVel && vel.first > -m_maxVel) {
		m_velocity.first = vel.first;
	}
	else if (m_velocity.first < -m_maxVel) {
			m_velocity.first = -m_maxVel;
	}
	else if (m_velocity.first > m_maxVel) {
			m_velocity.first = m_maxVel;
	}

	if(vel.second < m_maxVel && vel.second > -m_maxVel) {
		m_velocity.second = vel.second;
	}
	else if (m_velocity.second < -m_maxVel) {
			m_velocity.second = -m_maxVel;
	}
	else if (m_velocity.second > m_maxVel) {
			m_velocity.second = m_maxVel;
	}

	if (m_velocity.first < 0.23 && m_velocity.first > -0.23) {
		m_velocity.first = 0;
	}

	if (m_velocity.second < 0.23 && m_velocity.second > -0.23) {
		m_velocity.second = 0;
	}
}

// Set X position
void Circle::setPos(std::pair<float, float> pos){
	m_position = pos;
}