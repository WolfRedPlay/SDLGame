#pragma once
#include "Basic.h"

extern SDL_Renderer* ren;


void drawScreen(char** map, Coordinates playerPos);
void drawPlayer(Coordinates playerPosition);