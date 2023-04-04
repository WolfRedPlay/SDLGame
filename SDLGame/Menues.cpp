#include "Menues.h"
char* randomName() {
	char name[MAX_NAME_LENGTH];
	FILE* file;
	int count = 0;
	if (fopen_s(&file, "Names.txt", "rt") != 0) {
		printf_s("Can not find saves\n");
		exit(1);
	}
	fscanf_s(file, "%d ", &count);
	int nameNumber = random(1, count);
	for (int i = 1; i <= count; i++) {
		fscanf_s(file, "%s\n", name, sizeof(name) / sizeof(char));

		if (i == nameNumber) {
			fclose(file);
			return name;
		}
	}


}



bool createHeroesMenu(Player& player) {
	int coursorPosition, choice;
	bool inHeroMenu = true;
	bool choosingName = false;
	bool fillingName = false;
	clearPlayer(player);

	SDL_Event ev;
	for (int i = 0; i < 4; i++)
	{
		char name[MAX_NAME_LENGTH] = "";
		coursorPosition = 0;
		while (inHeroMenu) {

			while (SDL_PollEvent(&ev)) {
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_UP:
						if (coursorPosition != 0 && coursorPosition != 1) coursorPosition -= 2;
						break;
					case SDL_SCANCODE_DOWN:
						if (coursorPosition != 3 && coursorPosition != 2) coursorPosition += 2;
						break;
					case SDL_SCANCODE_LEFT:
						if (coursorPosition != 0 && coursorPosition != 2) coursorPosition--;
						break;
					case SDL_SCANCODE_RIGHT:
						if (coursorPosition != 3 && coursorPosition != 1) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						inHeroMenu = false;
						choosingName = true;
						break;
					case SDL_SCANCODE_ESCAPE:
						return false;
						break;
					}
					break;

				}
			}

			drawHeroCreatingMenu(i + 1, coursorPosition);
		}
		switch (choice) {
		case 0:
			player.team[i].maxHealth = 150;
			player.team[i].health = player.team[i].maxHealth;
			player.team[i].armor = 15;
			player.team[i].maxMana = 0;
			player.team[i].mana = player.team[i].maxMana;
			player.team[i].maxStamina = 100;
			player.team[i].stamina = player.team[i].maxStamina;
			player.team[i].damage = 8;
			player.team[i].heroClass = KNIGHT;
			player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -100, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -200, qountOfArmors);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -601, qountOfAbilities), player.team[i].abilities);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -602, qountOfAbilities), player.team[i].abilities);

			player.team[i].lvl = 1;
			player.team[i].exp = 0;
			break;
		case 1:
			player.team[i].maxHealth = 75;
			player.team[i].health = player.team[i].maxHealth;
			player.team[i].armor = 10;
			player.team[i].maxMana = 0;
			player.team[i].mana = player.team[i].maxMana;
			player.team[i].maxStamina = 100;
			player.team[i].stamina = player.team[i].maxStamina;
			player.team[i].damage = 16;
			player.team[i].heroClass = ROGUE;
			player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -101, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -201, qountOfArmors);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -501, qountOfAbilities), player.team[i].abilities);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -502, qountOfAbilities), player.team[i].abilities);

			player.team[i].lvl = 1;
			player.team[i].exp = 0;
			break;
		case 2:
			player.team[i].maxHealth = 70;
			player.team[i].health = player.team[i].maxHealth;
			player.team[i].armor = 8;
			player.team[i].maxMana = 100;
			player.team[i].mana = player.team[i].maxMana;
			player.team[i].maxStamina = 10;
			player.team[i].stamina = player.team[i].maxStamina;
			player.team[i].damage = 16;
			player.team[i].heroClass = MAGE;
			player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -102, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -202, qountOfArmors);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -701, qountOfAbilities), player.team[i].abilities);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -702, qountOfAbilities), player.team[i].abilities);

			player.team[i].lvl = 1;
			player.team[i].exp = 0;
			break;
		case 3:
			player.team[i].maxHealth = 80;
			player.team[i].health = player.team[i].maxHealth;
			player.team[i].armor = 10;
			player.team[i].maxMana = 100;
			player.team[i].mana = player.team[i].maxMana;
			player.team[i].maxStamina = 10;
			player.team[i].stamina = player.team[i].maxStamina;
			player.team[i].damage = 2;
			player.team[i].heroClass = HEALER;
			player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -103, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -203, qountOfArmors);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -801, qountOfAbilities), player.team[i].abilities);
			addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, -802, qountOfAbilities), player.team[i].abilities);

			player.team[i].lvl = 1;
			player.team[i].exp = 0;
			break;
		}

		coursorPosition = 0;
		while (choosingName) {
			while (SDL_PollEvent(&ev)) {
				switch (ev.type) {
				case SDL_QUIT:
					return false;
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
						choosingName = false;
						fillingName = true;
						break;
					case SDL_SCANCODE_ESCAPE:
						choosingName = false;
						inHeroMenu = true;
						i--;
						break;
					}
					break;

				}
			}
			drawHeroNameChoice(coursorPosition);
		}
		int currentrSym = 0;
		switch (choice) {
		case 0:
			SDL_StartTextInput();
			while (fillingName) {
				while (SDL_PollEvent(&ev)) {
					switch (ev.type) {
					case SDL_TEXTINPUT:
						if (currentrSym < MAX_NAME_LENGTH - 1) {
							strcat_s(name, ev.text.text);
							currentrSym++;
						}
						break;
					case SDL_KEYDOWN:

						switch (ev.key.keysym.scancode) {
						case SDL_SCANCODE_BACKSPACE:
							currentrSym--;
							name[currentrSym] = '\0';
							break;
						case SDL_SCANCODE_RETURN:
							strcpy_s(player.team[i].name, name);
							fillingName = false;
							inHeroMenu = true;
							break;
						case SDL_SCANCODE_ESCAPE:
							choosingName = true;
							fillingName = false;
							i--;
							break;

						}
						break;
					}
				}
				drawPlayerNameChoosing(name);
			}
			SDL_StopTextInput();
			break;
		case 1:

			strncpy_s(name, randomName(), MAX_NAME_LENGTH);
			while (fillingName) {

				while (SDL_PollEvent(&ev)) {
					switch (ev.type) {
					case SDL_KEYDOWN:
						switch (ev.key.keysym.scancode) {
						case SDL_SCANCODE_LEFT:
							strncpy_s(name, randomName(), MAX_NAME_LENGTH);
							break;
						case SDL_SCANCODE_RIGHT:
							strncpy_s(name, randomName(), MAX_NAME_LENGTH);
							break;

						case SDL_SCANCODE_RETURN:
							strcpy_s(player.team[i].name, name);
							fillingName = false;
							inHeroMenu = true;
							break;
						case SDL_SCANCODE_ESCAPE:
							choosingName = true;
							fillingName = false;
							i--;
							break;

						}
						break;
					}
				}


				drawRandomNameChoosing(name);


			}
			break;
		}


	}
	addPotionToInventory(findInPotionsList(ALLPotionsList, -302, qountOfPotions), player.potions);
	addPotionToInventory(findInPotionsList(ALLPotionsList, -302, qountOfPotions), player.potions);
	return true;
}

