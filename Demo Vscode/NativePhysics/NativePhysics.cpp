#include "NativePhysics.h"

/*
*   B O U N D S
*   C H E C K E R S
*/

bool NativePhysics::checkLeftBound(float x, float r) {
    if ((x + r) < 0) {
        return true;
    }
    else{
        return false;
    }
}
bool NativePhysics::checkRightBound(float x, float r) {
    if ((x - r) > m_windowWidth) {
        return true;
    }
    else{
        return false;
    }
}
bool NativePhysics::checkTopBound(float y, float r) {
    if ((y + r) < 0) {
        return true;
    }
    else{
        return false;
    }
}
bool NativePhysics::checkBottomBound(float y, float r) {
    if ((y - r) > m_windowHeight) {
        return true;
    }
    else{
        return false;
    }
}

float NativePhysics::leftBoundRes(float r) {
    return m_windowWidth + r;
}
float NativePhysics::rightBoundRes(float r) {
    return -r;
}
float NativePhysics::topBoundRes(float r) {
    return m_windowHeight + r;
}
float NativePhysics::bottomBoundRes(float r) {
    return -r;
}

float NativePhysics::restitution(float x) {
    return (x * 0.8);
}
/*
*   CIRCLE - CIRCLE COLLISION
*/

bool NativePhysics::circleCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2){
    if(getDist(x1, y1, x2, y2) <= (r1 + r2)) {
        return true;
    }
    else {
        return false;
    }
}

float NativePhysics::circlePushBackX(float x1, float r1, float x2, float r2) {
    float xPoint = collisionPointX(x1, r1, x2, r2);
    float temp = (x1 - xPoint) / 16;
    return temp;
}

float NativePhysics::circlePushBackY(float y1, float r1, float y2, float r2) {
    float yPoint = collisionPointX(y1, r1, y2, r2);
    float temp = (y1 - yPoint) / 16;
    return temp;
}

float NativePhysics::circleVelX1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float dp = dpTan1(x1, y1, vx1, vy1, x2, y2);
    float mass = mass1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2);
    float temp = (tx1 * dp) + (nx1 * mass);
    return temp;
}

float NativePhysics::circleVelY1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float ny1 = ny(x1, y1, x2, y2);
    float ty1 = ty(ny1);
    float dp = dpTan1(x1, y1, vx1, vy1, x2, y2);
    float mass = mass1(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2);
    float temp = (ty1 * dp) + (ny1 * mass);
    return temp;
}

float NativePhysics::circleVelX2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float dp = dpTan2(x1, y1, x2, y2, vx2, vy2);
    float mass = mass2(x1, y1, vx1, vy1, m1, x2, y2, vx2, vy2, m2);
    float temp = (tx1 * dp) + (nx1 * mass);
    return temp;
}

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


