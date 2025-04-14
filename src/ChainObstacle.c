#include <assert.h>

#include "ChainObstacle.h"
#include "Types.h"

#include "raylib/raylib.h"
#include "box2d/box2d.h"

void createChainObstacle( b2Vec2 *points, int pointQuantity, Color color, GameWorld *gw ) {

    assert( gw->chainObstacleQuantity < MAX_CHAIN_OBSTACLES && pointQuantity < MAX_CHAIN_OBSTACLE_POINTS );

    ChainObstacle *co = &gw->chainObstacles[gw->chainObstacleQuantity++];

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.userData = "chain";
    co->bodyId = b2CreateBody( gw->worldId, &bodyDef );

    for ( int i = 0; i < pointQuantity; i++ ) {
        co->points[i] = points[i];
    }
    co->pointQuantity = pointQuantity;

    // add two more points, one for loop, one to prevend misscollision
    co->points[co->pointQuantity++] = points[0];
    co->points[co->pointQuantity++] = points[0];

    b2ChainDef chainDef = b2DefaultChainDef();
    chainDef.points = co->points;
    chainDef.count = co->pointQuantity;
    chainDef.userData = co;
    
    co->chainId = b2CreateChain( co->bodyId, &chainDef );

    co->color = color;

}

void drawChainObstacle( ChainObstacle *co ) {

    for ( int i = 0; i < co->pointQuantity - 1; i++ ) {
        DrawLine( 
            co->points[i].x,
            co->points[i].y,
            co->points[i+1].x,
            co->points[i+1].y,
            co->color
        );
    }

}