bool startMenu(Player& player) {
	int coursorPosition = 0, choice;
	bool inStartMenu = true;
	SDL_Event ev;
	while (true) {

		while (inStartMenu) {
			while (SDL_PollEvent(&ev))
			{
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
						if (coursorPosition != 3) coursorPosition++;
						break;

					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						inStartMenu = false;
						break;
					}
					break;
				}
			}

			drawStartMenu(coursorPosition);

		}

		switch (choice) {
		case 0:
			if (createHeroesMenu(player)) return true;
			else inStartMenu = true;
			break;
		case 1: break;
		case 2: break;


		case 3:
			return false;
			break;
		}

	}


}

void gameMenu() {

}

void playerMenu(Player& player) {
	bool inPlayerMenu, inHeroesStats, inInventory, inHeroChoosing;
	int coursorPosition, choice, heroChoice;
	bool isItemChoosen, isHeroChoosen, isDeleted;
	SDL_Event ev;



	while (true) {
		inPlayerMenu = true;
		coursorPosition = 0;
		while (inPlayerMenu) {

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
						if (coursorPosition != 6) coursorPosition++;
						break;

					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						inPlayerMenu = false;
						break;

					case SDL_SCANCODE_TAB:
						inPlayerMenu = false;
						return;
						break;

					case SDL_SCANCODE_ESCAPE:
						inPlayerMenu = false;
						return;
						break;

					}
					break;
				}
			drawPlayerMenu(coursorPosition);

		}
		switch (choice) {
		case 0:
#pragma region HERO STATS
			inHeroesStats = true;
			while (inHeroesStats) {
				while (SDL_PollEvent(&ev)) {
					switch (ev.type) {
					case SDL_QUIT:
						DeInit(0);
						break;
					case SDL_KEYDOWN:
						switch (ev.key.keysym.scancode) {

						case SDL_SCANCODE_TAB:
							inPlayerMenu = true;
							inHeroesStats = false;
							break;

						case SDL_SCANCODE_ESCAPE:
							inPlayerMenu = true;
							inHeroesStats = false;
							break;

						}
						break;
					}
				}

				drawHeroesStats(player);
			}

#pragma endregion
			break;
		case 1:
#pragma region WEAPON INVENTORY
			inInventory = true;
			coursorPosition = 0;

			while (inInventory) {
				isItemChoosen = false;
				isHeroChoosen = false;

				while (SDL_PollEvent(&ev)) {
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
							isItemChoosen = true;
							break;
						case SDL_SCANCODE_ESCAPE:
							inInventory = false;
							inPlayerMenu = true;
							break;
						case SDL_SCANCODE_TAB:
							inInventory = false;
							inPlayerMenu = true;
							break;
						}


						break;
					}

				}


				if (isItemChoosen) coursorPosition = 0;
				while (isItemChoosen) {
					while (SDL_PollEvent(&ev)) {
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
								isHeroChoosen = true;
								isItemChoosen = false;
								break;
							case SDL_SCANCODE_ESCAPE:
								isItemChoosen = false;
								break;
							case SDL_SCANCODE_TAB:
								isItemChoosen = false;
								break;
							}


							break;
						}

					}

					if (isHeroChoosen) {
						Weapon changedWeapon = player.team[heroChoice].equipedWeapon;
						player.team[heroChoice].equipedWeapon = takeWeaponFromInventory(player.weapons, choice);
						addWeaponToInventory(changedWeapon, player.weapons);
					}
					drawHeroChoice(player, coursorPosition);

				}
				drawPlayerWeapons(player, coursorPosition);
			}
