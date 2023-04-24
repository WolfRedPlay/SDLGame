#pragma once
#include "Drawer.h"
#include "Phrases.h"

extern void DeInit(int error);
extern int qountOfQusts;
extern Quest* questsList;


void NPCDialog(NPC npc);
void QuestDialog(QuestNPC& npc, Player& player);
bool BossDialog(Enemy boss);