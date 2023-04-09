#pragma once
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


extern SDL_Renderer* ren;
extern int window_width;
extern int window_height;

#define UNIT_SIZE_X 40 //(window_width/48) //40
#define UNIT_SIZE_Y 40 //(window_height/20) //54



#define MAP_SIZE_X 401
#define MAP_SIZE_Y 100

#define SHOP_MAP_SIZE_X 27
#define SHOP_MAP_SIZE_Y 11

#define DUNGE_MAP_SIZE_X 181
#define DUNGE_MAP_SIZE_Y 60

#define SCREEN_SIZE_X window_width/UNIT_SIZE_X
#define SCREEN_SIZE_Y window_height/UNIT_SIZE_Y


#define MAX_NAME_LENGTH 15

#define MAX_PLAYER_INVENTORY_SIZE 10
#define MAX_INVENTORY_SIZE 20
#define MAX_ABILITIES 8
#define MAX_QUESTS 5


#define KNIGHT 90
#define ROGUE 91
#define MAGE 92
#define HEALER 93

enum Diractions {
	UP,
	DOWN,
	LEFT,
	RIGHT
};


enum Symbols {
	WOODEN_WALL = '#',
	STONE_WALL = '\[',
	EMPTY = ' ',
	GRASS = '.',
	WOOD = ',',
	SHOP = 'S',
	DUNGE = '0',  //
	LOCATION = 'O',//
	WEAPON_SELLER = 'W',
	ARMOR_SELLER = 'A',
	POTION_SELLER = 'P',
	ABILITIES_SELLER = 'M',
	NPC = 'N',
	NPC_QUEST = 'Q',
	INKEEPER = 'I',
	DUNGE_BOSS = 'B',//
	BANDITS_LEADER = 'L',//
	KEY = 'K',
	DOOR = 'D',
	CHEST = 'C',
	QUEST_CHEST = 'G',
	PUZZLE_MAN = '?'//

};

enum AbilityTypes {
	ATTACKING,
	BUFFING
};
enum Statuses {
	NORMAL,
	DEAD,
	ESCAPED,
	STUNED,
	BURN,
	POISONED,
	MARKED

};
enum CharacteristicsForAbilities {
	HEALTH,
	ARMOR,
	DAMAGE
};

struct Weapon {
	int damage;
	int price;
	char name[MAX_NAME_LENGTH];
	int ID;

};

struct Armor {
	int armor;
	int price;
	char name[MAX_NAME_LENGTH];
	int ID;

};

struct Potion {
	int health;
	int mana;
	int price;
	char name[MAX_NAME_LENGTH];
	int ID;

};

struct Ability {
	char name[MAX_NAME_LENGTH];
	int type;
	int damage;
	int manaCost;
	int staminaCost;
	int cooldown;
	int ID;
	int price;
	int effect;
	int buffedCharacteristic;
	int buff;
	int duration;
	bool aoe;
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
	Weapon equipedWeapon;
	Armor equipedArmor;
	Ability abilities[MAX_ABILITIES];
	int lvl;
	int exp;
	SDL_Texture* texture;
};

struct Player {
	int money;
	int keys;
	Coordinates position;
	int diraction;
	Weapon weapons[MAX_PLAYER_INVENTORY_SIZE];
	Armor armors[MAX_PLAYER_INVENTORY_SIZE];
	Potion potions[MAX_PLAYER_INVENTORY_SIZE];
	/*QuestItem questItems[MAX_PLAYER_INVENTORY_SIZE];
	Quest quests[MAX_QUESTS];*/
	Hero team[4];
	int currentLocation;
};

struct Enemy {
	int health;
	int damage;
	int armor;
	int ID;
	int moneyDrop;
	int expDrop;
	int IDweaponDrop;
	int IDarmorDrop;
	int IDpotionDrop;
	char name[MAX_NAME_LENGTH];
	int status;
	Ability ability;
	int mana;
	int stamina;
	int lvl;
	SDL_Texture* texture;
};

struct EnemiesSquad {
	Enemy enemies[4];
};

struct SellerOfWeapons {

	Weapon weapons[MAX_INVENTORY_SIZE];

};
struct SellerOfArmors {

	Armor armors[MAX_INVENTORY_SIZE];

};
struct SellerOfPotions {

	Potion potions[MAX_INVENTORY_SIZE];

};
struct SellerOfAbilities {

	Ability abilities[MAX_ABILITIES];

};

int random(int min, int max);

SDL_Texture* generateTextureFromPNG(const char* file);

void readMap(char** map, const char* fileName, int size_x, int size_y);

void deleteObject(char** map, int x, int y);

void clearWeaponInventory(Weapon* weapons);
void clearArmorInventory(Armor* armors);
void clearPotionInventory(Potion* potions);
void clearAbilities(Ability* abilities);
void clearPlayer(Player& player);



Weapon findInWeaponsList(Weapon* ALLWeaopnsList, int ID, int numWeapons);
Armor findInArmorsList(Armor* ALLArmorsList, int ID, int numArmors);
Potion findInPotionsList(Potion* ALLPotionsList, int ID, int numPotions);
Ability findInAbilitiesList(Ability* ALLAbilitiesList, int ID, int numAbilities);

Weapon* createAllWeapons(int& amount);
Armor* createAllArmors(int& amount);
Potion* createAllPotions(int& amount);
Ability* createAllAbilities(int& amount);
Enemy* createAllEnemies(int& amount);


bool addWeaponToInventory(Weapon weapon, Weapon* weapons);
bool addArmorToInventory(Armor armor, Armor* armors);
bool addPotionToInventory(Potion potion, Potion* potions);
bool addAbilityToAbilities(Ability ability, Ability* abilities);

Weapon takeWeaponFromInventory(Weapon* weapons, int itemIndex);
Armor takeArmorFromInventory(Armor* armors, int itemIndex);
Potion takePotionFromInventory(Potion* potions, int itemIndex);
Ability takeAbilityFromList(Ability* abilities, int abilityIndex);