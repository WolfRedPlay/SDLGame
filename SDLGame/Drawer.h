#pragma once
#include "Basic.h"
#include "Phrases.h"



extern SDL_Renderer* ren;

extern int window_width;
extern int window_height;

extern bool isMoving;
extern int mapSizeX, mapSizeY;

extern int qountOfQusts;
extern Quest* questsList;

extern char** map;

extern bool inGlobal;


void drawScreen(Coordinates playerPos);
void drawPlayer(Coordinates playerPosition, int diraction, int frame);
void drawNPCs(NPC* npcs, Player players);
void drawQuestNPCs(QuestNPC* NPCs, Player player);
void drawBosses(Enemy* bosses, Player player);
void drawChests(QuestChest* chests, Player player);

void drawChestOpenning(Weapon givedWeapon, Armor givedArmor, Potion givedPotion, int givedMoney);
void drawChestOpenning(Weapon givedWeapon, Armor givedArmor, Potion givedPotion, int givedMoney, QuestItem item);

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
void drawQuestsList(Player player);
void drawQuestItems(Player player, int coursorPosition);


void drawSeller(int typeOfSeller, int coursorPosition);

void drawSellerChoice(int coins, SellerOfWeapons seller, int coursorPosition);
void drawSellerChoice(int coins, SellerOfArmors seller, int coursorPosition);
void drawSellerChoice(int coins, SellerOfPotions seller, int coursorPosition);
void drawSellerChoice(int coins, SellerOfAbilities seller, int coursorPosition);


void drawInkeeperDialog(int restorePrice, int revivePrice, int money, int coursorPosition);
void drawInkeeperReject();


void drawFightingScene(Player player,EnemiesSquad enemies, int coursorPosition, int type);
void drawFightingScene(Player player, Enemy boss, int coursorPosition, int type);

void attackAnimation(Player player, EnemiesSquad enemies, int attacker, int defender);

void drawNPCDialogWindow(NPC npc);
void drawQuestDialogWindow(QuestNPC npc, int dialogeStage, int coursorPosition);
void drawBanditLeaderDialogWindow(Enemy boss, int dialogeStage, int coursorPosition);