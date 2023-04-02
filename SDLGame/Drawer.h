#pragma once
#include "Basic.h"
#include <SDL_ttf.h>

extern SDL_Renderer* ren;


void drawScreen(char** map, Coordinates playerPos);
void drawPlayer(Coordinates playerPosition);
void drawStartMenu(int coursorPosition);