#pragma once

#include "Types.h"

void createChainObstacle( b2Vec2 *points, int pointQuantity, Color color, bool isConcave, GameWorld *gw );
void drawChainObstacle( ChainObstacle *co );