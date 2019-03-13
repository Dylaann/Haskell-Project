module Move where

foreign export ccall moveGravity :: Float -> Float
foreign export ccall applyForce :: Float -> Float -> Float
foreign export ccall circleCircleCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Bool
foreign export ccall circleRectCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Bool
foreign export ccall pushBackPosX :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float
foreign export ccall pushBackPosY :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Float

-- | act as gravity and move the y coordinate
moveGravity :: Float -> Float
moveGravity y = y + 0.8

-- | add two forces together
applyForce :: Float -> Float -> Float 
applyForce x y = x + y

-- | detect if circles collide given position and radius
circleCircleCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Bool
circleCircleCollision x1 y1 r1 x2 y2 r2 = (getDist x1 y1 x2 y2) < (r1 + r2)

-- | check if  circle collides with a rectangle
circleRectCollision :: Float -> Float -> Float -> Float -> Float -> Float -> Float -> Bool
circleRectCollision x1 y1 r1 x2 y2 w2 h2 = sqrt((((circleRectCompX x1 x2 w2) - x1) * ((circleRectCompX x1 x2 w2) - x1)) + (((circleRectCompY y1 y2 h2) - y1) * ((circleRectCompY y1 y2 h2) - y1))) < r1


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


-- | returns the distance between two points
getDist :: Float -> Float -> Float -> Float -> Float
getDist x1 y1 x2 y2 = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)))