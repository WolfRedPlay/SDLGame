#include "Shop.h"


bool inSeller = true;


void buyWeapon(Player& player, SellerOfWeapons& seller)
{
	int choice, coursorPosition = 0;
	SDL_Event ev;

	bool isChoosen = false;


	while (true) {

		while (!isChoosen) {
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
						if (coursorPosition != 19) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						if (seller.weapons[coursorPosition].ID != 0)
						{
							choice = coursorPosition;
							isChoosen = true;
						}

						break;
					case SDL_SCANCODE_ESCAPE: return;
					}
					break;
				}
			drawSellerChoice(player.money, seller, coursorPosition);

		}

		if (player.money >= seller.weapons[choice].price) {
			
			Weapon boughtWeapon = takeWeaponFromInventory(seller.weapons, choice);

			if (addWeaponToInventory(boughtWeapon, player.weapons) == true)
			{
				player.money -= boughtWeapon.price;
				isChoosen = false;
				//звук покупки
			}
			else {

				addWeaponToInventory(boughtWeapon, seller.weapons);
				isChoosen = false;
				//звук неудачной покупки


			}
		}
		else
		{
			isChoosen = false;
			//звук неудачной покупки
		}

	}

}
void sellWeapon(Player& player, SellerOfWeapons& seller)
{
	int choice, coursorPosition = 0;
	SDL_Event ev;

	bool isChoosen = false;


	while (true) {

		while (!isChoosen) {
			while (SDL_PollEvent(&ev))
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_LEFT:
						if (coursorPosition != 0 && coursorPosition != 5) coursorPosition--;
						break;
					case SDL_SCANCODE_RIGHT:
						if (coursorPosition != 4 && coursorPosition != 9) coursorPosition++;
						break;
					case SDL_SCANCODE_UP:
						if (coursorPosition >= 5) coursorPosition -= 5;
						break;
					case SDL_SCANCODE_DOWN:
						if (coursorPosition <= 4) coursorPosition += 5;
						break;
					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						isChoosen = true;
						break;
					case SDL_SCANCODE_ESCAPE: return;
					}
					break;
				}
			drawPlayerWeapons(player, coursorPosition);

		}

		if (player.weapons[choice].ID != 0)
		{
			Weapon soldWeapon = takeWeaponFromInventory(player.weapons, choice);
			addWeaponToInventory(soldWeapon, seller.weapons);
			player.money += soldWeapon.price;
			isChoosen = false;
		}
		else isChoosen = false;
		

	}

}

void buyArmor(Player& player, SellerOfArmors& seller)
{
	int choice, coursorPosition = 0;
	SDL_Event ev;

	bool isChoosen = false;


	while (true) {

		while (!isChoosen) {
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
						if (coursorPosition != 19) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						if (seller.armors[coursorPosition].ID != 0)
						{
							choice = coursorPosition;
							isChoosen = true;
						}

						break;
					case SDL_SCANCODE_ESCAPE: return;
					}
					break;
				}
			drawSellerChoice(player.money, seller, coursorPosition);

		}

		if (player.money >= seller.armors[choice].price) {
			
			Armor boughtArmor = takeArmorFromInventory(seller.armors, choice);

			if (addArmorToInventory(boughtArmor, player.armors) == true)
			{
				player.money -= boughtArmor.price;
				isChoosen = false;
				//звук покупки
			}
			else {

				addArmorToInventory(boughtArmor, seller.armors);
				isChoosen = false;
				//звук неудачной покупки


			}
		}
		else
		{
			isChoosen = false;
			//звук неудачной покупки
		}

	}

}
void sellArmor(Player& player, SellerOfArmors& seller)
{
	int choice, coursorPosition = 0;
	SDL_Event ev;

	bool isChoosen = false;


	while (true) {

		while (!isChoosen) {
			while (SDL_PollEvent(&ev))
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_LEFT:
						if (coursorPosition != 0 && coursorPosition != 5) coursorPosition--;
						break;
					case SDL_SCANCODE_RIGHT:
						if (coursorPosition != 4 && coursorPosition != 9) coursorPosition++;
						break;
					case SDL_SCANCODE_UP:
						if (coursorPosition >= 5) coursorPosition -= 5;
						break;
					case SDL_SCANCODE_DOWN:
						if (coursorPosition <= 4) coursorPosition += 5;
						break;
					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						isChoosen = true;
						break;
					case SDL_SCANCODE_ESCAPE: return;
					}
					break;
				}
			drawPlayerArmors(player, coursorPosition);

		}

		if (player.weapons[choice].ID != 0)
		{
			Armor soldArmor = takeArmorFromInventory(player.armors, choice);
			addArmorToInventory(soldArmor, seller.armors);
			player.money += soldArmor.price;
			isChoosen = false;
		}
		else isChoosen = false;
		

	}

}

