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


void inkeeper(Player& player, char** map) {
	int choice, heroChoice;
	short coursorPosition;
	int priceForRestore = 10, priceForRevive = 50;

	bool inMenu = true, inHeroChoosing = false, choosen = false;

	SDL_Event ev;

	while (true) {
		coursorPosition = 0;
		while (inMenu) {
			while (SDL_PollEvent(&ev))
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;
				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_UP:
						if (coursorPosition != 0) coursorPosition--;
						break;
					case SDL_SCANCODE_DOWN:
						if (coursorPosition != 1) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						inMenu = false;
						break;
					case SDL_SCANCODE_ESCAPE:
						return;
					}
					break;
				}


			drawInkeeperDialog(priceForRestore, priceForRevive,player.money, coursorPosition);

		}





		if (choice == 0) {
			if (player.money >= priceForRestore) {
				if (player.team[0].health != player.team[0].maxHealth && player.team[1].health != player.team[1].maxHealth
					&& player.team[2].health != player.team[2].maxHealth && player.team[3].health != player.team[1].maxHealth)
				{
					player.money -= priceForRestore;
					for (int i = 0; i < 4; i++)
						player.team[i].health = player.team[i].maxHealth;
				}
				else {
					drawInkeeperReject();
				}

			}
			else {
				//звук неудачной покупки
			}
			inMenu = true;
		}
		if (choice == 1) {
			if (player.money >= priceForRevive) {
				coursorPosition = 0;
				inHeroChoosing = true;
				choosen = false;
				while (inHeroChoosing) {
					while (SDL_PollEvent(&ev))
						switch (ev.type) {
						case SDL_QUIT:
							DeInit(0);
							break;
						case SDL_KEYDOWN:
							switch (ev.key.keysym.scancode) {
							case SDL_SCANCODE_LEFT:
								if (coursorPosition != 0) coursorPosition--;
								break;
							case SDL_SCANCODE_RIGHT:
								if (coursorPosition != 3) coursorPosition++;
								break;
							case SDL_SCANCODE_RETURN:
								heroChoice = coursorPosition;
								if (player.team[heroChoice].status == DEAD)
								{
									choosen = true;
									inHeroChoosing = false;
								}
								else {
									drawInkeeperReject();
									drawInkeeperDialog(priceForRestore, priceForRevive, player.money, 2);
								}
								break;
							case SDL_SCANCODE_ESCAPE:
								inHeroChoosing = false;
								choosen = false;
								inMenu = true;
								drawScreen(map, player.position);
								drawPlayer(player.position, player.diraction, 0);
								break;
							}
							break;
						}


					if (inHeroChoosing) drawHeroChoice(player, coursorPosition);

				}

				if (choosen) {
					player.money -= priceForRevive;
					player.team[heroChoice].health = 5;
					player.team[heroChoice].status = NORMAL;
				}
			}
			else {
				//звук неудачной покупки
			}
		}


	}
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
		if (map[tempY1][tempX1] == INKEEPER || map[tempY1][tempX2] == INKEEPER) inkeeper(player, map);
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
		if (map[tempY1][tempX1] == INKEEPER || map[tempY2][tempX1] == INKEEPER) inkeeper(player, map);
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
		if (map[tempY1][tempX1] == INKEEPER || map[tempY2][tempX1] == INKEEPER) inkeeper(player, map);
		if (map[tempY1][tempX1] == CHEST || map[tempY2][tempX1] == CHEST) {
			openChest(player);
			if (map[tempY1][tempX1] == CHEST) deleteObject(map, tempX1, tempY1);
			if (map[tempY2][tempX1] == CHEST) deleteObject(map, tempX1, tempY2);

		}



	}



}