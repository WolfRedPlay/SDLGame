#pragma once
#include "Basic.h"


extern SDL_Renderer* ren;

extern int window_width;
extern int window_height;

extern bool isMoving;
extern int dt;

void drawScreen(char** map, Coordinates playerPos, int mapSizeX, int mapSizeY);
void drawPlayer(Coordinates playerPosition, int diraction, int frame);


void drawChestOpenning(Weapon givedWeapon, Armor givedArmor, Potion givedPotion, int givedMoney);
//void drawChestOpenning(Weapon givedWeapon, Armor givedArmor, Potion givedPotion, int givedMoney, QuestItem item);

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



void drawSeller(int typeOfSeller, int coursorPosition);

void drawSellerChoice(SellerOfWeapons seller, int coursorPosition);
void drawSellerChoice(SellerOfArmors seller, int coursorPosition);
void drawSellerChoice(SellerOfPotions seller, int coursorPosition);
void drawSellerChoice(SellerOfAbilities seller, int coursorPosition);