void buyPotion(Player& player, SellerOfPotions& seller)
{
	int choice, coursorPosition = 0;
	SDL_Event ev;

	bool isChoosen = false;


	while (true) {

		while (!isChoosen) {
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
						if (coursorPosition != 19) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						if (seller.potions[coursorPosition].ID != 0)
						{
							choice = coursorPosition;
							isChoosen = true;
						}

						break;
					case SDL_SCANCODE_ESCAPE: return;
					}
					break;
				}
			drawSellerChoice(player.money, seller, coursorPosition);

		}

		if (player.money >= seller.potions[choice].price) {
			
			Potion boughtPotion = takePotionFromInventory(seller.potions, choice);

			if (addPotionToInventory(boughtPotion, player.potions) == true)
			{
				player.money -= boughtPotion.price;
				isChoosen = false;
				//звук покупки
			}
			else {

				addPotionToInventory(boughtPotion, seller.potions);
				isChoosen = false;
				//звук неудачной покупки


			}
		}
		else
		{
			isChoosen = false;
			//звук неудачной покупки
		}

	}

}
void sellPotion(Player& player, SellerOfPotions& seller)
{
	int choice, coursorPosition = 0;
	SDL_Event ev;

	bool isChoosen = false;


	while (true) {

		while (!isChoosen) {
			while (SDL_PollEvent(&ev))
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_LEFT:
						if (coursorPosition != 0 && coursorPosition != 5) coursorPosition--;
						break;
					case SDL_SCANCODE_RIGHT:
						if (coursorPosition != 4 && coursorPosition != 9) coursorPosition++;
						break;
					case SDL_SCANCODE_UP:
						if (coursorPosition >= 5) coursorPosition -= 5;
						break;
					case SDL_SCANCODE_DOWN:
						if (coursorPosition <= 4) coursorPosition += 5;
						break;
					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						isChoosen = true;
						break;
					case SDL_SCANCODE_ESCAPE: return;
					}
					break;
				}
			drawPlayerPotions(player, coursorPosition);

		}

		if (player.weapons[choice].ID != 0)
		{
			Potion soldPotion = takePotionFromInventory(player.potions, choice);
			addPotionToInventory(soldPotion, seller.potions);
			player.money += soldPotion.price;
			isChoosen = false;
		}
		else isChoosen = false;
		

	}

}

void buyAbility(Player& player, SellerOfAbilities& seller)
{
	int choice, coursorPosition = 0, heroChoice = 0;
	SDL_Event ev;

	bool isChoosen = false;


	while (true) {

		while (!isChoosen) {
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
						if (coursorPosition != 19) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						if (seller.abilities[coursorPosition].ID != 0)
						{
							choice = coursorPosition;
							isChoosen = true;
						}

						break;
					case SDL_SCANCODE_ESCAPE: return;
					}
					break;
				}
			drawSellerChoice(player.money, seller, coursorPosition);

		}

		if (player.money >= seller.abilities[choice].price) {

			Ability boughtAbility = takeAbilityFromList(seller.abilities, choice);

			if (addAbilityToAbilities(boughtAbility, player.team[heroChoice].abilities) == true)
			{
				player.money -= boughtAbility.price;
				isChoosen = false;
				//звук покупки
			}
			else {

				addAbilityToAbilities(boughtAbility, seller.abilities);
				isChoosen = false;
				//звук неудачной покупки


			}
		}
		else
		{
			isChoosen = false;
			//звук неудачной покупки
		}

	}

}


