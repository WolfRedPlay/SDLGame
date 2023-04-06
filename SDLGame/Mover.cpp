#include "Mover.h"

bool movePlayer(char** map, Player& player, Coordinates move) {

	int tempMoveY1, tempMoveX1;
	int tempMoveY2, tempMoveX2;
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
				if (map[tempMoveY1][tempMoveX1] == DOOR) map[tempMoveY1][tempMoveX1] = map[tempMoveY1 - 1][tempMoveX1];
				if (map[tempMoveY1][tempMoveX2] == DOOR) map[tempMoveY1][tempMoveX2] = map[tempMoveY1 - 1][tempMoveX2];
				player.keys--;
			}
			else return false;
		}
		if (map[tempMoveY1][tempMoveX1] == WOODEN_WALL || map[tempMoveY1][tempMoveX2] == WOODEN_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == STONE_WALL || map[tempMoveY1][tempMoveX2] == STONE_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == WEAPON_SELLER || map[tempMoveY1][tempMoveX2] == WEAPON_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == POTION_SELLER || map[tempMoveY1][tempMoveX2] == POTION_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ARMOR_SELLER || map[tempMoveY1][tempMoveX2] == ARMOR_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ABILITIES_SELLER || map[tempMoveY1][tempMoveX2] == ABILITIES_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == NPC || map[tempMoveY1][tempMoveX2] == NPC) return false;
		if (map[tempMoveY1][tempMoveX1] == NPC_QUEST || map[tempMoveY1][tempMoveX2] == NPC_QUEST) return false;
		if (map[tempMoveY1][tempMoveX1] == INKEEPER || map[tempMoveY1][tempMoveX2] == INKEEPER) return false;
		if (map[tempMoveY1][tempMoveX1] == CHEST || map[tempMoveY1][tempMoveX2] == CHEST) return false;
		if (map[tempMoveY1][tempMoveX1] == QUEST_CHEST || map[tempMoveY1][tempMoveX2] == QUEST_CHEST) return false;
		if (map[tempMoveY1][tempMoveX1] == BANDITS_LEADER || map[tempMoveY1][tempMoveX2] == BANDITS_LEADER) return false;
		if (map[tempMoveY1][tempMoveX1] == PUZZLE_MAN || map[tempMoveY1][tempMoveX2] == PUZZLE_MAN) return false;
		if (map[tempMoveY1][tempMoveX1] == KEY || map[tempMoveY1][tempMoveX2] == KEY) {
			if (map[tempMoveY1][tempMoveX1] == KEY) map[tempMoveY1][tempMoveX1] = map[tempMoveY1][tempMoveX1 - 1];
			if (map[tempMoveY1][tempMoveX2] == KEY) map[tempMoveY1][tempMoveX2] = map[tempMoveY1][tempMoveX2 - 1];
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
				if (map[tempMoveY1][tempMoveX1] == DOOR) map[tempMoveY1][tempMoveX1] = map[tempMoveY1 - 1][tempMoveX1];
				if (map[tempMoveY2][tempMoveX1] == DOOR) map[tempMoveY2][tempMoveX1] = map[tempMoveY2 - 1][tempMoveX1];
				player.keys--;
			}
			else return false;
		}
		if (map[tempMoveY1][tempMoveX1] == WOODEN_WALL || map[tempMoveY2][tempMoveX1] == WOODEN_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == STONE_WALL || map[tempMoveY2][tempMoveX1] == STONE_WALL) return false;
		if (map[tempMoveY1][tempMoveX1] == WEAPON_SELLER || map[tempMoveY2][tempMoveX1] == WEAPON_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == POTION_SELLER || map[tempMoveY2][tempMoveX1] == POTION_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ARMOR_SELLER || map[tempMoveY2][tempMoveX1] == ARMOR_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == ABILITIES_SELLER || map[tempMoveY2][tempMoveX1] == ABILITIES_SELLER) return false;
		if (map[tempMoveY1][tempMoveX1] == NPC || map[tempMoveY2][tempMoveX1] == NPC) return false;
		if (map[tempMoveY1][tempMoveX1] == NPC_QUEST || map[tempMoveY2][tempMoveX1] == NPC_QUEST) return false;
		if (map[tempMoveY1][tempMoveX1] == INKEEPER || map[tempMoveY2][tempMoveX1] == INKEEPER) return false;
		if (map[tempMoveY1][tempMoveX1] == CHEST || map[tempMoveY2][tempMoveX1] == CHEST) return false;
		if (map[tempMoveY1][tempMoveX1] == QUEST_CHEST || map[tempMoveY2][tempMoveX1] == QUEST_CHEST) return false;
		if (map[tempMoveY1][tempMoveX1] == BANDITS_LEADER || map[tempMoveY2][tempMoveX1] == BANDITS_LEADER) return false;
		if (map[tempMoveY1][tempMoveX1] == PUZZLE_MAN || map[tempMoveY2][tempMoveX1] == PUZZLE_MAN) return false;
		if (map[tempMoveY1][tempMoveX1] == KEY || map[tempMoveY2][tempMoveX1] == KEY) {
			if (map[tempMoveY1][tempMoveX1] == KEY) map[tempMoveY2][tempMoveX1] = map[tempMoveY2][tempMoveX1 - 1];
			if (map[tempMoveY1][tempMoveX1] == KEY) map[tempMoveY2][tempMoveX1] = map[tempMoveY2][tempMoveX1 - 1];
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