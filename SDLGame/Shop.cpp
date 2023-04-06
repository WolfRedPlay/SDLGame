#include "Shop.h"


bool inSeller = true;


void buyWeapon(Player& player, SellerOfWeapons& seller)
{
	int choice = 2, coursorPosition = 0;
	SDL_Event ev;

		if (player.money >= seller.weapons[choice - 1].price)
		{
			Weapon boughtWeapon = takeWeaponFromInventory(seller.weapons, choice - 1);

			if (addWeaponToInventory(boughtWeapon, player.weapons) == true)
			{
				player.money -= boughtWeapon.price;
			}
			else
			{
				addWeaponToInventory(boughtWeapon, seller.weapons);
				printf_s("Not enough place in your inventory");
				Sleep(1000);
			}

		}
		else
		{
			printf("Not enough money");
			Sleep(1000);

		}


}

//void sellWeapon(Player& player, SellerOfWeapons& seller)
//{
//	int choice = 0;
//	int butCode, coursorPosition = 2;
//	do
//	{
//		do {
//			system("cls");
//			drawScreen(screen);
//			drawBar(player);
//			drawPlayerWeaponInventory(player, { 100, 1 });
//			SetConsoleCursorPosition(hConsole, { 99,(short)coursorPosition });
//			printf_s(">");
//
//			butCode = _getch();
//			if (butCode == 224)
//				switch (_getch()) {
//				case UP:
//					if (coursorPosition != 2) coursorPosition--;
//					break;
//				case DOWN:
//					if (coursorPosition != 2 + MAX_PLAYER_INVENTORY_SIZE - 1) coursorPosition++;
//					break;
//				}
//			else {
//				if (butCode == ENTER) {
//					if (coursorPosition == 2) choice = 1;
//					if (coursorPosition == 3) choice = 2;
//					if (coursorPosition == 4) choice = 3;
//					if (coursorPosition == 5) choice = 4;
//					if (coursorPosition == 6) choice = 5;
//					if (coursorPosition == 7) choice = 6;
//					if (coursorPosition == 8) choice = 7;
//					if (coursorPosition == 9) choice = 8;
//					if (coursorPosition == 10) choice = 9;
//					if (coursorPosition == 11) choice = 10;
//					break;
//				}
//				if (butCode == ESC) return;
//			}
//		} while (true);
//
//		Weapon soldWeapon = takeWeaponFromInventory(player.weapons, choice - 1);
//		addWeaponToInventory(soldWeapon, seller.weapons);
//
//		player.money += soldWeapon.price;
//
//	} while (true);
//
//}
//
//void buyArmor(Player& player, SellerOfArmors& seller)
//{
//
//	int choice = 0;
//
//	do
//	{
//		choice = armorBuyChoiceChecker(screen, player, seller);
//
//		if (choice == 0) return;
//
//		if (player.money >= seller.armors[choice - 1].price)
//		{
//			Armor boughtArmor = takeArmorFromInventory(seller.armors, choice - 1);
//
//			if (addArmorToInventory(boughtArmor, player.armors) == true)
//			{
//				player.money -= boughtArmor.price;
//			}
//			else
//			{
//				addArmorToInventory(boughtArmor, seller.armors);
//				printf_s("Not enough place in your inventory");
//			}
//
//		}
//		else
//		{
//			printf("Not enough money");
//
//		}
//
//	} while (true);
//
//}
//
//void sellArmor(Player& player, SellerOfArmors& seller)
//{
//	int butCode, coursorPosition = 2;
//	int choice = 0;
//
//	do {
//		do {
//			system("cls");
//			drawScreen(screen);
//			drawBar(player);
//			drawPlayerArmorInventory(player, { 100, 1 });
//			SetConsoleCursorPosition(hConsole, { 99,(short)coursorPosition });
//			printf_s(">");
//
//			butCode = _getch();
//			if (butCode == 224)
//				switch (_getch()) {
//				case UP:
//					if (coursorPosition != 2) coursorPosition--;
//					break;
//				case DOWN:
//					if (coursorPosition != 2 + MAX_PLAYER_INVENTORY_SIZE - 1) coursorPosition++;
//					break;
//				}
//			else {
//				if (butCode == ENTER) {
//					if (coursorPosition == 2) choice = 1;
//					if (coursorPosition == 3) choice = 2;
//					if (coursorPosition == 4) choice = 3;
//					if (coursorPosition == 5) choice = 4;
//					if (coursorPosition == 6) choice = 5;
//					if (coursorPosition == 7) choice = 6;
//					if (coursorPosition == 8) choice = 7;
//					if (coursorPosition == 9) choice = 8;
//					if (coursorPosition == 10) choice = 9;
//					if (coursorPosition == 11) choice = 10;
//					break;
//				}
//				if (butCode == ESC) return;
//			}
//		} while (true);
//
//		Armor soldArmor = takeArmorFromInventory(player.armors, choice - 1);
//		addArmorToInventory(soldArmor, seller.armors);
//
//		player.money += soldArmor.price;
//
//	} while (true);
//
//}
//
//void buyPotion(Player& player, SellerOfPotions& seller)
//{
//
//	int choice = 0;
//
//	do
//	{
//		choice = potionBuyChoiceChecker(screen, player, seller);
//
//		if (choice == 0) return;
//
//		if (player.money >= seller.potions[choice - 1].price)
//		{
//			Potion boughtPotion = takePotionFromInventory(seller.potions, choice - 1);
//
//			if (addPotionToInventory(boughtPotion, player.potions) == true)
//			{
//				player.money -= boughtPotion.price;
//			}
//			else
//			{
//				addPotionToInventory(boughtPotion, seller.potions);
//				printf_s("Not enough place in your inventory");
//			}
//
//		}
//		else
//		{
//			printf("Not enough money");
//
//		}
//
//	} while (true);
//
//}
//
//void sellPotion(Player& player, SellerOfPotions& seller)
//{
//	int butCode, coursorPosition = 2;
//	int choice = 0;
//
//	do
//	{
//		do {
//			system("cls");
//			drawScreen(screen);
//			drawBar(player);
//			drawPlayerPotionInventory(player, { 100, 1 });
//			SetConsoleCursorPosition(hConsole, { 99,(short)coursorPosition });
//			printf_s(">");
//
//			butCode = _getch();
//			if (butCode == 224)
//				switch (_getch()) {
//				case UP:
//					if (coursorPosition != 2) coursorPosition--;
//					break;
//				case DOWN:
//					if (coursorPosition != 2 + MAX_PLAYER_INVENTORY_SIZE - 1) coursorPosition++;
//					break;
//				}
//			else {
//				if (butCode == ENTER) {
//					if (coursorPosition == 2) choice = 1;
//					if (coursorPosition == 3) choice = 2;
//					if (coursorPosition == 4) choice = 3;
//					if (coursorPosition == 5) choice = 4;
//					if (coursorPosition == 6) choice = 5;
//					if (coursorPosition == 7) choice = 6;
//					if (coursorPosition == 8) choice = 7;
//					if (coursorPosition == 9) choice = 8;
//					if (coursorPosition == 10) choice = 9;
//					if (coursorPosition == 11) choice = 10;
//					break;
//				}
//				if (butCode == ESC) return;
//			}
//		} while (true);
//
//		Potion soldPotion = takePotionFromInventory(player.potions, choice - 1);
//		addPotionToInventory(soldPotion, seller.potions);
//
//		player.money += soldPotion.price;
//
//	} while (true);
//}
//
//void buyAbilities(Player& player, SellerOfAbilities& seller)
//
//{
//
//	int choice = 0;
//	int heroChoice = 0;
//	int butCode, coursorPosition2 = 14;
//
//	do
//	{
//		choice = abilityBuyChoiceChecker(screen, player, seller);
//
//		if (choice == 0) return;
//
//		if (player.money >= seller.abilities[choice - 1].price)
//		{
//
//
//			SetConsoleCursorPosition(hConsole, { 100, 2 + MAX_ABILITIES + 2 });
//			printf_s("Wich hero do you want to learn this ability?");
//			do {
//				system("cls");
//				drawScreen(screen);
//				drawBar(player);
//				drawAbilitiesSellerGoods(seller);
//				drawHeroChoice(player, 100, -4);
//				SetConsoleCursorPosition(hConsole, { 99, (short)coursorPosition2 });
//				printf_s(">");
//				butCode = _getch();
//				if (butCode == 224)
//					switch (_getch()) {
//					case UP: if (coursorPosition2 != 14) coursorPosition2--; break;
//					case DOWN: if (coursorPosition2 != 17) coursorPosition2++; break;
//					}
//				else {
//					if (butCode == ENTER) {
//						if (coursorPosition2 == 14) heroChoice = 1;
//						if (coursorPosition2 == 15) heroChoice = 2;
//						if (coursorPosition2 == 16) heroChoice = 3;
//						if (coursorPosition2 == 17) heroChoice = 4;
//						break;
//					}
//					if (butCode == ESC) return;
//				}
//
//			} while (true);
//
//			Ability boughtAbility = takeAbilityFromList(seller.abilities, choice - 1);
//
//			switch (heroChoice) {
//			case 1:
//				if (addAbilityToAbilities(boughtAbility, player.team[0].abilities))
//				{
//					player.money -= boughtAbility.price;
//				}
//				else
//				{
//					addAbilityToAbilities(boughtAbility, seller.abilities);
//					printf_s("Not enough place in your ability List");
//					Sleep(3000);
//				}
//
//				break;
//
//			case 2:
//				if (addAbilityToAbilities(boughtAbility, player.team[1].abilities))
//				{
//					player.money -= boughtAbility.price;
//				}
//				else
//				{
//					addAbilityToAbilities(boughtAbility, seller.abilities);
//					printf_s("Not enough place in your List");
//					Sleep(3000);
//				}
//
//				break;
//
//			case 3:
//				if (addAbilityToAbilities(boughtAbility, player.team[2].abilities) == true)
//				{
//					player.money -= boughtAbility.price;
//				}
//				else
//				{
//					addAbilityToAbilities(boughtAbility, seller.abilities);
//					printf_s("Not enough place in your List");
//					Sleep(3000);
//				}
//
//				break;
//
//			case 4:
//				if (addAbilityToAbilities(boughtAbility, player.team[3].abilities) == true)
//				{
//					player.money -= boughtAbility.price;
//				}
//				else
//				{
//					addAbilityToAbilities(boughtAbility, seller.abilities);
//					printf_s("Not enough place in your List");
//					Sleep(3000);
//				}
//
//				break;
//
//
//			}
//
//
//
//
//		}
//		else
//		{
//			printf("Not enough money");
//			Sleep(3000);
//
//		}
//
//	} while (true);
//
//}
//
//
//
//
void weaponSeller(Player& player, int stage)
{
	SDL_Event ev;
	SellerOfWeapons seller;


	clearWeaponInventory(seller.weapons);

	if (stage == 1)
	{
		addWeaponToInventory(ALLWeaponsList[1], seller.weapons);
		addWeaponToInventory(ALLWeaponsList[2], seller.weapons);
		addWeaponToInventory(ALLWeaponsList[4], seller.weapons);
	}

	if (stage == 2)
	{
		addWeaponToInventory(ALLWeaponsList[0], seller.weapons);
		addWeaponToInventory(ALLWeaponsList[3], seller.weapons);
	}

	int choice;
	int coursorPosition;

	


	while (true) {
		coursorPosition = 0;
		while (inSeller) {
			while (SDL_PollEvent(&ev)) {
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
						inSeller = false;
						break;
					case SDL_SCANCODE_ESCAPE: 
						return;
					}
					break;
				}
			}

			drawSeller(1, coursorPosition);

		}
	switch (choice)
	{
	case 1: buyWeapon(player, seller); 
		break;
	case 2: //sellWeapon(player, seller); 
		break;
	case 3: return; 
	}

	}




}

