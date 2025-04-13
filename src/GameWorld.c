/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GameWorld.h"
#include "ResourceManager.h"
#include "Types.h"
#include "Player.h"
#include "Obstacle.h"
#include "ChainObstacle.h"

#include "raylib/raylib.h"
#include "raylib/rlgl.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#include "box2d/box2d.h"

b2Vec2 creationPoints[MAX_CHAIN_OBSTACLE_POINTS];
int creationPointsQ;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    SetExitKey( KEY_NULL );
    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    float lengthUnitsPerMeter = 128.0f;
	b2SetLengthUnitsPerMeter( lengthUnitsPerMeter );

    gw->worldDef = b2DefaultWorldDef();
    gw->worldDef.gravity = (b2Vec2){ 0.0f, 9.8f * lengthUnitsPerMeter };
    gw->worldId = b2CreateWorld( &gw->worldDef );

    gw->obstaclesQuantity = 0;
    gw->chainObstacleQuantity = 0;

    createPlayer( &gw->player, GetScreenWidth() / 2, GetScreenHeight() / 2, 40, 40, BLUE, gw );

    createObstacle( 10, GetScreenHeight() / 2, 20, GetScreenHeight() - 40, ORANGE, gw );
    createObstacle( GetScreenWidth() - 10, GetScreenHeight() / 2, 20, GetScreenHeight() - 40, ORANGE, gw );
    createObstacle( GetScreenWidth() / 2, 10, GetScreenWidth(), 20, ORANGE, gw );
    createObstacle( GetScreenWidth() / 2, GetScreenHeight() - 10, GetScreenWidth(), 20, ORANGE, gw );

    // dummy chain obstacle
    creationPointsQ = 0;
    b2Vec2 pos[MAX_CHAIN_OBSTACLE_POINTS];
    pos[0] = (b2Vec2) { 700, 300 };
    pos[1] = (b2Vec2) { 700, 330 };
    pos[2] = (b2Vec2) { 500, 330 };
    pos[3] = (b2Vec2) { 500, 300 };
    createChainObstacle( pos, 4, BLACK, gw );

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta ) {

    int subStepCount = 4;
    b2World_Step( gw->worldId, delta, subStepCount );

    updatePlayer( &gw->player );

    if ( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) ) {
        if ( creationPointsQ < MAX_CHAIN_OBSTACLE_POINTS ) {
            int p = creationPointsQ;
            creationPoints[p].x = GetMouseX();
            creationPoints[p].y = GetMouseY();
            creationPointsQ++;
        }
    }

    if ( IsKeyPressed( KEY_ENTER ) ) {
        if ( creationPointsQ > 3 && creationPointsQ < MAX_CHAIN_OBSTACLE_POINTS ) {
            createChainObstacle( creationPoints, creationPointsQ, BLACK, gw );
            /*for ( int i = 0; i < creationPointsQ; i++ ) {
                TraceLog( LOG_INFO, "%.2f, %.2f", creationPoints[i].x, creationPoints[i].y );
            }*/
            creationPointsQ = 0;
        }
    }

    if ( IsKeyPressed( KEY_ESCAPE ) ) {
        creationPointsQ = 0;
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    drawPlayer( &gw->player );

    for ( int i = 0; i < gw->obstaclesQuantity; i++ ) {
        drawObstacle( &gw->obstacles[i] );
    }

    for ( int i = 0; i < gw->chainObstacleQuantity; i++ ) {
        drawChainObstacle( &gw->chainObstacles[i] );
    }

    for ( int i = 0; i < creationPointsQ - 1; i++ ) {
        DrawLine( 
            creationPoints[i].x,
            creationPoints[i].y,
            creationPoints[i+1].x,
            creationPoints[i+1].y,
            GREEN
        );
    }

    EndDrawing();

}