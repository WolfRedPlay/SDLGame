#pragma once
#include "Basic.h"
#include "Drawer.h"

extern void DeInit(int error);

extern bool inGame;

extern int qountOfWeapons;
extern int qountOfArmors;
extern int qountOfPotions;
extern Weapon* ALLWeaponsList;
extern Armor* ALLArmorsList;
extern Potion* ALLPotionsList;

void startBattle(Player& player, EnemiesSquad enemies);