#pragma endregion
			break;
		case 2:
#pragma region ARMOR INVENTORY
			inInventory = true;
			coursorPosition = 0;
			while (inInventory) {
				isItemChoosen = false;
				isHeroChoosen = false;

				while (SDL_PollEvent(&ev)) {
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
							isItemChoosen = true;
							break;
						case SDL_SCANCODE_ESCAPE:
							inInventory = false;
							inPlayerMenu = true;
							break;
						case SDL_SCANCODE_TAB:
							inInventory = false;
							inPlayerMenu = true;
							break;
						}


						break;
					}

				}


				if (isItemChoosen) coursorPosition = 0;
				while (isItemChoosen) {
					while (SDL_PollEvent(&ev)) {
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
								isHeroChoosen = true;
								isItemChoosen = false;
								break;
							case SDL_SCANCODE_ESCAPE:
								isItemChoosen = false;
								break;
							case SDL_SCANCODE_TAB:
								isItemChoosen = false;
								break;
							}


							break;
						}

					}

					if (isHeroChoosen) {
						Armor changedarmor = player.team[heroChoice].equipedArmor;
						player.team[heroChoice].equipedArmor = takeArmorFromInventory(player.armors, choice);
						addArmorToInventory(changedarmor, player.armors);
					}
					drawHeroChoice(player, coursorPosition);

				}
				drawPlayerArmors(player, coursorPosition);
			}
#pragma endregion
			break;
		case 3:
