#include "Basic.h"

SDL_Texture* generateTextureFromPNG(const char* file) {
	SDL_Surface* surf = IMG_Load(file);
	if (surf == NULL) {
		printf_s("Error with loading img!!!");
		exit(1);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
	return texture;
}

int random(int min, int max) {
	return rand() % (max - min + 1) + min;

}

void readMap(char** map, const char* fileName, int size_x, int size_y) {
	FILE* file;
	if (fopen_s(&file, fileName, "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	for (int i = 0; i < size_y; i++)
		for (int j = 0; j < size_x; j++)
			fscanf_s(file, "%c", &map[i][j], sizeof(char));

	fclose(file);
}

void deleteObject(char** map, int x, int y) {
	int grassCount = 0;
	int woodCount = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (map[y + i][x + j] == GRASS) grassCount++;
			if (map[y + i][x + j] == WOOD) woodCount++;
		}
	}
	if (grassCount > woodCount) map[y][x] = GRASS;
	if (woodCount > grassCount) map[y][x] = WOOD;
	if (woodCount == grassCount) map[y][x] = WOOD;


}

Weapon createEmptyWeapon() {
	Weapon empty;
	empty.price = 0;
	empty.damage = 0;
	empty.ID = 0;
	for (int i = 0; i < 15; i++)
		empty.name[i] = ' ';
	return empty;
}
Armor createEmptyArmor() {
	Armor empty;
	empty.price = 0;
	empty.armor = 0;
	empty.ID = 0;
	for (int i = 0; i < 15; i++)
		empty.name[i] = ' ';
	return empty;
}
Potion createEmptyPotion() {
	Potion empty;
	empty.price = 0;
	empty.health = 0;
	empty.mana = 0;
	empty.ID = 0;
	for (int i = 0; i < 15; i++)
		empty.name[i] = ' ';
	return empty;
}
Ability createEmptyAbility() {
	Ability empty;
	empty.damage = 0;
	empty.manaCost = 0;
	empty.cooldown = 0;
	empty.ID = 0;
	empty.price = 0;
	empty.type = -1;
	empty.buff = 0;
	empty.buffedCharacteristic = -1;
	empty.aoe = 0;
	empty.duration = 0;
	for (int i = 0; i < 15; i++)
		empty.name[i] = ' ';
	return empty;
}
//QuestItem createEmptyQuestItem() {
//	QuestItem empty;
//	empty.ID = 0;
//	for (int i = 0; i < 15; i++)
//		empty.name[i] = ' ';
//	return empty;
//}
//Quest createEmptyQuest() {
//	Quest empty;
//	empty.requiredItem = createEmptyQuestItem();
//	for (int i = 0; i < 15; i++)
//		empty.name[i] = ' ';
//	return empty;
//}
Hero createEmptyHero() {
	Hero empty;
	/*for (int i = 0; i < MAX_ABILITIES; i++) {
		empty.abilities[i] = createEmptyAbility();
	}*/
	empty.armor = 0;
	empty.damage = 0;
	empty.equipedArmor = createEmptyArmor();
	empty.equipedWeapon = createEmptyWeapon();
	empty.health = 0;
	empty.heroClass = 0;
	empty.mana = 0;
	empty.stamina = 0;

	for (int i = 0; i < 15; i++)
		empty.name[i] = ' ';
	return empty;
}
//Enemy createEmptyEnemy() {
//	Enemy empty;
//	/*for (int i = 0; i < MAX_ABILITIES; i++) {
//	}*/
//	empty.ability = createEmptyAbility();
//	empty.armor = 0;
//	empty.damage = 0;
//	empty.IDarmorDrop = 0;
//	empty.IDpotionDrop = 0;
//	empty.health = 0;
//	empty.mana = 0;
//	empty.stamina = 0;
//	empty.IDweaponDrop = 0;
//	empty.ID = 0;
//	empty.moneyDrop = 0;
//	empty.symbol = ' ';
//
//	for (int i = 0; i < MAX_NAME_LENGTH; i++)
//		empty.name[i] = ' ';
//	return empty;
//}





void clearWeaponInventory(Weapon* weapons) {
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
		weapons[i] = createEmptyWeapon();
	}

}
void clearArmorInventory(Armor* armors)
{

	for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
		armors[i] = createEmptyArmor();
	}


}
void clearPotionInventory(Potion* potions) {
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
		potions[i] = createEmptyPotion();
	}

}
void clearAbilities(Ability* abilities) {
	for (int i = 0; i < MAX_ABILITIES; i++) {
		abilities[i] = createEmptyAbility();
	}
}
void clearPlayer(Player& player) {
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		player.weapons[i] = createEmptyWeapon();
	}
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		player.armors[i] = createEmptyArmor();
	}
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		player.potions[i] = createEmptyPotion();
	}
	for (int i = 0; i < 4; i++) {
		clearAbilities(player.team[i].abilities);
	}

	/*for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		player.questItems[i] = createEmptyQuestItem();
	}
	for (int i = 0; i < MAX_QUESTS; i++) {
		player.quests[i] = createEmptyQuest();
	}*/
}




