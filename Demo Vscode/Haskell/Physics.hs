module Physics where

foreign export ccall moveGravity :: Float -> Float
foreign export ccall applyForce :: Float -> Float -> Float
foreign export ccall groundRestitution :: Float -> Float

foreign export ccall circleRectCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Bool
foreign export ccall circleRectResY :: Float -> Float
foreign export ccall circleRectResX :: Float -> Float
foreign export ccall pushBackPosX :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall pushBackPosY :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall topPushBackPosY :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float

foreign export ccall checkLeftBound :: Float -> Float -> Bool
foreign export ccall checkRightBound :: Float -> Float -> Bool
foreign export ccall checkTopBound :: Float -> Float -> Bool
foreign export ccall checkBottomBound :: Float -> Float -> Bool
foreign export ccall leftBoundRes :: Float -> Float
foreign export ccall rightBoundRes :: Float -> Float
foreign export ccall topBoundRes :: Float -> Float
foreign export ccall bottomBoundRes :: Float -> Float

foreign export ccall circleCircleCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Bool
foreign export ccall circleVelX1 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall circleVelY1 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall circleVelX2 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall circleVelY2 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall circlePushBackX :: Float -> Float -> Float -> Float -> Float
foreign export ccall circlePushBackY :: Float -> Float -> Float -> Float -> Float

-- | act as gravity and move the y coordinate
moveGravity :: Float -> Float
moveGravity y = y + 0.298

-- | add two forces together
applyForce :: Float -> Float -> Float 
applyForce x y = x + y

-- | returns the distance between two points
getDist :: Float -> Float -> Float -> Float -> Float
getDist x1 y1 x2 y2 = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)))

-- | check if object is off screen to left
checkLeftBound :: Float -> Float -> Bool
checkLeftBound x1 r1 = x1 + r1 < 0
-- | check if object is off screen to right
checkRightBound :: Float -> Float -> Bool
checkRightBound x1 r1 = x1 - r1 > 1280
-- | check if object is off screen top
checkTopBound :: Float -> Float -> Bool
checkTopBound x1 r1 = x1 + r1 < 0
-- | check if object is off screen bottom
checkBottomBound :: Float -> Float -> Bool
checkBottomBound x1 r1 = x1 - r1 > 720

-- | place object on left side of screen
leftBoundRes :: Float -> Float
leftBoundRes r1 = 1280 + r1
-- | place object on right side of screen
rightBoundRes :: Float -> Float
rightBoundRes r1 = 0 - r1
-- | place object on bottom of screen
topBoundRes :: Float -> Float
topBoundRes r1 = 720 + r1
-- | place object top of screen
bottomBoundRes :: Float -> Float
bottomBoundRes r1 = 0 - r1


-- | detect if circles collide given position and radius
circleCircleCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Bool
circleCircleCollision x1 y1 r1 x2 y2 r2 = (getDist x1 y1 x2 y2) <= (r1 + r2)

circleVelX1 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float-> Float -> Float
circleVelX1 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2 = ((tx (ny x1 y1 x2 y2)) * (dpTan1 x1 y1 vx1 vy1 x2 y2)) + ((nx x1 y1 x2 y2) * (mass1 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2))
circleVelY1 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
circleVelY1 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2 = ((ty (ny x1 y1 x2 y2)) * (dpTan1 x1 y1 vx1 vy1 x2 y2)) + ((ny x1 y1 x2 y2) * (mass1 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2))

circleVelX2 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
circleVelX2 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2 = ((tx (ny x1 y1 x2 y2)) * (dpTan2 x1 y1 x2 y2 vx2 vy2)) + ((nx x1 y1 x2 y2) * (mass2 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2))
circleVelY2 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
circleVelY2 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2 = ((ty (ny x1 y1 x2 y2)) * (dpTan2 x1 y1 x2 y2 vx2 vy2)) + ((ny x1 y1 x2 y2) * (mass2 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2))

nx :: Float -> Float -> Float -> Float -> Float
nx x1 y1 x2 y2 = (x2 - x1) / (getDist x1 y1 x2 y2)
ny :: Float -> Float -> Float -> Float -> Float
ny x1 y1 x2 y2 = (y2 - y1) / (getDist x1 y1 x2 y2)

tx :: Float -> Float
tx ny1 = ny1 * (-1)
ty :: Float -> Float
ty nx1 = nx1

dpTan1 :: Float -> Float -> Float -> Float -> Float -> Float -> Float
dpTan1 x1 y1 vx1 vy1 x2 y2 = (vx1 * (tx (ny x1 y1 x2 y2))) + (vy1 *  (ty (nx x1 y1 x2 y2)))
dpTan2 :: Float -> Float -> Float -> Float -> Float -> Float -> Float
dpTan2 x1 y1 x2 y2 vx2 vy2 = (vx2 * (tx (ny x1 y1 x2 y2))) + (vy2 *  (ty (nx x1 y1 x2 y2)))

dpNorm1 :: Float -> Float -> Float -> Float -> Float -> Float -> Float
dpNorm1 x1 y1 vx1 vy1 x2 y2 = (vx1 * (nx x1 y1 x2 y2)) + (vy1 * (ny x1 y1 x2 y2))
dpNorm2 :: Float -> Float -> Float -> Float -> Float -> Float -> Float
dpNorm2 x1 y1 x2 y2 vx2 vy2 = (vx2 * (nx x1 y1 x2 y2)) + (vy2 * (ny x1 y1 x2 y2))

