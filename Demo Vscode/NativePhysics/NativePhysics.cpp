#include "NativePhysics.h"

/*
*   B O U N D S
*   C H E C K E R S
*/

/* 
* @param{float} x -> x position
* @param{float} r -> radius of objects
* @return bool if object has gone off to the left
*/
bool NativePhysics::checkLeftBound(float x, float r) {
    if ((x + r) < 0) {
        return true;
    }
    else{
        return false;
    }
}

/* 
* @param{float} x -> x position
* @param{float} r -> radius of objects
* @return bool if object has gone off to the right
*/
bool NativePhysics::checkRightBound(float x, float r) {
    if ((x - r) > m_windowWidth) {
        return true;
    }
    else{
        return false;
    }
}

/* 
* @param{float} y -> y position
* @param{float} r -> radius of objects
* @return bool if object has gone off the top of the screen
*/
bool NativePhysics::checkTopBound(float y, float r) {
    if ((y + r) < 0) {
        return true;
    }
    else{
        return false;
    }
}

/* 
* @param{float} y -> y position
* @param{float} r -> radius of objects
* @return{bool} if object has gone off the bottom of the screen
*/
bool NativePhysics::checkBottomBound(float y, float r) {
    if ((y - r) > m_windowHeight) {
        return true;
    }
    else{
        return false;
    }
}

/* 
* @param{float} r -> radius
* @return{float} window width + radius
*/
float NativePhysics::leftBoundRes(float r) {
    return m_windowWidth + r;
}

/* 
* @param{float} r -> radius
* @return{float} -radius
*/
float NativePhysics::rightBoundRes(float r) {
    return -r;
}

/* 
* @param{float} r -> radius
* @return{float} window Height + radius
*/
float NativePhysics::topBoundRes(float r) {
    return m_windowHeight + r;
}
/* 
* @param{float} r -> radius
* @return{float} -radius
*/
float NativePhysics::bottomBoundRes(float r) {
    return -r;
}

/* 
* @param{float} x -> velocity
* @return{float} new velocity after collisions
*/
float NativePhysics::restitution(float x) {
    return (x * 0.8);
}
/*
*   CIRCLE - CIRCLE COLLISION
*/

/* 
* @param{float} x1 -> x position of first Circle
* @param{float} y1 -> y position of first Circle
* @param{float} r1 -> radius of first Circle
* @param{float} x2 -> x position of second Circle
* @param{float} y2 -> y position of second Circle
* @param{float} r1 -> radius of second Circle
* @return{bool} return if collision is true
*/
bool NativePhysics::circleCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2){
    if(getDist(x1, y1, x2, y2) <= (r1 + r2)) {
        return true;
    }
    else {
        return false;
    }
}

/* 
* @param{float} x1 -> x position of first Circle
* @param{float} r1 -> radius of first Circle
* @param{float} x2 -> x position of second Circle
* @param{float} r1 -> radius of second Circle
* @return{float} return push back distance
*/
float NativePhysics::circlePushBackX(float x1, float r1, float x2, float r2) {
    float xPoint = collisionPointX(x1, r1, x2, r2);
    float temp = (x1 - xPoint) / 16;
    return temp;
}

/* 
* @param{float} y1 -> y position of first Circle
* @param{float} r1 -> radius of first Circle
* @param{float} y2 -> y position of second Circle
* @param{float} r1 -> radius of second Circle
* @return{float} return push back distance
*/
float NativePhysics::circlePushBackY(float y1, float r1, float y2, float r2) {
    float yPoint = collisionPointX(y1, r1, y2, r2);
    float temp = (y1 - yPoint) / 16;
    return temp;
}

/* 
* @param{float} x1 -> x position of first Circle
* @param{float} y1 -> y position of first Circle
* @param{float} vx1 -> x velocity of first Circle
* @param{float} vy1 -> y velocity of first Circle
* @param{float} m1 -> y mass of first Circle
* @param{float} x2 -> x position of second Circle
* @param{float} y2 -> y position of second Circle
* @param{float} vx2 -> x velocity of second Circle
* @param{float} vy2 -> y velocity of second Circle
* @param{float} m1 -> y mass of second Circle
* @return{float} return new x velocity
*/
float NativePhysics::circleVelX1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float dp = dpTan1(x1, y1, vx1, vy1, x2, y2);
    float mass = mass1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2);
    float temp = (tx1 * dp) + (nx1 * mass);
    return temp;
}

