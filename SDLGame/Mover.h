#pragma once
#include "Basic.h"
#include <math.h>

extern bool inShop, inDunge, inGlobal,
shopMapReaded, dungeMapReaded, globalMapReaded;
extern NPC* NPCs;
extern QuestNPC* questNPCs;
extern Coordinates temp;
extern int shopStage, dungeType;
bool movePlayer(char** map, Player& player, Coordinates move);