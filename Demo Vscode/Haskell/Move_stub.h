#include "HsFFI.h"
#ifdef __cplusplus
extern "C" {
#endif
extern HsFloat moveGravity(HsFloat a1);
extern HsFloat applyForce(HsFloat a1, HsFloat a2);
extern HsBool circleCircleCollision(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6);
extern HsBool circleRectCollision(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7);
extern HsFloat pushBackPosX(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7);
extern HsFloat pushBackPosY(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7);
extern HsFloat circleRectResY(HsFloat a1);
extern HsFloat circleRectResX(HsFloat a1);
extern HsBool checkLeftBound(HsFloat a1, HsFloat a2);
extern HsBool checkRightBound(HsFloat a1, HsFloat a2);
extern HsBool checkTopBound(HsFloat a1, HsFloat a2);
extern HsBool checkBottomBound(HsFloat a1, HsFloat a2);
extern HsFloat leftBoundRes(HsFloat a1);
extern HsFloat rightBoundRes(HsFloat a1);
extern HsFloat topBoundRes(HsFloat a1);
extern HsFloat bottomBoundRes(HsFloat a1);
extern HsFloat circleCircleResX(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6);
extern HsFloat circleCircleResY(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6);
extern HsFloat newVelX1(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8);
extern HsFloat newVelY1(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8);
extern HsFloat newVelX2(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8);
extern HsFloat newVelY2(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8);
extern HsFloat lastHopeX1(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8, HsFloat a9, HsFloat a10);
extern HsFloat lastHopeY1(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8, HsFloat a9, HsFloat a10);
extern HsFloat lastHopeX2(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8, HsFloat a9, HsFloat a10);
extern HsFloat lastHopeY2(HsFloat a1, HsFloat a2, HsFloat a3, HsFloat a4, HsFloat a5, HsFloat a6, HsFloat a7, HsFloat a8, HsFloat a9, HsFloat a10);
extern HsFloat groundRestitution(HsFloat a1);
#ifdef __cplusplus
}
#endif