Weapon findInWeaponsList(Weapon* ALLWeaopnsList, int ID, int numWeapons) {
	if (ID == 0) return createEmptyWeapon();
	for (int i = 0; i < numWeapons; i++)
		if (ALLWeaopnsList[i].ID == ID) return ALLWeaopnsList[i];
}
Armor findInArmorsList(Armor* ALLArmorsList, int ID, int numArmors) {
	if (ID == 0) return createEmptyArmor();
	for (int i = 0; i < numArmors; i++)
		if (ALLArmorsList[i].ID == ID) return ALLArmorsList[i];
}
Potion findInPotionsList(Potion* ALLPotionsList, int ID, int numPotions) {
	if (ID == 0) return createEmptyPotion();
	for (int i = 0; i < numPotions; i++)
		if (ALLPotionsList[i].ID == ID) return ALLPotionsList[i];
}
Ability findInAbilitiesList(Ability* ALLAbilitiesList, int ID, int numAbilities) {
	if (ID == 0) return createEmptyAbility();
	for (int i = 0; i < numAbilities; i++)
		if (ALLAbilitiesList[i].ID == ID) return ALLAbilitiesList[i];
}


Weapon* createAllWeapons(int& amount) {
	FILE* file;
	if (fopen_s(&file, "Items\\Weapons.txt", "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}

	fscanf_s(file, "%d", &amount, sizeof(int));
	Weapon* weaponsList = (Weapon*)malloc(amount * sizeof(Weapon));
	for (int i = 0; i < amount; i++) {
		fscanf_s(file, "%d", &weaponsList[i].ID, sizeof(int));
		fscanf_s(file, "%s", weaponsList[i].name, sizeof(weaponsList[0].name) / sizeof(char));
		fscanf_s(file, "%d", &weaponsList[i].damage, sizeof(int));
		fscanf_s(file, "%d", &weaponsList[i].price, sizeof(int));
	}

	fclose(file);
	return weaponsList;
}
Armor* createAllArmors(int& amount) {

	FILE* file;

	if (fopen_s(&file, "Items\\Armors.txt", "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	fscanf_s(file, "%d", &amount, sizeof(int));
	Armor* armorsList = (Armor*)malloc(amount * sizeof(Armor));
	for (int i = 0; i < amount; i++) {
		fscanf_s(file, "%d", &armorsList[i].ID, sizeof(int));
		fscanf_s(file, "%s", armorsList[i].name, sizeof(armorsList[0].name) / sizeof(char));
		fscanf_s(file, "%d", &armorsList[i].armor, sizeof(int));
		fscanf_s(file, "%d", &armorsList[i].price, sizeof(int));
	}

	fclose(file);
	return armorsList;
}
Potion* createAllPotions(int& amount) {

	FILE* file;

	if (fopen_s(&file, "Items\\Potions.txt", "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	fscanf_s(file, "%d", &amount, sizeof(int));
	Potion* potionsList = (Potion*)malloc(amount * sizeof(Potion));
	for (int i = 0; i < amount; i++) {
		fscanf_s(file, "%d", &potionsList[i].ID, sizeof(int));
		fscanf_s(file, "%s", potionsList[i].name, sizeof(potionsList[0].name) / sizeof(char));
		fscanf_s(file, "%d", &potionsList[i].health, sizeof(int));
		fscanf_s(file, "%d", &potionsList[i].mana, sizeof(int));
		fscanf_s(file, "%d", &potionsList[i].price, sizeof(int));
	}

	fclose(file);
	return potionsList;
}
Ability* createAllAbilities(int& amount) {
	FILE* file;

	if (fopen_s(&file, "Abilities\\Abilities.txt", "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	fscanf_s(file, "%d", &amount, sizeof(int));

	Ability* ALLAbilities = (Ability*)malloc(amount * sizeof(Ability));
	for (int i = 0; i < amount; i++) {
		fscanf_s(file, "%d ", &ALLAbilities[i].ID, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].type, sizeof(int));
		fscanf_s(file, "%s ", &ALLAbilities[i].name, sizeof(ALLAbilities[0].name) / sizeof(char));
		fscanf_s(file, "%d ", &ALLAbilities[i].damage, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].buffedCharacteristic, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].buff, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].manaCost, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].staminaCost, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].cooldown, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].effect, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].duration, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].aoe, sizeof(int));
		fscanf_s(file, "%d ", &ALLAbilities[i].price, sizeof(int));
	}

	fclose(file);

	return ALLAbilities;
}



bool addWeaponToInventory(Weapon weapon, Weapon* weapons) {
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++)
		if (weapons[i].ID == 0) {
			weapons[i] = weapon;
			return true;
		}
	return false;
}
bool addArmorToInventory(Armor armor, Armor* armors) {
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++)
		if (armors[i].ID == 0) {
			armors[i] = armor;
			return true;
		}
	return false;
}
bool addPotionToInventory(Potion potion, Potion* potions) {
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++)
		if (potions[i].ID == 0) {
			potions[i] = potion;
			return true;
		}
	return false;
}
bool addAbilityToAbilities(Ability ability, Ability* abilities) {
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++)
		if (abilities[i].ID == 0) {
			abilities[i] = ability;
			return true;
		}
	return false;
}

Weapon takeWeaponFromInventory(Weapon* weapons, int itemIndex) {

	Weapon weapon = weapons[itemIndex];
	weapons[itemIndex] = createEmptyWeapon();
	return weapon;


}
Armor takeArmorFromInventory(Armor* armors, int itemIndex) {

	Armor armor = armors[itemIndex];
	armors[itemIndex] = createEmptyArmor();
	return armor;


}
Potion takePotionFromInventory(Potion* potions, int itemIndex) {

	Potion potion = potions[itemIndex];
	potions[itemIndex] = createEmptyPotion();
	return potion;


}
Ability takeAbilityFromList(Ability* abilities, int abilityIndex) {

	Ability ability = abilities[abilityIndex];
	abilities[abilityIndex] = createEmptyAbility();
	return ability;

}