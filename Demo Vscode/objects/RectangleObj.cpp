#include "RectangleObj.h"

RectangleObj::RectangleObj(float x, float y, float w, float h, float isStatic, SDL_Color col) {

    m_position.first = x;
	m_position.second = y;
    m_rect.first = w;
    m_rect.second = h;
	m_static = isStatic;
    m_color = col;

    m_drawRect.x = m_position.first;
    m_drawRect.y = m_position.second;
    m_drawRect.w = m_rect.first;
    m_drawRect.h =  m_rect.second;
}

RectangleObj::~RectangleObj() {

}

void RectangleObj::update() {

}

void RectangleObj::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_drawRect);
}
