#include "Interactions.h"





void openChest(Player& player) {
	Weapon givedWeapon;
	Armor givedArmor;
	Potion givedPotion;
	givedWeapon.ID = 0;
	givedArmor.ID = 0;
	givedPotion.ID = 0;
	int randomNum = 0;
	int maxID;
	int minID;
	if ((rand() % (10 - 1 + 1) + 1) > 5) {
		maxID = -100;
		minID = -103;
		randomNum = rand() % (maxID - minID + 1) + minID;
		givedWeapon = findInWeaponsList(ALLWeaponsList, randomNum, qountOfWeapons);
		addWeaponToInventory(givedWeapon, player.weapons);
	}
	if ((rand() % (10 - 1 + 1) + 1) > 5) {
		maxID = -200;
		minID = -202;
		randomNum = rand() % (maxID - minID + 1) + minID;
		givedArmor = findInArmorsList(ALLArmorsList, randomNum, qountOfArmors);
		addArmorToInventory(givedArmor, player.armors);
	}
	if ((rand() % (10 - 1 + 1) + 1) > 5) {
		maxID = -300;
		minID = -305;
		randomNum = rand() % (maxID - minID + 1) + minID;
		givedPotion = findInPotionsList(ALLPotionsList, randomNum, qountOfPotions);
		addPotionToInventory(givedPotion, player.potions);
	}
	int givedMoney = rand() % (100 - 0 + 1) + 0;
	player.money += givedMoney;
	drawChestOpenning(givedWeapon, givedArmor, givedPotion, givedMoney);
}




void interact(char** map, Player& player) {


	int tempX1 = 0, tempX2 = 0;
	int tempY1 = 0, tempY2 = 0;
	if (player.diraction == UP) {
		tempY1 = floorf(player.position.Y) - 1;
		tempX1 = floorf(player.position.X);
		tempX2 = ceilf(player.position.X);

		if (map[tempY1][tempX1] == NPC || map[tempY1][tempX2] == NPC) player.position.Y += 5;
		if (map[tempY1][tempX1] == WEAPON_SELLER || map[tempY1][tempX2] == WEAPON_SELLER) weaponSeller(player, 1, map);
		if (map[tempY1][tempX1] == ARMOR_SELLER || map[tempY1][tempX2] == ARMOR_SELLER) armorSeller(player, 1, map);
		if (map[tempY1][tempX1] == POTION_SELLER || map[tempY1][tempX2] == POTION_SELLER) potionSeller(player, 1, map);
		if (map[tempY1][tempX1] == ABILITIES_SELLER || map[tempY1][tempX2] == ABILITIES_SELLER) abilitySeller(player, 1, map);
		if (map[tempY1][tempX1] == CHEST || map[tempY1][tempX2] == CHEST) {
			openChest(player);
			if (map[tempY1][tempX1] == CHEST) deleteObject(map, tempX1, tempY1);
			if (map[tempY1][tempX2] == CHEST)  deleteObject(map, tempX2, tempY1);
		}
	}
	if (player.diraction == LEFT) {
		tempX1 = floorf(player.position.X) - 1;
		tempY1 = floorf(player.position.Y);
		tempY2 = ceilf(player.position.Y);

		if (map[tempY1][tempX1] == NPC || map[tempY2][tempX1] == NPC) player.position.X += 5;
		if (map[tempY1][tempX1] == WEAPON_SELLER || map[tempY2][tempX1] == WEAPON_SELLER) weaponSeller(player, 1, map);
		if (map[tempY1][tempX1] == ARMOR_SELLER || map[tempY2][tempX1] == ARMOR_SELLER) armorSeller(player, 1, map);
		if (map[tempY1][tempX1] == POTION_SELLER || map[tempY2][tempX1] == POTION_SELLER) potionSeller(player, 1, map);
		if (map[tempY1][tempX1] == ABILITIES_SELLER || map[tempY2][tempX1] == ABILITIES_SELLER) abilitySeller(player, 1, map);
		if (map[tempY1][tempX1] == CHEST || map[tempY2][tempX1] == CHEST) {
			openChest(player);
			if (map[tempY1][tempX1] == CHEST) deleteObject(map, tempX1, tempY1);
			if (map[tempY2][tempX1] == CHEST) deleteObject(map, tempX1, tempY2);

		}

	}
	if (player.diraction == RIGHT) {
		tempX1 = floorf(player.position.X) + 1;
		tempY1 = floorf(player.position.Y);
		tempY2 = ceilf(player.position.Y);

		if (map[tempY1][tempX1] == NPC || map[tempY2][tempX1] == NPC) player.position.X += 5;
		if (map[tempY1][tempX1] == WEAPON_SELLER || map[tempY2][tempX1] == WEAPON_SELLER) weaponSeller(player, 1, map);
		if (map[tempY1][tempX1] == ARMOR_SELLER || map[tempY2][tempX1] == ARMOR_SELLER) armorSeller(player, 1, map);
		if (map[tempY1][tempX1] == POTION_SELLER || map[tempY2][tempX1] == POTION_SELLER) potionSeller(player, 1, map);
		if (map[tempY1][tempX1] == ABILITIES_SELLER || map[tempY2][tempX1] == ABILITIES_SELLER) abilitySeller(player, 1, map);
		if (map[tempY1][tempX1] == CHEST || map[tempY2][tempX1] == CHEST) {
			openChest(player);
			if (map[tempY1][tempX1] == CHEST) deleteObject(map, tempX1, tempY1);
			if (map[tempY2][tempX1] == CHEST) deleteObject(map, tempX1, tempY2);

		}



	}



}