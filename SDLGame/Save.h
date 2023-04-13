#pragma once
#include "Basic.h"


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



void setSaves(const char* fn, Player player);
void setMapSaves(const char* fn, char** map);
void setQuestsSaves(const char* fn, Quest* quests, int amountQuests);

void loadSaves(const char* fn, Player& player);
void loadQuestsSaves(const char* fn, Quest* quests, int amountQuests);