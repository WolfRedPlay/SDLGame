#pragma once
#include "Basic.h"
#include <SDL_ttf.h>
#include <SDL_image.h>

extern SDL_Renderer* ren;





void drawScreen(char** map, Coordinates playerPos);
void drawPlayer(Coordinates playerPosition);

void drawStartMenu(int coursorPosition);

void drawHeroCreatingMenu(int heroNum, int coursorPosition);
void drawHeroNameChoice(int coursorPosition);
void drawPlayerNameChoosing(char* name);
void drawRandomNameChoosing(char* name);

void drawPlayerMenu(int coursorPosition);
void drawHeroesStats(Player& player);