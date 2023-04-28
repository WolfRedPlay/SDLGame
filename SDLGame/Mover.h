#pragma once
#include "Basic.h"
#include "Save.h"
#include <math.h>

extern bool inShop, inDunge, inGlobal,
shopMapReaded, dungeMapReaded, globalMapReaded;
extern char** map;
extern NPC* NPCs;
extern QuestNPC* questNPCs;
extern Enemy* bosses;
extern QuestChest* chests;
extern Coordinates temp;
extern int shopStage, dungeType;
extern int enemyCounter;
bool movePlayer(char** map, Player& player, Coordinates move);