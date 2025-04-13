#include "Player.h"
#include "Types.h"

#include "raylib/raylib.h"
#include "box2d/box2d.h"

void createPlayer( Player *p, float x, float y, float w, float h, Color color, GameWorld *gw ) {

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){ x, y };
    bodyDef.fixedRotation = true;
    p->bodyId = b2CreateBody( gw->worldId, &bodyDef );

    p->dim = (Vector2){ w, h };
    p->rect = b2MakeBox( p->dim.x/2, p->dim.y/2 );

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.05f;

    p->shapeId = b2CreatePolygonShape( p->bodyId, &shapeDef, &p->rect );

    p->color = color;

    p->maxWalkVelocity = 200;
    p->walkImpulse = 1000000;
    p->runImpulse = 5000000;
    p->jumpImpulse = -1000000;

}

void updatePlayer( Player *p ) {

    if ( IsKeyDown( KEY_RIGHT ) ) {
        if ( b2Body_GetLinearVelocity( p->bodyId ).x < p->maxWalkVelocity ) {
            b2Body_ApplyForceToCenter( p->bodyId, (b2Vec2){ p->walkImpulse, 0 }, true );
        }
    }

    if ( IsKeyDown( KEY_LEFT ) ) {
        if ( b2Body_GetLinearVelocity( p->bodyId ).x > -p->maxWalkVelocity ) {
            b2Body_ApplyForceToCenter( p->bodyId, (b2Vec2){ -p->walkImpulse, 0 }, true );
        }
    }

    if ( IsKeyPressed( KEY_SPACE ) ) {
        b2Body_ApplyLinearImpulseToCenter( p->bodyId, (b2Vec2){ 0, p->jumpImpulse }, true );
    }

}

void drawPlayer( Player *p ) {

    b2Vec2 position = b2Body_GetPosition( p->bodyId );
    b2Rot rotation = b2Body_GetRotation( p->bodyId );
    
    Rectangle rect = (Rectangle){ 
        position.x, 
        position.y, 
        p->dim.x, 
        p->dim.y
    };

    DrawRectanglePro( 
        rect, 
        (Vector2) { rect.width / 2, rect.height / 2 }, 
        RAD2DEG * b2Rot_GetAngle( rotation ),
        p->color
    );

}