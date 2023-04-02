#pragma once
#include <iostream>
#include <Windows.h>
#include <SDL.h>

#define UNIT_SIZE 30

#define MAX_NAME_LENGTH 15

#define WINDOW_WIDTH 1920 
#define WINDOW_HEIGHT 1080

#define MAP_SIZE_X 401
#define MAP_SIZE_Y 100


#define SCREEN_SIZE_X WINDOW_WIDTH/UNIT_SIZE
#define SCREEN_SIZE_Y WINDOW_HEIGHT/UNIT_SIZE

#define KNIGHT 90
#define ROGUE 91
#define MAGE 92
#define HEALER 93

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

struct Hero {
	char name[MAX_NAME_LENGTH];
	int heroClass;
	int health;
	int maxHealth;
	int damage;
	int armor;
	int mana;
	int maxMana;
	int stamina;
	int maxStamina;
	int status;
	/*Weapon equipedWeapon;
	Armor equipedArmor;
	Ability abilities[MAX_ABILITIES];*/
	int lvl;
	int exp;
};

struct Player {
	int money;
	int keys;
	Coordinates position;
	/*Weapon weapons[MAX_PLAYER_INVENTORY_SIZE];
	Armor armors[MAX_PLAYER_INVENTORY_SIZE];
	Potion potions[MAX_PLAYER_INVENTORY_SIZE];
	QuestItem questItems[MAX_PLAYER_INVENTORY_SIZE];
	Quest quests[MAX_QUESTS];*/
	Hero team[4];
	int currentLocation;
};



void readMap(char** map, const char* fileName, int size_x, int size_y);