module Move where

foreign export ccall moveGravity :: Float -> Float
foreign export ccall applyForce :: Float -> Float -> Float
foreign export ccall circleCircleCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Bool
foreign export ccall circleRectCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Bool
foreign export ccall pushBackPosX :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall pushBackPosY :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall circleRectResY :: Float -> Float
foreign export ccall circleRectResX :: Float -> Float
foreign export ccall checkLeftBound :: Float -> Float -> Bool
foreign export ccall checkRightBound :: Float -> Float -> Bool
foreign export ccall leftBoundRes :: Float -> Float
foreign export ccall rightBoundRes :: Float -> Float
foreign export ccall circleCircleResX :: Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall circleCircleResY :: Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall newVelX1 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall newVelY1 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall newVelX2 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall newVelY2 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float

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

-- | place object on left side of screen
leftBoundRes :: Float -> Float
leftBoundRes r1 = 1280 + r1
-- | place object on right side of screen
rightBoundRes :: Float -> Float
rightBoundRes r1 = 0 - r1




-- | detect if circles collide given position and radius
circleCircleCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Bool
circleCircleCollision x1 y1 r1 x2 y2 r2 = (getDist x1 y1 x2 y2) < (r1 + r2)

-- | circle collision response
circleCircleResX :: Float -> Float -> Float -> Float -> Float -> Float -> Float
circleCircleResX x1 y1 v1 x2 y2 v2 = (v1 - v2) - ((normaliseVec (tangentX y1 y2) (getMag x1 y1)) * (dotProd x1 y1 x2 y2))

-- | circle collision response
circleCircleResY :: Float -> Float -> Float -> Float -> Float -> Float -> Float
circleCircleResY x1 y1 v1 x2 y2 v2 = (v1 - v2) - ((normaliseVec (tangentY x1 x2) (getMag x1 y1)) * (dotProd x1 y1 x2 y2))


nxPoint :: Float -> Float -> Float -> Float
nxPoint x1 x2 d = (x2 -x1) / d
nyPoint :: Float -> Float -> Float -> Float
nyPoint y1 y2 d = (y2 -y1) / d

pValue :: Float -> Float -> Float -> Float -> Float -> Float -> Float
pValue vx1 vy1 vx2 vy2 nx ny = 2 * (vx1 * nx + vy1 * ny - vx2 * nx - vy2 * ny)

newVelX1 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
newVelX1 x1 y1 vx1 vy1 x2 y2 vx2 vy2 = vx1 - (pValue vx1 vy1 vx2 vy2 (nxPoint x1 x2 (getDist x1 y1 x2 y2)) (nyPoint y1 y2 (getDist x1 y1 x2 y2))) * (nxPoint x1 x2 (getDist x1 y1 x2 y2))
newVelY1 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
newVelY1 x1 y1 vx1 vy1 x2 y2 vx2 vy2 = vy1 - (pValue vx1 vy1 vx2 vy2 (nxPoint x1 x2 (getDist x1 y1 x2 y2)) (nyPoint y1 y2 (getDist x1 y1 x2 y2))) * (nyPoint y1 y2 (getDist x1 y1 x2 y2))
newVelX2 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
newVelX2 x1 y1 vx1 vy1 x2 y2 vx2 vy2 = vx2 + (pValue vx1 vy1 vx2 vy2 (nxPoint x1 x2 (getDist x1 y1 x2 y2)) (nyPoint y1 y2 (getDist x1 y1 x2 y2))) * (nxPoint x1 x2 (getDist x1 y1 x2 y2))
newVelY2 ::  Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
newVelY2 x1 y1 vx1 vy1 x2 y2 vx2 vy2 = vy2 - (pValue vx1 vy1 vx2 vy2 (nxPoint x1 x2 (getDist x1 y1 x2 y2)) (nyPoint y1 y2 (getDist x1 y1 x2 y2))) * (nyPoint y1 y2 (getDist x1 y1 x2 y2))




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

-- | check if  circle collides with a rectangle
circleRectCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Bool
circleRectCollision x1 y1 r1 x2 y2 w2 h2 = sqrt((((circleRectCompX x1 x2 w2) - x1) * ((circleRectCompX x1 x2 w2) - x1)) + (((circleRectCompY y1 y2 h2) - y1) * ((circleRectCompY y1 y2 h2) - y1))) < r1

-- | circle rectangle collison effect on velocity
circleRectResY :: Float -> Float
circleRectResY y = (groundRestitution y) * (-1)
-- | circle rectangle collison effect on velocity
circleRectResX :: Float -> Float
circleRectResX x = (groundRestitution x)

-- | restitution
groundRestitution :: Float -> Float
groundRestitution y1 = y1 * 0.7


-- | get the push back vector
pushBackPosX :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
pushBackPosX x1 y1 r1 x2 y2 w2 h2 = (getPenVecX (getEdgeX (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) (penDist r1 (getDist (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2) x1 y1)) (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) - (getEdgeX (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2)))
-- | get the push back vector
pushBackPosY :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
pushBackPosY x1 y1 r1 x2 y2 w2 h2 = (getPenVecY (getEdgeY (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) (penDist r1 (getDist (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2) x1 y1)) (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2))) - (getEdgeY (circleRectCompX x1 x2 w2) r1 (penAngle x1 y1 (circleRectCompX x1 x2 w2) (circleRectCompY y1 y2 h2)))

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

-- | Get penetration distance
penDist :: Float -> Float -> Float
penDist r1 d1 = r1 - d1


-- | checks if closest wall is left or right and returns wall
circleRectCompX :: Float -> Float -> Float -> Float
circleRectCompX x1 x2 w2 = if x1 < x2 then x2 else if x1 > x2 + w2 then x2 + w2 else x1

-- | checks if closest wall is top or bottom and returns wall
circleRectCompY :: Float -> Float -> Float -> Float
circleRectCompY y1 y2 h2 = if y1 < y2 then y2 else if y1 > y2 + h2 then y2 + h2 else y1