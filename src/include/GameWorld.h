/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "raylib/raylib.h"
#include "box2d/box2d.h"

#include "Types.h"

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void );

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw );

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta );

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw );

void handleChainObjectCreation( GameWorld *gw );
void createDummyObstcales( GameWorld *gw );

void handleContactEvents( GameWorld *gw );
void handleContacBetweenShapes( b2ShapeId sIdA, b2ShapeId sIdB, Color color );