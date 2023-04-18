#include "Mover.h"

int tempMoveY1, tempMoveX1;
int tempMoveY2, tempMoveX2;


bool checkForNPCCollision() {
	for (int i = 0; i < NPC_AMOUNT_1; i++) {
		if (NPCs[i].position.X == tempMoveX1 && NPCs[i].position.Y == tempMoveY1) return true;
		if (NPCs[i].position.X == tempMoveX2 && NPCs[i].position.Y == tempMoveY1) return true;
		if (NPCs[i].position.X == tempMoveX1 && NPCs[i].position.Y == tempMoveY2) return true;
	}
	return false;
}
bool checkForQuestNPCCollision() {
	for (int i = 0; i < QUEST_NPC_AMOUNT_1; i++) {
		if (questNPCs[i].position.X == tempMoveX1 && questNPCs[i].position.Y == tempMoveY1) return true;
		if (questNPCs[i].position.X == tempMoveX2 && questNPCs[i].position.Y == tempMoveY1) return true;
		if (questNPCs[i].position.X == tempMoveX1 && questNPCs[i].position.Y == tempMoveY2) return true;
	}
	return false;
}
bool checkForBossCollision() {
	for (int i = 0; i < BOSSES_AMOUNT_1; i++) {
		if (bosses[i].position.X == tempMoveX1 && bosses[i].position.Y == tempMoveY1) return true;
		if (bosses[i].position.X == tempMoveX2 && bosses[i].position.Y == tempMoveY1) return true;
		if (bosses[i].position.X == tempMoveX1 && bosses[i].position.Y == tempMoveY2) return true;
	}
	return false;
}
bool checkForChestCollision() {
	for (int i = 0; i < CHESTS_AMOUNT_1; i++) {
		if (chests[i].position.X == tempMoveX1 && chests[i].position.Y == tempMoveY1) return true;
		if (chests[i].position.X == tempMoveX2 && chests[i].position.Y == tempMoveY1) return true;
		if (chests[i].position.X == tempMoveX1 && chests[i].position.Y == tempMoveY2) return true;
	}
	return false;
}




