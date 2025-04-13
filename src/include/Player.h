#pragma once

#include "Types.h"

void createPlayer( Player *p, float x, float y, float w, float h, Color color, GameWorld *gw );
void updatePlayer( Player *p );
void drawPlayer( Player *p );