/**
 * @file utils.h
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary function and constant declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "raylib/raylib.h"
#include "box2d/box2d.h"

void drawShape( const Vector2 *points, int pointCount, Color color, bool cw );
void drawConcaveShape( const Vector2 *points, int pointCount, Color color, bool cw );
void drawShapeLines( const Vector2 *points, int pointCount, Color color );

void drawShapeB2Vec2( const b2Vec2 *points, int pointCount, Color color, bool cw );
void drawConcaveShapeB2Vec2( const b2Vec2 *points, int pointCount, Color color, bool cw );
void drawShapeLinesB2Vec2( const b2Vec2 *points, int pointCount, Color color );