bool movePlayer(char** map, Player& player, Coordinates move) {

	float tempY, tempX;

	tempX = (float(nearbyint((player.position.X + move.X) * 100))) / 100;
	tempY = (float(nearbyint((player.position.Y + move.Y) * 100))) / 100;



	if (move.X < 0) tempMoveX1 = int(floorf(tempX));
	if (move.X == 0) {
		tempMoveX1 = int(floorf(tempX + 0.2f));
		tempMoveX2 = int(ceilf(tempX - 0.2f));
	}
	if (move.X > 0) tempMoveX1 = int(ceilf(tempX));
	if (move.Y < 0) tempMoveY1 = int(floorf(tempY));
	if (move.Y == 0) {
		tempMoveY1 = int(floorf(tempY + 0.2f));
		tempMoveY2 = int(ceilf(tempY - 0.2f));
	}
	if (move.Y > 0) tempMoveY1 = int(ceilf(tempY));
	if (move.X == 0)
	{
		if (map[tempMoveY1][tempMoveX1] == SHOP || map[tempMoveY1][tempMoveX2] == SHOP && inGlobal) {

			/*if (player.position.Y == 5 && player.position.X == 47) shopStage = 1;
			if (player.position.Y == 2 && player.position.X == 196) shopStage = 2;*/

			inShop = true;
			inGlobal = false;
			temp = player.position;
			player.position = { 12, 9 };
			return true;
		}
		if (map[tempMoveY1][tempMoveX1] == DOOR || map[tempMoveY1][tempMoveX2] == DOOR) {
			if (player.keys >= 1) {
				if (map[tempMoveY1][tempMoveX1] == DOOR) deleteObject(map, tempMoveX1, tempMoveY1);
				if (map[tempMoveY1][tempMoveX2] == DOOR) deleteObject(map, tempMoveX2, tempMoveY1);
				player.keys--;
			}
			else return false;
		}
		if (checkForNPCCollision()) return false;
		if (checkForQuestNPCCollision()) return false;
		if (checkForBossCollision()) return false;
		if (checkForChestCollision()) return false;
		if (map[tempMoveY1][tempMoveX1] == WOODEN_WALL || map[tempMoveY1][tempMoveX2] == WOODEN_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == STONE_WALL || map[tempMoveY1][tempMoveX2] == STONE_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == WEAPON_SELLER || map[tempMoveY1][tempMoveX2] == WEAPON_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == POTION_SELLER || map[tempMoveY1][tempMoveX2] == POTION_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ARMOR_SELLER || map[tempMoveY1][tempMoveX2] == ARMOR_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ABILITIES_SELLER || map[tempMoveY1][tempMoveX2] == ABILITIES_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == INKEEPER || map[tempMoveY1][tempMoveX2] == INKEEPER) return false;
		if (map[tempMoveY1][tempMoveX1] == CHEST || map[tempMoveY1][tempMoveX2] == CHEST) return false;
		if (map[tempMoveY1][tempMoveX1] == PUZZLE_MAN || map[tempMoveY1][tempMoveX2] == PUZZLE_MAN) return false;
		if (map[tempMoveY1][tempMoveX1] == KEY || map[tempMoveY1][tempMoveX2] == KEY) {
			if (map[tempMoveY1][tempMoveX1] == KEY) deleteObject(map, tempMoveX1, tempMoveY1);
			if (map[tempMoveY1][tempMoveX2] == KEY) deleteObject(map, tempMoveX2, tempMoveY1);
			player.keys++;
		}
	}
	if (move.Y == 0)
	{
		if (map[tempMoveY1][tempMoveX1] == SHOP || map[tempMoveY2][tempMoveX1] == SHOP && inGlobal) {

			/*if (player.position.Y == 5 && player.position.X == 47) shopStage = 1;
			if (player.position.Y == 2 && player.position.X == 196) shopStage = 2;*/

			inShop = true;
			inGlobal = false;
			temp = player.position;
			player.position = { 12, 9 };
			return true;
		}
		if (map[tempMoveY1][tempMoveX1] == DOOR || map[tempMoveY2][tempMoveX1] == DOOR) {
			if (player.keys >= 1) {
				if (map[tempMoveY1][tempMoveX1] == DOOR) deleteObject(map, tempMoveX1, tempMoveY1);
				if (map[tempMoveY2][tempMoveX1] == DOOR) deleteObject(map, tempMoveX1, tempMoveY2);
				player.keys--;
			}
			else return false;
		}
		if (checkForNPCCollision()) return false;
		if (checkForQuestNPCCollision()) return false;
		if (checkForBossCollision()) return false;
		if (checkForChestCollision()) return false;
		if (map[tempMoveY1][tempMoveX1] == WOODEN_WALL || map[tempMoveY2][tempMoveX1] == WOODEN_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == STONE_WALL || map[tempMoveY2][tempMoveX1] == STONE_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == WEAPON_SELLER || map[tempMoveY2][tempMoveX1] == WEAPON_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == POTION_SELLER || map[tempMoveY2][tempMoveX1] == POTION_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ARMOR_SELLER || map[tempMoveY2][tempMoveX1] == ARMOR_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ABILITIES_SELLER || map[tempMoveY2][tempMoveX1] == ABILITIES_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == INKEEPER || map[tempMoveY2][tempMoveX1] == INKEEPER) return false;
		if (map[tempMoveY1][tempMoveX1] == CHEST || map[tempMoveY2][tempMoveX1] == CHEST) return false;
		if (map[tempMoveY1][tempMoveX1] == PUZZLE_MAN || map[tempMoveY2][tempMoveX1] == PUZZLE_MAN) return false;
		if (map[tempMoveY1][tempMoveX1] == KEY || map[tempMoveY2][tempMoveX1] == KEY) {
			if (map[tempMoveY1][tempMoveX1] == KEY) deleteObject(map, tempMoveX1, tempMoveY1);
			if (map[tempMoveY2][tempMoveX1] == KEY) deleteObject(map, tempMoveX1, tempMoveY2);
			player.keys++;
		}
	}

	if (inShop) {
		if (player.position.Y > 9) {
			inShop = false;
			inDunge = false;
			inGlobal = true;
			player.position.X = temp.X - 1;
			player.position.Y = temp.Y;
			temp = { 0,0 };
			shopStage = 0;
			dungeType = 0;

		}

	}



	player.position.X = (float(nearbyint((player.position.X + move.X) * 100))) / 100;
	player.position.Y = (float(nearbyint((player.position.Y + move.Y) * 100))) / 100;
	return true;
}