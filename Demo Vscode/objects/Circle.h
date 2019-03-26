#ifndef CIRCLE
#define CIRCLE

#include <SDL.h>
#include <SDL_stdinc.h>
#include <stdlib.h>
#include <iostream>

//Class to make a Circle Object.
class Circle {
public:
    //Constructor / Destructor.
	Circle(int id, float x, float y, bool isStatic, int radius, SDL_Color col);
	~Circle();

    //Update & Render functions.
    void update();
    void render(SDL_Renderer* renderer);


    //Gets & Sets.
    void setPosX(float x);
    void setPosY(float y);
    void setVel(std::pair<float, float> vel);
    void setPos(std::pair<float, float> pos);
    float getPosX(){ return m_position.first; };
    float getPosY(){ return m_position.second; };
    float getRadius(){ return m_radius; };
    float getMass(){ return m_mass; };
    std::pair<float, float> getPos(){ return m_position; };
    std::pair<float, float> getVel(){ return m_velocity; };
    bool getStatic(){ return m_static; };
    void setStatic(bool stat) { m_static = stat; }

    int m_id = 0;

private:
    //Private Member Variables.
    SDL_Color m_color;
    std::pair<float, float> m_position;
    std::pair<float, float> m_velocity;
    int m_radius;
    bool m_static;
    float m_maxVel = 20;
    float m_mass = 10;
};
#endif // !Circle   