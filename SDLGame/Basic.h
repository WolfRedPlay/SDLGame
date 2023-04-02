#pragma once
#include <iostream>
#include <Windows.h>
#include <SDL.h>

#define UNIT_SIZE 30

#define WINDOW_WIDTH 1920 
#define WINDOW_HEIGHT 1080

#define MAP_SIZE_X 401
#define MAP_SIZE_Y 100


#define SCREEN_SIZE_X WINDOW_WIDTH/UNIT_SIZE
#define SCREEN_SIZE_Y WINDOW_HEIGHT/UNIT_SIZE

enum Symbols {
	WALL = '#',
	SHOP = 'S',
	DUNGE = '0',
	LOCATION = 'O',
	WEAPON_SELLER = 'W',
	ARMOR_SELLER = 'A',
	POTION_SELLER = 'P',
	ABILITIES_SELLER = 'M',
	NPC = 'N',
	NPC_QUEST = 'Q',
	INKEEPER = 'I',
	DUNGE_BOSS = 'B',
	BANDITS_LEADER = 'L',
	KEY = 'K',
	DOOR = 'D',
	CHEST = 'C',
	QUEST_CHEST = 'G',
	PUZZLE_MAN = '?'

};


struct Coordinates {
	float X, Y;
};


struct Player {
	int money;
	int keys;
	Coordinates position;
	/*Weapon weapons[MAX_PLAYER_INVENTORY_SIZE];
	Armor armors[MAX_PLAYER_INVENTORY_SIZE];
	Potion potions[MAX_PLAYER_INVENTORY_SIZE];
	QuestItem questItems[MAX_PLAYER_INVENTORY_SIZE];
	Quest quests[MAX_QUESTS];
	Hero team[4];*/
	int currentLocation;
};



void readMap(char** map, const char* fileName, int size_x, int size_y);