mass1 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
mass1 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2 = (dpNorm1  x1 y1 vx1 vy1 x2 y2) * (m1 - m2) + 2.0 * m2 * (dpNorm2 x1 y1 x2 y2 vx2 vy2) / (m1 + m2)
mass2 :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
mass2 x1 y1 vx1 vy1 m1 x2 y2 vx2 vy2 m2 = (dpNorm2  x1 y1 x2 y2 vx2 vy2) * (m2 - m1) + 2.0 * m1 * (dpNorm1 x1 y1 vx1 vy1 x2 y2) / (m1 + m2)

-- | Get tangent vector
tangentX :: Float -> Float -> Float
tangentX y1 y2 = y2 - y1
tangentY :: Float -> Float -> Float
tangentY x1 x2 = (x2 - x1) * (-1)

-- | dot product
dotProd :: Float -> Float -> Float -> Float -> Float
dotProd x1 y1 x2 y2 = (getMag x1 y1) * (getMag x2 y2) * (penAngle x1 y1 x2 y2)

-- | normalise vector
normaliseVec :: Float -> Float -> Float
normaliseVec x mag = x / mag

-- | magnetude
getMag :: Float -> Float -> Float
getMag x y = sqrt((x * x) + (y * y))

-- | check if circle collides with a rectangle
circleRectCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Bool
circleRectCollision x1 y1 r1 x2 y2 w2 h2 = sqrt((((circleRectCompX x1 x2 w2) - x1) * ((circleRectCompX x1 x2 w2) - x1)) + (((circleRectCompY y1 y2 h2) - y1) * ((circleRectCompY y1 y2 h2) - y1))) < r1

-- | circle rectangle collison effect on velocity
circleRectResY :: Float -> Float
circleRectResY y = (groundRestitution y) * (-1)
-- | circle rectangle collison effect on velocity
circleRectResX :: Float -> Float
circleRectResX x = (groundRestitution x) * (-1)

-- | restitution
groundRestitution :: Float -> Float
groundRestitution y1 = y1 * 0.8

-- | get the push back vector
circlePushBackX :: Float -> Float -> Float -> Float -> Float
circlePushBackX x1 r1 x2 r2 = (x1 - (collisonPointX x1 r1 x2 r2)) / 16
-- | get the push back vector
circlePushBackY :: Float -> Float -> Float -> Float -> Float
circlePushBackY y1 r1 y2 r2 = (y1 - (collisonPointY y1 r1 y2 r2)) / 16


-- | collision point between two circles X
collisonPointX :: Float -> Float -> Float -> Float -> Float
collisonPointX x1 r1 x2 r2 = (((x1 * r2) + (x2 * r1)) / (r1 + r2))

-- | collision point between two circles Y
collisonPointY :: Float -> Float -> Float -> Float -> Float
collisonPointY y1 r1 y2 r2 = (((y1 * r2) + (y2 * r1)) / (r1 + r2)) 


-- | get the push back vector
pushBackPosX :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
pushBackPosX x1 y1 r1 x2 y2 w2 h2 = (getPenVecX (getEdgeX (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) (penDist r1 (getDist (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2) x1 y1)) (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) - (getEdgeX (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2)))
-- | get the push back vector
pushBackPosY :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
pushBackPosY x1 y1 r1 x2 y2 w2 h2 = (getPenVecY (getEdgeY (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) (penDist r1 (getDist (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2) x1 y1)) (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) - (getEdgeY (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2)))
-- | get the push back vector
topPushBackPosY :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
topPushBackPosY x1 y1 r1 x2 y2 w2 h2 = (getPenVecY (getEdgeY (circleRectCompX x1 x2 w2) r1 (topPenAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) (penDist r1 (getDist (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2) x1 y1)) (topPenAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) - (getEdgeY (circleRectCompX x1 x2 w2) r1 (topPenAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2)))


-- | get edgeX
getEdgeX :: Float -> Float -> Float -> Float
getEdgeX x1 r1 angle = (x1 + r1) * cos (angle)
-- | get edgeY
getEdgeY :: Float -> Float -> Float -> Float
getEdgeY y1 r1 angle = (y1 + r1) * sin (angle)


-- | get Penetration vector
getPenVecX :: Float -> Float -> Float -> Float 
getPenVecX x1 d1 angle = (x1 + d1) * cos (angle)

-- | get Penetration vector
getPenVecY :: Float -> Float -> Float -> Float
getPenVecY y1 d1 angle = (y1 + d1) * sin (angle)


-- | Get penetration angle
penAngle :: Float -> Float -> Float -> Float -> Float
penAngle x1 y1 x2 y2 = atan2 (y2 - y1) (x2 - x1)
-- | Get penetration angle for top 
topPenAngle :: Float -> Float -> Float -> Float -> Float
topPenAngle x1 y1 x2 y2 = atan2 (y1 - y2) (x1 - x2)

-- | Get penetration distance
penDist :: Float -> Float -> Float
penDist r1 d1 = r1 - d1

-- | checks if closest wall is left or right and returns wall
circleRectCompX :: Float -> Float -> Float -> Float
circleRectCompX x1 x2 w2 = if x1 < x2 then x2 else if x1 > x2 + w2 then x2 + w2 else x1

-- | checks if closest wall is top or bottom and returns wall
circleRectCompY :: Float -> Float -> Float -> Float
circleRectCompY y1 y2 h2 = if y1 < y2 then y2 else if y1 > y2 + h2 then y2 + h2 else y1