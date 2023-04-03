#include "Basic.h"

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
//Ability createEmptyAbility() {
//	Ability empty;
//	empty.damage = 0;
//	empty.manaCost = 0;
//	empty.cooldown = 0;
//	empty.ID = 0;
//	empty.price = 0;
//	empty.type = -1;
//	empty.buff = 0;
//	empty.buffedCharacteristic = -1;
//	empty.aoe = 0;
//	empty.duration = 0;
//	for (int i = 0; i < 15; i++)
//		empty.name[i] = ' ';
//	return empty;
//}
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