/* 
* @param{float} x1 -> x position of first Circle
* @param{float} y1 -> y position of first Circle
* @param{float} vx1 -> x velocity of first Circle
* @param{float} vy1 -> y velocity of first Circle
* @param{float} m1 -> y mass of first Circle
* @param{float} x2 -> x position of second Circle
* @param{float} y2 -> y position of second Circle
* @param{float} vx2 -> x velocity of second Circle
* @param{float} vy2 -> y velocity of second Circle
* @param{float} m1 -> y mass of second Circle
* @return{float} return new y velocity
*/
float NativePhysics::circleVelY1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float ny1 = ny(x1, y1, x2, y2);
    float ty1 = ty(ny1);
    float dp = dpTan1(x1, y1, vx1, vy1, x2, y2);
    float mass = mass1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2);
    float temp = (ty1 * dp) + (ny1 * mass);
    return temp;
}

/* 
* @param{float} x1 -> x position of first Circle
* @param{float} y1 -> y position of first Circle
* @param{float} vx1 -> x velocity of first Circle
* @param{float} vy1 -> y velocity of first Circle
* @param{float} m1 -> y mass of first Circle
* @param{float} x2 -> x position of second Circle
* @param{float} y2 -> y position of second Circle
* @param{float} vx2 -> x velocity of second Circle
* @param{float} vy2 -> y velocity of second Circle
* @param{float} m1 -> y mass of second Circle
* @return{float} return new x velocity
*/
float NativePhysics::circleVelX2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float dp = dpTan2(x1, y1, x2, y2, vx2, vy2);
    float mass = mass2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2);
    float temp = (tx1 * dp) + (nx1 * mass);
    return temp;
}

/* 
* @param{float} x1 -> x position of first Circle
* @param{float} y1 -> y position of first Circle
* @param{float} vx1 -> x velocity of first Circle
* @param{float} vy1 -> y velocity of first Circle
* @param{float} m1 -> y mass of first Circle
* @param{float} x2 -> x position of second Circle
* @param{float} y2 -> y position of second Circle
* @param{float} vx2 -> x velocity of second Circle
* @param{float} vy2 -> y velocity of second Circle
* @param{float} m1 -> y mass of second Circle
* @return{float} return new y velocity
*/
float NativePhysics::circleVelY2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float ny1 = ny(x1, y1, x2, y2);
    float ty1 = ty(ny1);
    float dp = dpTan2(x1, y1, x2, y2, vx2, vy2);
    float mass = mass2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2);
    float temp = (ty1 * dp) + (ny1 * mass);
    return temp;
}


/*
*   CIRCLE - RECTANGLE COLLISION
*/

