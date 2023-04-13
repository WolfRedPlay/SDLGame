#pragma once
#include "Basic.h"
#include "Drawer.h"
#include "Save.h"

extern int qountOfWeapons;
extern int qountOfArmors;
extern int qountOfPotions;
extern int qountOfAbilities;
extern int qountOfQusts;
//extern int qountOfQustItems;
extern Weapon* ALLWeaponsList;
extern Armor* ALLArmorsList;
extern Potion* ALLPotionsList;
extern Ability* ALLAbilitiesList;
extern Quest* questsList;
//extern QuestItem* ALLQuestItemsList = createAllQuestItems(qountOfQustItems);



extern bool inGame;

void DeInit(int error);

void startMenu(Player& player, char **map);

void gameMenu(Player& player, char** map);

void playerMenu(Player& player);
