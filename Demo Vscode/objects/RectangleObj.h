#ifndef RECTANGLEOBJ
#define RECTANGLEOBJ

#include <SDL.h>
#include <iostream>

class RectangleObj {
public:
    RectangleObj(float x, float y, float w, float h, float isStatic, SDL_Color col);
    ~RectangleObj();

    void update();
    void render(SDL_Renderer* renderer);

    std::pair<float, float> getPos(){ return m_position; }
    std::pair<float, float> getRect(){ return m_rect; }

private:
    std::pair<float, float> m_position;
    std::pair<float, float> m_rect;
    std::pair<float, float> m_velocity;
    bool m_static;
    SDL_Color m_color;

    SDL_Rect m_drawRect;
};
#endif