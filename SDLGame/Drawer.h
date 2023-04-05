#pragma once
#include "Basic.h"


extern SDL_Renderer* ren;

extern int window_width;
extern int window_height;


void drawScreen(char** map, Coordinates playerPos);
void drawPlayer(Coordinates playerPosition);

void drawHeroChoice(Player player, int coursorPosition);
void drawConfirmation();
void drawSaveSlots(int coursorPosition);

void drawStartMenu(int coursorPosition);
void drawHeroCreatingMenu(int heroNum, int coursorPosition);
void drawHeroNameChoice(int coursorPosition);
void drawPlayerNameChoosing(char* name);
void drawRandomNameChoosing(char* name);

void drawGameMenu(int coursorPosition);

void drawPlayerMenu(int coursorPosition);
void drawHeroesStats(Player& player);
void drawPlayerWeapons(Player& player, int coursorPosition);
void drawPlayerArmors(Player& player, int coursorPosition);
void drawPlayerPotions(Player& player, int coursorPosition);
void drawHeroAbilities(Hero& hero, int coursorPosition);