bool NativePhysics::circleRectCollision(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {
    float comp = sqrt(((circleRectCompX(x1, x2, w2) - x1) * (circleRectCompX(x1, x2, w2) - x1)) + ((circleRectCompY(y1, y2, h2) - y1) * (circleRectCompY(y1, y2, h2) - y1)));
    if(comp < r1) {
        return true;
    }
    else {
        return false;
    }
 }

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

float NativePhysics::pushBackPosY(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {
    float compX = circleRectCompX(x1, x2, w2);
    float compY = circleRectCompY(y1, y2, h2);
    float angle = penAngle(x1, y1, compX, compY);
    float dist = penDist(r1, getDist(compX, compY, x1, y1));
    float edgeY = getEdgeY(compY, r1, angle);
    float penVec = getPenVecY(edgeY, dist, angle);
    
    return (penVec - edgeY);
}

float NativePhysics::topPushBackPosY(float x1, float y1, float r1, float x2, float y2, float w2, float h2) {
    float compX = circleRectCompX(x1, x2, w2);
    float compY = circleRectCompY(y1, y2, h2);
    float angle = topPenAngle(x1, y1, compX, compY);
    float dist = penDist(r1, getDist(compX, compY, x1, y1));
    float edgeY = getEdgeY(compY, r1, angle);
    float penVec = getPenVecY(edgeY, dist, angle);

    return (penVec - edgeY);
}

float NativePhysics::circleRectResX(float x) {
    float temp = restitution(x) * (-1);
    return temp;
}

float NativePhysics::circleRectResY(float y) {
    float temp = restitution(y) * (-1);
    return temp;
}


/*
*   P R I V A T E
*   V A R I A B L E S
*/

float NativePhysics::applyForce(float x, float y) {
    return (x + y);
}

float NativePhysics::getDist(float x1, float y1, float x2, float y2) {
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

float NativePhysics::getEdgeX(float x1, float r1, float angle) {
    float edgeX = (x1 + r1) * cos(angle);
    return edgeX;
}

float NativePhysics::getEdgeY(float y1, float r1, float angle) {
    float edgeY = (y1 + r1) * sin(angle);
    return edgeY;
}

float NativePhysics::getPenVecX(float x1, float d1, float angle) {
    float penX = (x1 + d1) * cos(angle);
    return penX;
}

float NativePhysics::getPenVecY(float y1, float d1, float angle) {
    float penY = (y1 + d1) * sin(angle);
    return penY;
}

float NativePhysics::penAngle(float x1, float y1, float x2, float y2) {
    float angle = atan2((y2 - y1), (x1 - x2));
    return angle;
}

float NativePhysics::topPenAngle(float x1, float y1, float x2, float y2) {
    float angle = atan2((y1 - y2), (x1 - x2));
    return angle;
}

float NativePhysics::penDist(float r1, float d1) {
    float pen = r1 - d1;
    return pen;
}

float NativePhysics::tangentX(float y1, float y2) {
    return (y2 - y1);
}

float NativePhysics::tangentY(float x1, float x2) {
    return (x2 - x1) * (-1);
}

float NativePhysics::dotProd(float x1, float y1, float x2, float y2) {
    float xMag = getMag(x1, y1);
    float yMag = getMag(x2, y2);
    float angle = penAngle(x1, y1, x2, y2);
    return xMag * yMag * angle;
}

float NativePhysics::normaliseVec(float x, float mag) {
    float norm = x / mag;
    return norm;
}

float NativePhysics::getMag(float x, float y) {
    float mag = sqrt((x * x) + (y * y));
    return mag;
}

float NativePhysics::nx(float x1, float y1, float x2, float y2) {
    float tempX = x2 - x1;
    float dist = getDist(x1, y1, x2, y2);
    return tempX / dist;
}

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

float NativePhysics::dpTan1(float x1, float y1, float vx1, float vy1, float x2, float y2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float ty1 = ty(nx1);
    float tempX = vx1 * tx1;
    float tempY = vy1 * ty1;
    return tempX + tempY;
}

float NativePhysics::dpTan2(float x1, float y1, float x2, float y2, float vx2, float vy2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tx1 = tx(ny1);
    float ty1 = ty(nx1);
    float tempX = vx2 * tx1;
    float tempY = vy2 * ty1;
    return tempX + tempY;
}

float NativePhysics::dpNorm1(float x1, float y1, float vx1, float vy1, float x2, float y2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tempX = vx1 * nx1;
    float tempY = vy1 * ny1;
    return tempX + tempY;
}

float NativePhysics::dpNorm2(float x1, float y1, float x2, float y2, float vx2, float vy2) {
    float ny1 = ny(x1, y1, x2, y2);
    float nx1 = nx(x1, y1, x2, y2);
    float tempX = vx2 * nx1;
    float tempY = vy2 * ny1;
    return tempX + tempY;
}

float NativePhysics::mass1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float norm1 = dpNorm1(x1, y1, vx1, vy1, x2, y2);
    float norm2 = dpNorm2(x1, y1, x2, y2, vx2, vy2);
    float temp = (norm1 * (m1 - m2) + 2.0 * m2 * norm2) / (m1 + m2);
    return temp;
}

float NativePhysics::mass2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2) {
    float norm1 = dpNorm1(x1, y1, vx1, vy1, x2, y2);
    float norm2 = dpNorm2(x1, y1, x2, y2, vx2, vy2);
    float temp = (norm2 * (m2 - m1) + 2.0 * m1 * norm1) / (m1 + m2);
    return temp;
}

float NativePhysics::collisionPointX(float x1, float r1, float x2, float r2) {
    float temp = (((x1 * r2) + (x2 * r1)) / (r1 + r2));
    return temp;
}
float NativePhysics::collisionPointY(float y1, float r1, float y2, float r2) {
    float temp = (((y1 * r2) + (y2 * r1)) / (r1 + r2)) ;
    return temp;
}