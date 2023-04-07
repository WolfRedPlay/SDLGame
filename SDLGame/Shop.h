#pragma once
#include "Basic.h"
#include "Drawer.h"



extern int qountOfWeapons;
extern int qountOfArmors;
extern int qountOfPotions;
extern int qountOfAbilities;
extern Weapon* ALLWeaponsList;
extern Armor* ALLArmorsList;
extern Potion* ALLPotionsList;
extern Ability* ALLAbilitiesList;

extern void DeInit(int error);


void weaponSeller(Player& player, int stage, char** map);
void armorSeller(Player& player, int stage, char** map);
void potionSeller(Player& player, int stage, char** map);
void abilitySeller(Player& player, int stage, char** map);