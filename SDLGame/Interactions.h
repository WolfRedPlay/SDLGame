#pragma once
#include "Basic.h"
#include "Drawer.h"

extern int qountOfWeapons;
extern int qountOfArmors;
extern int qountOfPotions;
extern int qountOfAbilities;
//extern int qountOfQustItems;
extern Weapon* ALLWeaponsList;
extern Armor* ALLArmorsList;
extern Potion* ALLPotionsList;
extern Ability* ALLAbilitiesList;
//extern QuestItem* ALLQuestItemsList = createAllQuestItems(qountOfQustItems);


void interact(char** map, Player& player);