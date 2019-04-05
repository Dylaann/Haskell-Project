#ifndef NATIVEPHYSICS
#define NATIVEPHYSICS

#include <math.h>
#include <stdlib.h>
#include <iostream>

//Class Physics Class.
class NativePhysics {
public:
    float applyForce(float x);

    bool CircleCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2);
    bool CircleRectCollision();

    float PushBackPosX();
    float PushBackPosY();

    float CircleRectResX();
    float CircleRectResY();

    bool CheckLeftBounds(float x, float r);
    bool CheckRightBounds(float x, float r);
    bool CheckTopBounds(float y, float r);
    bool CheckBottomBounds(float y, float r);

    float LeftBoundRes(float r);
    float RightBoundRes(float r);
    float TopBoundRes(float r);
    float BottomBoundRes(float r);

    float CircleCircleResX();
    float CircleCircleResY();

    float CircleVelX1();
    float CircleVelY1();
    float CircleVelX2();
    float CircleVelY2();

    float GroundRestitution();

    float CirclePushBackX();
    float CirclePushBackY();

private:
    //Private Member Variables.
    float getDist(float x1, float y1, float x2, float y2);
    float nx();
    float ny();
    float tx();
    float ty();
    float dpTan1();
    float dpTan2();
    float dpNorm1();
    float dpNorm2();
    float mass1();
    float mass2();
    float tangentX();
    float tangentY();
    float dotProd();
    float normaliseVec();
    float getMag();
    float collisionPointX();
    float collisionPointY();
    float getEdgeX();
    float getEdgeY();
    float getPenVecX();
    float getPenVecY();
    float penAngle();
    float penDist();
    float circleRectCompX();
    float circleRectCompY();

    float m_windowWidth = 1280;
    float m_windowHeight = 720;
};
#endif // !NativePhysics