void weaponSeller(Player& player, int stage, char** map)
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
		case 0: 
			buyWeapon(player, seller);
			inSeller = true;
			break;
		case 1: 
			sellWeapon(player, seller);
			drawScreen(map, player.position);
			drawPlayer(player.position, player.diraction, 0);
			inSeller = true;
			break;
		}

	}

}
void armorSeller(Player& player, int stage, char** map)
{
	SDL_Event ev;
	SellerOfArmors seller;


	clearArmorInventory(seller.armors);

	if (stage == 1)
	{
		addArmorToInventory(ALLArmorsList[0], seller.armors);
		addArmorToInventory(ALLArmorsList[3], seller.armors);
	}

	if (stage == 2)
	{
		addArmorToInventory(ALLArmorsList[1], seller.armors);
		addArmorToInventory(ALLArmorsList[2], seller.armors);
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

			drawSeller(2, coursorPosition);

		}
		switch (choice)
		{
		case 0: 
			buyArmor(player, seller);
			inSeller = true;
			break;
		case 1: 
			sellArmor(player, seller);
			drawScreen(map, player.position);
			drawPlayer(player.position, player.diraction, 0);
			inSeller = true;
			break;
		}

	}

}
void potionSeller(Player& player, int stage, char** map)
{
	SDL_Event ev;
	SellerOfPotions seller;


	clearPotionInventory(seller.potions);

	if (stage == 1)
	{
		addPotionToInventory(ALLPotionsList[0], seller.potions);
		addPotionToInventory(ALLPotionsList[1], seller.potions);
		addPotionToInventory(ALLPotionsList[2], seller.potions);
	}

	if (stage == 2)
	{
		addPotionToInventory(ALLPotionsList[3], seller.potions);
		addPotionToInventory(ALLPotionsList[4], seller.potions);
		addPotionToInventory(ALLPotionsList[5], seller.potions);
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

			drawSeller(3, coursorPosition);

		}
		switch (choice)
		{
		case 0: 
			buyPotion(player, seller);
			inSeller = true;
			break;
		case 1: 
			sellPotion(player, seller);
			drawScreen(map, player.position);
			drawPlayer(player.position, player.diraction, 0);
			inSeller = true;
			break;
		}

	}

}

void abilitySeller(Player& player, int stage, char** map)
{
	SDL_Event ev;
	SellerOfAbilities seller;


	clearAbilities(seller.abilities);

	if (stage == 1)
	{
		addAbilityToAbilities(ALLAbilitiesList[0], seller.abilities);
		addAbilityToAbilities(ALLAbilitiesList[2], seller.abilities);
		addAbilityToAbilities(ALLAbilitiesList[4], seller.abilities);
		addAbilityToAbilities(ALLAbilitiesList[6], seller.abilities);
	}

	if (stage == 2)
	{
		addAbilityToAbilities(ALLAbilitiesList[1], seller.abilities);
		addAbilityToAbilities(ALLAbilitiesList[3], seller.abilities);
		addAbilityToAbilities(ALLAbilitiesList[5], seller.abilities);
		addAbilityToAbilities(ALLAbilitiesList[7], seller.abilities);
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

			drawSeller(4, coursorPosition);

		}
		switch (choice)
		{
		case 0: 
			buyAbility(player, seller);
			drawScreen(map, player.position);
			drawPlayer(player.position, player.diraction, 0);
			inSeller = true;
			break;
		case 1: 
			//forgetAbility(player, seller);
			drawScreen(map, player.position);
			drawPlayer(player.position, player.diraction, 0);
			inSeller = true;
			break;
		}

	}

}



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

