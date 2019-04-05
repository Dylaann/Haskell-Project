#include "NativePhysics.h"

float NativePhysics::applyForce(float x) {
    float y = x + y;
    return y;
}

/*
*   B O U N D S
*   C H E C K E R S
*/

bool NativePhysics::CheckLeftBounds(float x, float r) {
    if ((x + r) < 0) {
        return true;
    }
    else{
        return false;
    }
}
bool NativePhysics::CheckRightBounds(float x, float r) {
    if ((x - r) > m_windowWidth) {
        return true;
    }
    else{
        return false;
    }
}
bool NativePhysics::CheckTopBounds(float y, float r) {
    if ((y + r) < 0) {
        return true;
    }
    else{
        return false;
    }
}
bool NativePhysics::CheckBottomBounds(float y, float r) {
    if ((y - r) > m_windowHeight) {
        return true;
    }
    else{
        return false;
    }
}

float NativePhysics::LeftBoundRes(float r) {
    return m_windowWidth + r;
}
float NativePhysics::RightBoundRes(float r) {
    return -r;
}
float NativePhysics::TopBoundRes(float r) {
    return m_windowHeight + r;
}
float NativePhysics::BottomBoundRes(float r) {
    return -r;
}

/*
*   CIRCLE - CIRCLE COLLISION
*/

bool NativePhysics::CircleCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2){
    if(getDist(x1, y1, x2, y2) <= (r1 + r2)) {
        return true;
    }
    else {
        return false;
    }
}



/*
*   CIRCLE - RECTANGLE COLLISION
*/


bool NativePhysics::CircleRectCollision() {
    return true;
}




/*
*   P R I V A T E
*   V A R I A B L E S
*/

float NativePhysics::getDist(float x1, float y1, float x2, float y2) {
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