/* 
* @param{float} x1 -> x position of Circle
* @param{float} y1 -> y position of Circle
* @param{float} r1 -> r1 Circle
* @param{float} x2 -> x position of Rect
* @param{float} y2 -> y position of Rect
* @param{float} w2 -> width of Rect
* @param{float} h2 -> height of Rect
* @return{bool} return if collision is true
*/
bool NativePhysics::circleRectCollision(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {
    float comp = sqrt(((circleRectCompX(x1, x2, w2) - x1) * (circleRectCompX(x1, x2, w2) - x1)) + ((circleRectCompY(y1, y2, h2) - y1) * (circleRectCompY(y1, y2, h2) - y1)));
    if(comp < r1) {
        return true;
    }
    else {
        return false;
    }
}

/* 
* @param{float} x1 -> x position of Circle
* @param{float} x2 -> x position of Rect
* @param{float} w2 -> width of Rect
* @return{float} return x co-ord of collision
*/
float NativePhysics::circleRectCompX(float x1, float x2, float w2) {
    if (x1 < x2){
        return x2;
    }
    else if(x1 > x2 + w2) {
        return (x2 + w2);
    }
    else {
        return x1;
    }
}

/* 
* @param{float} y1 -> y position of Circle
* @param{float} y2 -> y position of Rect
* @param{float} h2 -> height of Rect
* @return{float} return y co-ord of collision
*/
float NativePhysics::circleRectCompY(float y1, float y2, float h2) {
    if (y1 < y2){
        return y2;
    }
    else if(y1 > y2 + h2) {
        return (y2 + h2);
    }
    else {
        return y1;
    }
}

/* 
* @param{float} x1 -> x position of Circle
* @param{float} y1 -> y position of Circle
* @param{float} r1 -> r1 Circle
* @param{float} x2 -> x position of Rect
* @param{float} y2 -> y position of Rect
* @param{float} w2 -> width of Rect
* @param{float} h2 -> height of Rect
* @return{float} return push back distance
*/
float NativePhysics::pushBackPosX(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {
    float compX = circleRectCompX(x1, x2, w2);
    float compY = circleRectCompY(y1, y2, h2);
    float angle = penAngle(x1, y1, compX, compY);
    float dist = penDist(r1, getDist(compX, compY, x1, y1));
    float edgeX = getEdgeX(compX, r1, angle);
    float penVec = getPenVecX(edgeX, dist, angle);
    
    if (edgeX > 0) {
    return (penVec - edgeX);
    }
    else {
        return (edgeX + penVec);
    }
}

/* 
* @param{float} x1 -> x position of Circle
* @param{float} y1 -> y position of Circle
* @param{float} r1 -> r1 Circle
* @param{float} x2 -> x position of Rect
* @param{float} y2 -> y position of Rect
* @param{float} w2 -> width of Rect
* @param{float} h2 -> height of Rect
* @return{float} return push back distance
*/
float NativePhysics::pushBackPosY(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {
    float compX = circleRectCompX(x1, x2, w2);
    float compY = circleRectCompY(y1, y2, h2);
    float angle = penAngle(x1, y1, compX, compY);
    float dist = penDist(r1, getDist(compX, compY, x1, y1));
    float edgeY = getEdgeY(compY, r1, angle);
    float penVec = getPenVecY(edgeY, dist, angle);
    
    return (penVec - edgeY);
}

/* 
* @param{float} x1 -> x position of Circle
* @param{float} y1 -> y position of Circle
* @param{float} r1 -> r1 Circle
* @param{float} x2 -> x position of Rect
* @param{float} y2 -> y position of Rect
* @param{float} w2 -> width of Rect
* @param{float} h2 -> height of Rect
* @return{float} return push back distance
*/
float NativePhysics::topPushBackPosY(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {
    float compX = circleRectCompX(x1, x2, w2);
    float compY = circleRectCompY(y1, y2, h2);
    float angle = topPenAngle(x1, y1, compX, compY);
    float dist = penDist(r1, getDist(compX, compY, x1, y1));
    float edgeY = getEdgeY(compY, r1, angle);
    float penVec = getPenVecY(edgeY, dist, angle);

    return (penVec - edgeY);
}

/* 
* @param{float} x -> x velocity of Circle
* @return{float} new x velocity
*/
float NativePhysics::circleRectResX(float x) {
    float temp = restitution(x) * (-1);
    return temp;
}

/* 
* @param{float} y -> y velocity of Circle
* @return{float} new y velocity
*/
float NativePhysics::circleRectResY(float y) {
    float temp = restitution(y) * (-1);
    return temp;
}


/*
*   P R I V A T E
*   V A R I A B L E S
*/

/* 
* @param{float} x -> x 
* @param{float} y -> y
* @return{float} addition of forces
*/
float NativePhysics::applyForce(float x, float y) {
    return (x + y);
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} distance between two points
*/
float NativePhysics::getDist(float x1, float y1, float x2, float y2) {
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

/* 
* @param{float} x1 -> x pos
* @param{float} r1 -> radius
* @param{float} angle -> angle 
* @return{float} edgeX
*/
float NativePhysics::getEdgeX(float x1, float r1, float angle) {
    float edgeX = (x1 + r1) * cos(angle);
    return edgeX;
}

/* 
* @param{float} y1 -> y pos
* @param{float} r1 -> radius
* @param{float} angle -> angle 
* @return{float} edgeY
*/
float NativePhysics::getEdgeY(float y1, float r1, float angle) {
    float edgeY = (y1 + r1) * sin(angle);
    return edgeY;
}

/* 
* @param{float} x1 -> x pos
* @param{float} d1 -> distance
* @param{float} angle -> angle 
* @return{float} Penetration pos x
*/
float NativePhysics::getPenVecX(float x1, float d1, float angle) {
    float penX = (x1 + d1) * cos(angle);
    return penX;
}

/* 
* @param{float} y1 -> y pos
* @param{float} d1 -> distance
* @param{float} angle -> angle 
* @return{float} Penetration pos y
*/
float NativePhysics::getPenVecY(float y1, float d1, float angle) {
    float penY = (y1 + d1) * sin(angle);
    return penY;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} Penetration angle
*/
float NativePhysics::penAngle(float x1, float y1, float x2, float y2) {
    float angle = atan2((y2 - y1), (x1 - x2));
    return angle;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} Penetration angle
*/
float NativePhysics::topPenAngle(float x1, float y1, float x2, float y2) {
    float angle = atan2((y1 - y2), (x1 - x2));
    return angle;
}

/* 
* @param{float} r1 -> radius
* @param{float} d1 -> distance
* @return{float} Penetration distance
*/
float NativePhysics::penDist(float r1, float d1) {
    float pen = r1 - d1;
    return pen;
}

/* 
* @param{float} y1 -> y pos
* @param{float} y2 -> y pos
* @return{float} X tangent
*/
float NativePhysics::tangentX(float y1, float y2) {
    return (y2 - y1);
}

/* 
* @param{float} x1 -> x pos
* @param{float} x2 -> x pos
* @return{float} Y tangent
*/
float NativePhysics::tangentY(float x1, float x2) {
    return (x2 - x1) * (-1);
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} dot product
*/
float NativePhysics::dotProd(float x1, float y1, float x2, float y2) {
    float xMag = getMag(x1, y1);
    float yMag = getMag(x2, y2);
    float angle = penAngle(x1, y1, x2, y2);
    return xMag * yMag * angle;
}

/* 
* @param{float} x -> x pos
* @param{float} mag -> magnitude of vector
* @return{float} Normalise vector
*/
float NativePhysics::normaliseVec(float x, float mag) {
    float norm = x / mag;
    return norm;
}

/* 
* @param{float} x -> x pos
* @param{float} y -> y pos
* @return{float} Magnitude of vector
*/
float NativePhysics::getMag(float x, float y) {
    float mag = sqrt((x * x) + (y * y));
    return mag;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} nx
*/
float NativePhysics::nx(float x1, float y1, float x2, float y2) {
    float tempX = x2 - x1;
    float dist = getDist(x1, y1, x2, y2);
    return tempX / dist;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} ny
*/
float NativePhysics::ny(float x1, float y1, float x2, float y2) {
    float tempY = y2 - y1;
    float dist = getDist(x1, y1, x2, y2);
    return tempY / dist;
}
float NativePhysics::tx(float ny1) {
    return ny1 * (-1);
}
float NativePhysics::ty(float nx1) {
    return nx1;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} vx1 -> x velocity
* @param{float} vy1 -> y velocity
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} pen tangent 1
*/
float NativePhysics::dpTan1(float x1, float y1, float vx1, float vy1, float x2, float y2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float ty1 = ty(nx1);
    float tempX = vx1 * tx1;
    float tempY = vy1 * ty1;
    return tempX + tempY;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @param{float} vx2 -> x velocity
* @param{float} vy2 -> y velocity
* @return{float} pen tangent 2
*/
float NativePhysics::dpTan2(float x1, float y1, float x2, float y2, float vx2, float vy2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float ty1 = ty(nx1);
    float tempX = vx2 * tx1;
    float tempY = vy2 * ty1;
    return tempX + tempY;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} vx1 -> x velocity
* @param{float} vy1 -> y velocity
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @return{float} pen Normal 1
*/
float NativePhysics::dpNorm1(float x1, float y1, float vx1, float vy1, float x2, float y2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tempX = vx1 * nx1;
    float tempY = vy1 * ny1;
    return tempX + tempY;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @param{float} vx2 -> x velocity
* @param{float} vy2 -> y velocity
* @return{float} pen Normal 2
*/
float NativePhysics::dpNorm2(float x1, float y1, float x2, float y2, float vx2, float vy2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tempX = vx2 * nx1;
    float tempY = vy2 * ny1;
    return tempX + tempY;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} vx1 -> x velocity
* @param{float} vy1 -> y velocity
* @param{float} m1 -> mass
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @param{float} vx2 -> x velocity
* @param{float} vy2 -> y velocity
* @param{float} m2 -> mass
* @return{float} mass resultant of two objects
*/
float NativePhysics::mass1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float norm1 = dpNorm1(x1, y1, vx1, vy1, x2, y2);
    float norm2 = dpNorm2(x1, y1, x2, y2, vx2, vy2);
    float temp = (norm1 * (m1 - m2) + 2.0 * m2 * norm2) / (m1 + m2);
    return temp;
}

/* 
* @param{float} x1 -> x pos
* @param{float} y1 -> y pos
* @param{float} vx1 -> x velocity
* @param{float} vy1 -> y velocity
* @param{float} m1 -> mass
* @param{float} x2 -> x pos
* @param{float} y2 -> y pos
* @param{float} vx2 -> x velocity
* @param{float} vy2 -> y velocity
* @param{float} m2 -> mass
* @return{float} mass resultant of two objects
*/
float NativePhysics::mass2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float norm1 = dpNorm1(x1, y1, vx1, vy1, x2, y2);
    float norm2 = dpNorm2(x1, y1, x2, y2, vx2, vy2);
    float temp = (norm2 * (m2 - m1) + 2.0 * m1 * norm1) / (m1 + m2);
    return temp;
}

/* 
* @param{float} x1 -> x pos
* @param{float} r1 -> radius
* @param{float} x2 -> x pos
* @param{float} r2 -> radius
* @return{float} collision point X
*/
float NativePhysics::collisionPointX(float x1, float r1, float x2, float r2) {
    float temp = (((x1 * r2) + (x2 * r1)) / (r1 + r2));
    return temp;
}

/* 
* @param{float} y1 -> y pos
* @param{float} r1 -> radius
* @param{float} y2 -> y pos
* @param{float} r2 -> radius
* @return{float} collision point Y
*/
float NativePhysics::collisionPointY(float y1, float r1, float y2, float r2) {
    float temp = (((y1 * r2) + (y2 * r1)) / (r1 + r2)) ;
    return temp;
}