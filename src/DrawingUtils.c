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

#include "DrawingUtils.h"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"

typedef struct Triangle {
    Vector2 a;
    Vector2 b;
    Vector2 c;
} Triangle;

typedef struct TriangleB2Vec2 {
    b2Vec2 a;
    b2Vec2 b;
    b2Vec2 c;
} TriangleB2Vec2;

bool isConvex( Vector2 prev, Vector2 curr, Vector2 next ) {
    return (curr.x - prev.x) * (next.y - curr.y) - (curr.y - prev.y) * (next.x - curr.x) < 0;
}

bool isTriangleCCW( Vector2 a, Vector2 b, Vector2 c ) {
    return ( (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) ) < 0;
}

bool isTriangleCW( Vector2 a, Vector2 b, Vector2 c ) {
    return ( (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) ) > 0;
}

// Ear Clipping
int triangulatePolygon( const Vector2 *points, int pointCount, Triangle *triangles, int maxTriangles, bool cw ) {

    if ( pointCount < 3 ) {
        return 0;
    }

    int *indices = (int*) malloc( sizeof(int) * pointCount );
    for ( int i = 0; i < pointCount; i++ ) {
        indices[i] = i;
    }

    int n = pointCount;
    int triCount = 0;

    while ( n > 3 && triCount < maxTriangles ) {

        bool earFound = false;

        for ( int i = 0; i < n; i++ ) {

            int i0 = indices[(i + n - 1) % n];
            int i1 = indices[i];
            int i2 = indices[(i + 1) % n];

            Vector2 prev;
            Vector2 curr;
            Vector2 next;
            
            if ( cw ) {
                prev = points[i2];
                curr = points[i1];
                next = points[i0];
            } else {
                prev = points[i0];
                curr = points[i1];
                next = points[i2];
            }

            if ( !isConvex( prev, curr, next ) ) {
                continue;
            }

            bool containsPoint = false;
            for ( int j = 0; j < n; j++ ) {
                int idx = indices[j];
                if ( idx == i0 || idx == i1 || idx == i2 ) {
                    continue;
                }
                if ( CheckCollisionPointTriangle( points[idx], prev, curr, next ) ) {
                    containsPoint = true;
                    break;
                }
            }

            if ( !containsPoint ) {
                triangles[triCount++] = (Triangle){ prev, curr, next };
                for ( int j = i; j < n - 1; j++ ) {
                    indices[j] = indices[j + 1];
                }
                n--;
                earFound = true;
                break;
            }

        }

        if ( !earFound ) {
            break;
        }

    }

    if ( n == 3 && triCount < maxTriangles ) {
        triangles[triCount++] = (Triangle){
            points[indices[0]],
            points[indices[1]],
            points[indices[2]]
        };
    }

    free( indices );

    return triCount;

}

void drawConcaveShape( const Vector2 *points, int pointCount, Color color, bool cw ) {

    Triangle triangles[128];
    int triCount = triangulatePolygon( points, pointCount, triangles, 128, cw );

    rlBegin( RL_TRIANGLES );
    rlColor4ub( color.r, color.g, color.b, color.a );

    for ( int i = 0; i < triCount; i++ ) {

        Vector2 a = triangles[i].a;
        Vector2 b = triangles[i].b;
        Vector2 c = triangles[i].c;

        if ( !isTriangleCCW( a, b, c ) ) {
            Vector2 tmp = b;
            b = c;
            c = tmp;
        }

        rlVertex2f( a.x, a.y );
        rlVertex2f( b.x, b.y );
        rlVertex2f( c.x, c.y );

    }

    rlEnd();

}

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

bool isConvexB2Vec2( b2Vec2 prev, b2Vec2 curr, b2Vec2 next ) {
    return (curr.x - prev.x) * (next.y - curr.y) - (curr.y - prev.y) * (next.x - curr.x) < 0;
}

bool isTriangleCCWB2Vec2( b2Vec2 a, b2Vec2 b, b2Vec2 c ) {
    return ( (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) ) < 0;
}

bool isTriangleCWB2Vec2( b2Vec2 a, b2Vec2 b, b2Vec2 c ) {
    return ( (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) ) > 0;
}

bool CheckCollisionPointTriangleB2Vec2( b2Vec2 point, b2Vec2 a, b2Vec2 b, b2Vec2 c ) {
    return CheckCollisionPointTriangle( 
        (Vector2){ point.x, point.y},
        (Vector2){ a.x, a.y},
        (Vector2){ b.x, b.y},
        (Vector2){ c.x, c.y}
    );
}

// Ear Clipping
int triangulatePolygonB2Vec2( const b2Vec2 *points, int pointCount, TriangleB2Vec2 *triangles, int maxTriangles, bool cw ) {

    if ( pointCount < 3 ) {
        return 0;
    }

    int *indices = (int*) malloc( sizeof(int) * pointCount );
    for ( int i = 0; i < pointCount; i++ ) {
        indices[i] = i;
    }

    int n = pointCount;
    int triCount = 0;

    while ( n > 3 && triCount < maxTriangles ) {

        bool earFound = false;

        for ( int i = 0; i < n; i++ ) {

            int i0 = indices[(i + n - 1) % n];
            int i1 = indices[i];
            int i2 = indices[(i + 1) % n];

            b2Vec2 prev;
            b2Vec2 curr;
            b2Vec2 next;
            
            if ( cw ) {
                prev = points[i2];
                curr = points[i1];
                next = points[i0];
            } else {
                prev = points[i0];
                curr = points[i1];
                next = points[i2];
            }

            if ( !isConvexB2Vec2( prev, curr, next ) ) {
                continue;
            }

            bool containsPoint = false;
            for ( int j = 0; j < n; j++ ) {
                int idx = indices[j];
                if ( idx == i0 || idx == i1 || idx == i2 ) {
                    continue;
                }
                if ( CheckCollisionPointTriangleB2Vec2( points[idx], prev, curr, next ) ) {
                    containsPoint = true;
                    break;
                }
            }

            if ( !containsPoint ) {
                triangles[triCount++] = (TriangleB2Vec2){ prev, curr, next };
                for ( int j = i; j < n - 1; j++ ) {
                    indices[j] = indices[j + 1];
                }
                n--;
                earFound = true;
                break;
            }

        }

        if ( !earFound ) {
            break;
        }

    }

    if ( n == 3 && triCount < maxTriangles ) {
        triangles[triCount++] = (TriangleB2Vec2){
            points[indices[0]],
            points[indices[1]],
            points[indices[2]]
        };
    }

    free( indices );

    return triCount;

}

void drawConcaveShapeB2Vec2( const b2Vec2 *points, int pointCount, Color color, bool cw ) {

    TriangleB2Vec2 triangles[128];
    int triCount = triangulatePolygonB2Vec2( points, pointCount, triangles, 128, cw );

    rlBegin( RL_TRIANGLES );
    rlColor4ub( color.r, color.g, color.b, color.a );

    for ( int i = 0; i < triCount; i++ ) {

        b2Vec2 a = triangles[i].a;
        b2Vec2 b = triangles[i].b;
        b2Vec2 c = triangles[i].c;

        if ( !isTriangleCCWB2Vec2( a, b, c ) ) {
            b2Vec2 tmp = b;
            b = c;
            c = tmp;
        }

        rlVertex2f( a.x, a.y );
        rlVertex2f( b.x, b.y );
        rlVertex2f( c.x, c.y );

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