#pragma once
#include "Basic.h"
#include <SDL_ttf.h>
#include <SDL_image.h>

extern SDL_Renderer* ren;


void drawScreen(char** map, Coordinates playerPos);
void drawPlayer(Coordinates playerPosition);
void drawStartMenu(int coursorPosition);
void drawHeroCreatingMenu(Player& player, int heroNum, int coursorPosition);