#include <assert.h>

#include "Obstacle.h"
#include "Types.h"

#include "raylib/raylib.h"
#include "box2d/box2d.h"

void createObstacle( float x, float y, float w, float h, Color color, GameWorld *gw ) {

    assert( gw->obstaclesQuantity < MAX_OBSTACLES );

    Obstacle *o = &gw->obstacles[gw->obstaclesQuantity++];

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.position = (b2Vec2){ x, y };
    o->bodyId = b2CreateBody( gw->worldId, &bodyDef );

    o->dim = (Vector2){ w, h };
    o->rect = b2MakeBox( o->dim.x/2, o->dim.y/2 );

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    o->shapeId = b2CreatePolygonShape( o->bodyId, &shapeDef, &o->rect );

    o->color = color;

}

void drawObstacle( Obstacle *o ) {

    b2Vec2 position = b2Body_GetPosition( o->bodyId );

    DrawRectangle( 
        position.x - o->dim.x/2, position.y - o->dim.y / 2, 
        o->dim.x, o->dim.y, o->color
    );

}