/**
 * @file utils.c
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"

void drawShape( const Vector2 *points, int pointCount, Color color, bool cw ) {

    if ( pointCount < 3 ) {
        return;
    }

    Vector2 center = { 0 };
    for ( int i = 0; i < pointCount; i++ ) {
        center.x += points[i].x;
        center.y += points[i].y;
    }
    center.x /= pointCount;
    center.y /= pointCount;

    rlBegin( RL_TRIANGLES );
    rlColor4ub( color.r, color.g, color.b, color.a );

    if ( cw ) {
        for ( int i = pointCount - 1; i >= 0; i-- ) {
            Vector2 p1 = points[(i + 1) % pointCount];
            Vector2 p2 = points[i];
            rlVertex2f( center.x, center.y );
            rlVertex2f( p1.x, p1.y );
            rlVertex2f( p2.x, p2.y );
        }
    } else {
        for ( int i = 0; i < pointCount; i++ ) {
            Vector2 p1 = points[i];
            Vector2 p2 = points[(i + 1) % pointCount];
            rlVertex2f( center.x, center.y );
            rlVertex2f( p1.x, p1.y );
            rlVertex2f( p2.x, p2.y );
        }
    }

    rlEnd();

}

void drawShapeLines( const Vector2 *points, int pointCount, Color color ) {

    if ( pointCount < 3 ) {
        return;
    }

    rlBegin( RL_LINES );
    rlColor4ub( color.r, color.g, color.b, color.a );

    for ( int i = 0; i < pointCount; i++ ) {
        Vector2 p1 = points[i];
        Vector2 p2 = points[(i + 1) % pointCount];
        rlVertex2f( p1.x, p1.y );
        rlVertex2f( p2.x, p2.y );
    }

    rlEnd();

}

void drawShapeB2Vec2( const b2Vec2 *points, int pointCount, Color color, bool cw ) {

    if ( pointCount < 3 ) {
        return;
    }

    b2Vec2 center = { 0 };
    for ( int i = 0; i < pointCount; i++ ) {
        center.x += points[i].x;
        center.y += points[i].y;
    }
    center.x /= pointCount;
    center.y /= pointCount;

    rlBegin( RL_TRIANGLES );
    rlColor4ub( color.r, color.g, color.b, color.a );

    if ( cw ) {
        for ( int i = pointCount - 1; i >= 0; i-- ) {
            b2Vec2 p1 = points[(i + 1) % pointCount];
            b2Vec2 p2 = points[i];
            rlVertex2f( center.x, center.y );
            rlVertex2f( p1.x, p1.y );
            rlVertex2f( p2.x, p2.y );
        }
    } else {
        for ( int i = 0; i < pointCount; i++ ) {
            b2Vec2 p1 = points[i];
            b2Vec2 p2 = points[(i + 1) % pointCount];
            rlVertex2f( center.x, center.y );
            rlVertex2f( p1.x, p1.y );
            rlVertex2f( p2.x, p2.y );
        }
    }

    rlEnd();

}

void drawShapeLinesB2Vec2( const b2Vec2 *points, int pointCount, Color color ) {

    if ( pointCount < 3 ) {
        return;
    }

    rlBegin( RL_LINES );
    rlColor4ub( color.r, color.g, color.b, color.a );

    for ( int i = 0; i < pointCount; i++ ) {
        b2Vec2 p1 = points[i];
        b2Vec2 p2 = points[(i + 1) % pointCount];
        rlVertex2f( p1.x, p1.y );
        rlVertex2f( p2.x, p2.y );
    }

    rlEnd();

}