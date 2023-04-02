#include "Menues.h"




bool createHeroesMenu(Player& player) {
	int coursorPosition = 0, choice;
	bool inHeroMenu = true;
	SDL_Event ev;
	for (int i = 0; i < 4; i++)
	{
		while (inHeroMenu) {

			while (SDL_PollEvent(&ev)) {
				switch (ev.type) {
				case SDL_QUIT:
					return false;
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
						break;
					}
					break;

				}
			}

			drawHeroCreatingMenu(player, i + 1, coursorPosition);
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
			/*player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -100, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -200, qountOfArmors);
			setStartingAbilities(player.team[i], heroClass);
			*/
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
			/*player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -100, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -200, qountOfArmors);
			setStartingAbilities(player.team[i], heroClass);
			*/
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
			/*player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -100, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -200, qountOfArmors);
			setStartingAbilities(player.team[i], heroClass);
			*/
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
			/*player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, -100, qountOfWeapons);
			player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, -200, qountOfArmors);
			setStartingAbilities(player.team[i], heroClass);
			*/
			player.team[i].lvl = 1;
			player.team[i].exp = 0;
			break;
		}
		inHeroMenu = true;

	}
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
					return false;
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
			break;
		case 1: break;
		case 2: break;


		case 3:
			return false;
			break;
		}

	}


}