//void armorSeller(Player& player, int stage)
//{
//	int qountOfArmors;
//
//	Armor* ALLArmorsList = createAllArmors(qountOfArmors);
//	SellerOfArmors seller;
//
//	clearArmorInventory(seller.armors);
//
//	if (stage == 1)
//	{
//		addArmorToInventory(ALLArmorsList[0], seller.armors);
//		addArmorToInventory(ALLArmorsList[3], seller.armors);
//	}
//
//	if (stage == 2)
//	{
//		addArmorToInventory(ALLArmorsList[1], seller.armors);
//		addArmorToInventory(ALLArmorsList[2], seller.armors);
//	}
//
//
//	int choice;
//	int butCode, coursorPosition = 3;
//
//	do
//	{
//		do {
//			system("cls");
//			drawScreen(screen);
//			drawBar(player);
//			drawSellerChoice(' ');
//			SetConsoleCursorPosition(hConsole, { 114,(short)coursorPosition });
//			printf_s(">");
//
//			butCode = _getch();
//			if (butCode == 224)
//				switch (_getch()) {
//				case UP:
//					if (coursorPosition != 3) {
//						coursorPosition--;
//					}
//
//					break;
//				case DOWN:
//					if (coursorPosition != 5) {
//						coursorPosition++;
//					}
//
//					break;
//				}
//			else
//				if (butCode == ENTER) {
//					if (coursorPosition == 3) choice = 1;
//					if (coursorPosition == 4) choice = 2;
//					if (coursorPosition == 5) choice = 3;
//					break;
//				}
//		} while (true);
//
//		switch (choice)
//		{
//		case 1: buyArmor(player, seller, screen); break;
//		case 2: sellArmor(player, seller, screen); break;
//		case 3: return; break;
//		default: break;
//
//		}
//	} while (true);
//}
//
//void potionSeller(Player& player, int stage)
//{
//	int qountOfPotions;
//
//	Potion* ALLPotionsList = createAllPotions(qountOfPotions);
//	SellerOfPotions seller;
//
//	clearPotionInventory(seller.potions);
//
//	if (stage == 1)
//	{
//		addPotionToInventory(ALLPotionsList[0], seller.potions);
//		addPotionToInventory(ALLPotionsList[1], seller.potions);
//		addPotionToInventory(ALLPotionsList[2], seller.potions);
//	}
//
//	if (stage == 2)
//	{
//		addPotionToInventory(ALLPotionsList[3], seller.potions);
//		addPotionToInventory(ALLPotionsList[4], seller.potions);
//		addPotionToInventory(ALLPotionsList[5], seller.potions);
//	}
//
//	int choice;
//	int butCode, coursorPosition = 3;
//
//	do
//	{
//		do {
//			system("cls");
//			drawScreen(screen);
//			drawBar(player);
//			drawSellerChoice(' ');
//			SetConsoleCursorPosition(hConsole, { 114,(short)coursorPosition });
//			printf_s(">");
//
//			butCode = _getch();
//			if (butCode == 224)
//				switch (_getch()) {
//				case UP:
//					if (coursorPosition != 3) {
//						coursorPosition--;
//					}
//
//					break;
//				case DOWN:
//					if (coursorPosition != 5) {
//						coursorPosition++;
//					}
//
//					break;
//				}
//			else
//				if (butCode == ENTER) {
//					if (coursorPosition == 3) choice = 1;
//					if (coursorPosition == 4) choice = 2;
//					if (coursorPosition == 5) choice = 3;
//					break;
//				}
//		} while (true);
//		switch (choice)
//		{
//		case 1: buyPotion(player, seller, screen); break;
//		case 2: sellPotion(player, seller, screen); break;
//		case 3: return; break;
//		default: break;
//		}
//	} while (true);
//}
//
//void abilitySeller(Player& player, int stage)
//{
//	int qountOfAbilities;
//
//	Ability* ALLAbilitiesList = createAllAbilities(qountOfAbilities);
//	SellerOfAbilities seller;
//
//
//	clearAbilities(seller.abilities);
//
//	if (stage == 1)
//	{
//		addAbilityToAbilities(ALLAbilitiesList[0], seller.abilities);
//		addAbilityToAbilities(ALLAbilitiesList[2], seller.abilities);
//		addAbilityToAbilities(ALLAbilitiesList[4], seller.abilities);
//		addAbilityToAbilities(ALLAbilitiesList[6], seller.abilities);
//	}
//
//	if (stage == 2)
//	{
//		addAbilityToAbilities(ALLAbilitiesList[1], seller.abilities);
//		addAbilityToAbilities(ALLAbilitiesList[3], seller.abilities);
//		addAbilityToAbilities(ALLAbilitiesList[5], seller.abilities);
//		addAbilityToAbilities(ALLAbilitiesList[7], seller.abilities);
//	}
//
//	int choice;
//	int butCode, coursorPosition = 3;
//
//	do
//	{
//		do {
//			system("cls");
//			drawScreen(screen);
//			drawBar(player);
//			drawSellerChoice('a');
//			SetConsoleCursorPosition(hConsole, { 114,(short)coursorPosition });
//			printf_s(">");
//
//			butCode = _getch();
//			if (butCode == 224)
//				switch (_getch()) {
//				case UP:
//					if (coursorPosition != 3) {
//						coursorPosition -= 2;
//					}
//
//					break;
//				case DOWN:
//					if (coursorPosition != 5) {
//						coursorPosition += 2;
//					}
//
//					break;
//				}
//			else
//				if (butCode == ENTER) {
//					if (coursorPosition == 3) choice = 1;
//					if (coursorPosition == 5) choice = 3;
//					break;
//				}
//		} while (true);
//
//		switch (choice)
//		{
//		case 1: buyAbilities(player, seller, screen); break;
//		case 3: return; break;
//		default: break;
//		}
//	} while (true);
//}

