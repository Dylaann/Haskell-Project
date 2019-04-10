#ifndef NATIVEPHYSICS
#define NATIVEPHYSICS

#include <math.h>
#include <stdlib.h>
#include <iostream>

//Class Physics Class.
class NativePhysics {
public:
    // Add two forces together
    float applyForce(float x, float y);

    // Check for Circle-Circle collision & Rect-Circle Collision
    bool circleCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2);
    bool circleRectCollision(float x1, float y1, float r1, float x2, float y2, float w2, float h2);

    // Get push back distance from Circle-Rect collision
    float pushBackPosX(float x1, float y1, float r1, float x2, float y2, float w2, float h2);
    float pushBackPosY(float x1, float y1, float r1, float x2, float y2, float w2, float h2);
    float topPushBackPosY(float x1, float y1, float r1, float x2, float y2, float w2, float h2);

    // Resultant of velocity after collision
    float circleRectResX(float x);
    float circleRectResY(float y);

    // Check if object is out of bounds
    bool checkLeftBound(float x, float r);
    bool checkRightBound(float x, float r);
    bool checkTopBound(float y, float r);
    bool checkBottomBound(float y, float r);

    // Reset object if it's out of bounds
    float leftBoundRes(float r);
    float rightBoundRes(float r);
    float topBoundRes(float r);
    float bottomBoundRes(float r);

    // Get Resultant Velocity of two circles colliding
    float circleVelX1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2);
    float circleVelY1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2);
    float circleVelX2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2);
    float circleVelY2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2);

    // Restitution 
    float restitution(float x);

    // Get push back distance of two circles colliding
    float circlePushBackX(float x1, float r1, float x2, float r2);
    float circlePushBackY(float y1, float r1, float y2, float r2);

private:
    // Private Member Variables.
    float getDist(float x1, float y1, float x2, float y2);
    float nx(float x1, float y1, float x2, float y2);
    float ny(float x1, float y1, float x2, float y2);
    float tx(float ny1);
    float ty(float nx1);

    // Penetration Tangent and Normal
    float dpTan1(float x1, float y1, float vx1, float vy1, float x2, float y2);
    float dpTan2(float x1, float y1, float x2, float y2, float vx2, float vy2);
    float dpNorm1(float x1, float y1, float vx1, float vy1, float x2, float y2);
    float dpNorm2(float x1, float y1, float x2, float y2, float vx2, float vy2);

    // Comp masses of each object for velocity after collisions.
    float mass1(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2);
    float mass2(float x1, float y1, float vx1, float vy1, float m1, float x2, float y2, float vx2, float vy2, float m2);
    
    // Tangent Vector
    float tangentX(float y1, float y2);
    float tangentY(float x1, float x2);

    // Dot product, Normalisation and Magnitude functions
    float dotProd(float x1, float y1, float x2, float y2);
    float normaliseVec(float x, float mag);
    float getMag(float x, float y);

    // Collision point
    float collisionPointX(float x1, float r1, float x2, float r2);
    float collisionPointY(float y1, float r1, float y2, float r2);

    // Get edge collision (Circle-Rect)
    float getEdgeX(float x1, float r1, float angle);
    float getEdgeY(float y1, float r1, float angle);

    // Get penetration vector, distance and angle
    float getPenVecX(float x1, float d1, float angle);
    float getPenVecY(float y1, float d1, float angle);
    float penAngle(float x1, float y1, float x2, float y2);
    float topPenAngle(float x1, float y1, float x2, float y2);
    float penDist(float r1, float d1);

    // Determine where the rectangle is hit
    float circleRectCompX(float x1, float x2, float w2);
    float circleRectCompY(float y1, float y2, float h2);

    // Window width and height
    float m_windowWidth = 1280;
    float m_windowHeight = 720;
};
#endif // !NativePhysics