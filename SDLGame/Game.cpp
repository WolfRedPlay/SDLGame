#include "Basic.h"
#include "Drawer.h"
#include "Mover.h"
#include "Menues.h"
#include "Interactions.h"
#include "Fighting.h"

#include <ctime>


float speed = 2.f;

#define MAX_ENEMY_COUNTER 100000
#define MIN_ENEMY_COUNTER 50000

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int window_width = 1920;
int window_height = 1080;

char** map;

int enemyCounter = 0;

bool inGame = false;

int mapSizeX, mapSizeY;

bool inShop, inDunge, inGlobal,
shopMapReaded, dungeMapReaded, globalMapReaded,
isMoving;



Coordinates temp = { 0.f,0.f };

NPC* NPCs;
QuestNPC* questNPCs;
Enemy* bosses;
QuestChest* chests;

int shopStage = 0, dungeType = 1;

int qountOfWeapons;
int qountOfArmors;
int qountOfPotions;
int qountOfAbilities;
int qountOfQusts;
//int qountOfQustItems;
Weapon* ALLWeaponsList = createAllWeapons(qountOfWeapons);
Armor* ALLArmorsList = createAllArmors(qountOfArmors);
Potion* ALLPotionsList = createAllPotions(qountOfPotions);
Ability* ALLAbilitiesList = createAllAbilities(qountOfAbilities);
Quest* questsList = createAllQuests(qountOfQusts);
//QuestItem* ALLQuestItemsList = createAllQuestItems(qountOfQustItems);



void DeInit(int error) {
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error);
}

void Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf_s("Error: %s!", SDL_GetError());
		DeInit(1);
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
		printf_s("Error: %s!", SDL_GetError());
		DeInit(1);
	}
	if (TTF_Init() != 0) {
		printf_s("Error: %s!", SDL_GetError());
		DeInit(1);
	}
	win = SDL_CreateWindow("Just Window", 0, 0, window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL) {
		printf_s("Create window error: %s!", SDL_GetError());
		DeInit(1);
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if (ren == NULL) {
		printf_s("Create render error: %s!", SDL_GetError());
		DeInit(1);
	}
}


char** createMapArray(int size_x, int size_y) {
	char** map = (char**)malloc(size_y * sizeof(char*));
	for (int i = 0; i < size_y; i++)
		map[i] = (char*)malloc(size_x * sizeof(char));

	mapSizeX = size_x;
	mapSizeY = size_y;
	return map;
}



