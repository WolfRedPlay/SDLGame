#pragma once
#include "Basic.h"


extern SDL_Renderer* ren;




void drawScreen(char** map, Coordinates playerPos);
void drawPlayer(Coordinates playerPosition);

void drawStartMenu(int coursorPosition);

void drawHeroCreatingMenu(int heroNum, int coursorPosition);
void drawHeroNameChoice(int coursorPosition);
void drawPlayerNameChoosing(char* name);
void drawRandomNameChoosing(char* name);

void drawHeroChoice(Player player, int coursorPosition);
void drawConfirmation();

void drawPlayerMenu(int coursorPosition);
void drawHeroesStats(Player& player);
void drawPlayerWeapons(Player& player, int coursorPosition);
void drawPlayerArmors(Player& player, int coursorPosition);
void drawPlayerPotions(Player& player, int coursorPosition);
void drawHeroAbilities(Hero& hero, int coursorPosition);