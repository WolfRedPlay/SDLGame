#pragma once
#include "Basic.h"
#include "Drawer.h"

extern int qountOfWeapons;
extern int qountOfArmors;
extern int qountOfPotions;
//extern int qountOfQustItems;
//extern int qountOfAbilities;
extern Weapon* ALLWeaponsList;
extern Armor* ALLArmorsList;
extern Potion* ALLPotionsList;
//extern QuestItem* ALLQuestItemsList = createAllQuestItems(qountOfQustItems);
//extern Ability* ALLAbilitiesList = createAllAbilities(qountOfAbilities);

void DeInit(int error);

bool startMenu(Player& player);

bool playerMenu(Player& player);