int main(int argc, char* argv[]) {

	srand(time(NULL));
	const Uint8* state = SDL_GetKeyboardState(NULL);
	int frame = 0;
	int framCount = 4;
	int current_frametime = 0;
	int max_frametime = 1000 / 4;



	bool enemyCounterRandomed = false; int startFight = 0;

	map = createMapArray(MAP_SIZE_X, MAP_SIZE_Y);
	SDL_Event ev;
	Player player;
	Init();

	int dt = 0;
	int lasttime = SDL_GetTicks();
	int newtime;



	while (true) {
		inShop = false;
		inDunge = false;
		inGlobal = true;
		shopMapReaded = false;
		dungeMapReaded = false;
		globalMapReaded = false;
		startMenu(player, map);
		NPCs = createNPCs();
		questNPCs = createQuestNPCs();
		bosses = createBosses();
		chests = createChests();
		while (inGame) {

			while (SDL_PollEvent(&ev)) {
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;
				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_ESCAPE:
						gameMenu(player, map);
						break;
					case SDL_SCANCODE_TAB:
						playerMenu(player);
						break;

					case SDL_SCANCODE_E:
						interact(map, player);
						break;
					}
					break;

				}
			}

			newtime = SDL_GetTicks();
			dt = newtime - lasttime;
			lasttime = newtime;


			isMoving = false;

			if (state[SDL_SCANCODE_LSHIFT]) {
				speed = 4.f;
				max_frametime = 1000 / 6;
			}
			if (!state[SDL_SCANCODE_LSHIFT]) {
				speed = 2.f;
				max_frametime = 1000 / 4;
			}
			if (state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]) {
				if (movePlayer(map, player, { 0, -speed * dt / 1000 }) && !inShop) enemyCounter++;
				player.diraction = UP;
				isMoving = true;
			}
			if (!state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN]) {
				if (movePlayer(map, player, { 0,  speed * dt / 1000 }) && !inShop) enemyCounter++;
				player.diraction = DOWN;
				isMoving = true;
			}
			if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
			{
				if (movePlayer(map, player, { -speed * dt / 1000, 0 }) && !inShop) enemyCounter++;
				player.diraction = LEFT;
				isMoving = true;
			}
			if (!state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT]) {
				if (movePlayer(map, player, { speed * dt / 1000, 0 }) && !inShop) enemyCounter++;
				player.diraction = RIGHT;
				isMoving = true;
			}

			if (isMoving) {
				current_frametime += dt;
				if (current_frametime >= max_frametime) {
					current_frametime -= max_frametime;
					frame = (frame + 1) % framCount;
				}
			}
			else frame = 0;




			if (inShop) {
				if (!shopMapReaded) {
					setMapSaves("Maps\\SavedMap.txt", map);
					map = createMapArray(SHOP_MAP_SIZE_X, SHOP_MAP_SIZE_Y);
					readMap(map, "Maps\\Shop.txt", SHOP_MAP_SIZE_X, SHOP_MAP_SIZE_Y);
					globalMapReaded = false;
					dungeMapReaded = false;
					shopMapReaded = true;
				}
			}
			else if (inDunge) {
				if (!dungeMapReaded) {
					setMapSaves("Maps\\SavedMap.txt", map);
					map = createMapArray(DUNGE_MAP_SIZE_X, DUNGE_MAP_SIZE_Y);
					if (dungeType == 1)readMap(map, "Maps\\Dunge1.txt", DUNGE_MAP_SIZE_X, DUNGE_MAP_SIZE_Y);
					if (dungeType == 2)readMap(map, "Maps\\Dunge2.txt", DUNGE_MAP_SIZE_X, DUNGE_MAP_SIZE_Y);
					globalMapReaded = false;
					shopMapReaded = false;
					dungeMapReaded = true;
				}
			}
			else if (inGlobal) {
				if (!globalMapReaded) {
					map = createMapArray(MAP_SIZE_X, MAP_SIZE_Y);
					readMap(map, "Maps\\SavedMap.txt", MAP_SIZE_X, MAP_SIZE_Y);
					shopMapReaded = false;
					dungeMapReaded = false;
					globalMapReaded = true;
				}
			}

			if (!enemyCounterRandomed) {
				startFight = random(MIN_ENEMY_COUNTER, MAX_ENEMY_COUNTER);
				enemyCounterRandomed = true;
			}

			if (enemyCounter >= startFight && !inShop) {
				int enemyCount;
				Enemy* enemyList = createAllEnemies(enemyCount);
				int enemyRandNum;
				int maxLvl = 0;
				for (int i = 0; i < 4; i++)
					if (player.team[i].lvl >= maxLvl) maxLvl = player.team[i].lvl;
				EnemiesSquad randomEnemiesSquad;

				int levelDiference = 1;
				if (inDunge) levelDiference = 3;

				do {
					enemyRandNum = random(1, enemyCount);
				} while ((enemyList[enemyRandNum - 1].lvl - maxLvl) > levelDiference);
				randomEnemiesSquad.enemies[0] = enemyList[enemyRandNum - 1];
				do {
					enemyRandNum = random(1, enemyCount);
				} while ((enemyList[enemyRandNum - 1].lvl - maxLvl) > levelDiference);
				randomEnemiesSquad.enemies[1] = enemyList[enemyRandNum - 1];
				do {
					enemyRandNum = random(1, enemyCount);
				} while ((enemyList[enemyRandNum - 1].lvl - maxLvl) > levelDiference);
				randomEnemiesSquad.enemies[2] = enemyList[enemyRandNum - 1];
				do {
					enemyRandNum = random(1, enemyCount);
				} while ((enemyList[enemyRandNum - 1].lvl - maxLvl) > levelDiference);
				randomEnemiesSquad.enemies[3] = enemyList[enemyRandNum - 1];

				startBattle(player, randomEnemiesSquad);

				enemyCounter = 0;
				enemyCounterRandomed = false;
				free(enemyList);
			}




			drawScreen(player.position);
			drawChests(chests, player);
			drawNPCs(NPCs, player);
			drawQuestNPCs(questNPCs, player);
			drawBosses(bosses, player);
			drawPlayer(player.position, player.diraction, frame);

			printf_s("x: %f y: %f \n", player.position.X, player.position.Y);

			SDL_RenderPresent(ren);
		}
	}
	free(NPCs);
	free(map);
	DeInit(0);
	return 0;
}