#pragma region POTION INVENTORY
			inInventory = true;
			coursorPosition = 0;
			while (inInventory) {
				isItemChoosen = false;
				isHeroChoosen = false;

				while (SDL_PollEvent(&ev)) {
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
							isItemChoosen = true;
							break;
						case SDL_SCANCODE_ESCAPE:
							inInventory = false;
							inPlayerMenu = true;
							break;
						case SDL_SCANCODE_TAB:
							inInventory = false;
							inPlayerMenu = true;
							break;
						}


						break;
					}

				}


				if (isItemChoosen) coursorPosition = 0;
				while (isItemChoosen) {
					while (SDL_PollEvent(&ev)) {
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
								isHeroChoosen = true;
								isItemChoosen = false;
								break;
							case SDL_SCANCODE_ESCAPE:
								isItemChoosen = false;
								break;
							case SDL_SCANCODE_TAB:
								isItemChoosen = false;
								break;
							}


							break;
						}

					}

					if (isHeroChoosen) {
						if (player.team[heroChoice].health < player.team[heroChoice].maxHealth - player.potions[choice].health)player.team[heroChoice].health += player.potions[choice].health;
						else player.team[heroChoice].health = player.team[heroChoice].maxHealth;
						if (player.team[heroChoice].mana < player.team[heroChoice].maxMana - player.potions[choice].mana)player.team[heroChoice].mana += player.potions[choice].mana;
						else player.team[heroChoice].mana = player.team[heroChoice].maxMana;
						takePotionFromInventory(player.potions, choice);
					}
					drawHeroChoice(player, coursorPosition);

				}
				drawPlayerPotions(player, coursorPosition);
			}
#pragma endregion
			break;
		case 4:
#pragma region ABILITIES LIST
			inHeroChoosing = true;
			isHeroChoosen = false;
			inInventory = false;
			isDeleted = false;
			isItemChoosen = false;
			coursorPosition = 0;
			while (inHeroChoosing) {
				while (SDL_PollEvent(&ev)) {
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
							isHeroChoosen = true;
							inHeroChoosing = false;
							break;
						case SDL_SCANCODE_ESCAPE:
							inHeroChoosing = false;
							isHeroChoosen = false;
							inPlayerMenu = true;
							break;
						case SDL_SCANCODE_TAB:
							inHeroChoosing = false;
							isHeroChoosen = false;
							inPlayerMenu = true;
							break;
						}


						break;
					}

				}
				if (isHeroChoosen) {
					inInventory = true;
					coursorPosition = 0;
				}
				while (inInventory) {
					while (SDL_PollEvent(&ev)) {
						switch (ev.type) {
						case SDL_QUIT:
							DeInit(0);
							break;

						case SDL_KEYDOWN:
							switch (ev.key.keysym.scancode) {
							case SDL_SCANCODE_LEFT:
								if (coursorPosition != 0 && coursorPosition != 4) coursorPosition--;
								break;
							case SDL_SCANCODE_RIGHT:
								if (coursorPosition != 3 && coursorPosition != 7) coursorPosition++;
								break;
							case SDL_SCANCODE_UP:
								if (coursorPosition >= 4) coursorPosition -= 4;
								break;
							case SDL_SCANCODE_DOWN:
								if (coursorPosition <= 3) coursorPosition += 4;
								break;
							case SDL_SCANCODE_RETURN:
								choice = coursorPosition;
								isItemChoosen = true;
								break;
							case SDL_SCANCODE_ESCAPE:
								inInventory = false;
								isHeroChoosen = false;
								inHeroChoosing = true;
								break;
							case SDL_SCANCODE_TAB:
								inInventory = false;
								isHeroChoosen = false;
								inHeroChoosing = true;
								break;
							}


							break;
						}

					}


					while (isItemChoosen) {
						while (SDL_PollEvent(&ev)) {
							switch (ev.type) {
							case SDL_QUIT:
								DeInit(0);
								break;

							case SDL_KEYDOWN:
								switch (ev.key.keysym.scancode) {
								case SDL_SCANCODE_Y:
									takeAbilityFromList(player.team[heroChoice].abilities, choice);
									isItemChoosen = false;
									break;
								case SDL_SCANCODE_N:
									isItemChoosen = false;
									break;
								}
								break;
							}

						}

						drawConfirmation();
					}



					drawHeroAbilities(player.team[heroChoice], coursorPosition);
				}

				drawHeroChoice(player, coursorPosition);
			}



#pragma endregion
			break;
		case 5:break;
		case 6:break;
		}
	}



}