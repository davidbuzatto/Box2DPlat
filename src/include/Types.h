#pragma once

#include "box2d/box2d.h"
#include "raylib/raylib.h"

#define MAX_OBSTACLES 100
#define MAX_CHAIN_OBSTACLES 100
#define MAX_CHAIN_OBSTACLE_POINTS 50

typedef struct Player {

    b2BodyId bodyId;
    b2ShapeId shapeId;

    Vector2 dim;
    b2Polygon rect;
    Color color;

    float maxWalkVelocity;
    float walkImpulse;
    float runImpulse;
    float jumpImpulse;
    
} Player;

typedef struct Obstacle {

    b2BodyId bodyId;
    b2ShapeId shapeId;

    Vector2 dim;
    b2Polygon rect;
    Color color;

} Obstacle;

typedef struct ChainObstacle {

    b2BodyId bodyId;
    b2ChainId chainId;

    b2Vec2 points[MAX_CHAIN_OBSTACLE_POINTS+2];
    int pointQuantity;
    
    Color color;

} ChainObstacle;

typedef struct GameWorld {

    b2WorldDef worldDef;
    b2WorldId worldId;

    Player player;

    Obstacle obstacles[MAX_OBSTACLES];
    int obstaclesQuantity;

    ChainObstacle chainObstacles[MAX_CHAIN_OBSTACLES];
    int chainObstacleQuantity;

} GameWorld;

