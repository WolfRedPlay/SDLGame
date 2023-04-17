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
		printf_s("Openning file error map!!!\a");
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

NPC* createNPCs(int location) {
	NPC* NPCs;
	if (location == 1) {
		NPCs = (NPC*)malloc(NPC_AMOUNT_1 * sizeof(NPC));
		NPCs[0].position = { 16, 3 };
		NPCs[1].position = { 24, 3 };
		NPCs[2].position = { 20, 10 };
		NPCs[3].position = { 25, 15 };

		NPCs[0].texture = generateTextureFromPNG("Textures\\NPC.png");
		NPCs[1].texture = generateTextureFromPNG("Textures\\NPC.png");
		NPCs[2].texture = generateTextureFromPNG("Textures\\NPC.png");
		NPCs[3].texture = generateTextureFromPNG("Textures\\NPC.png");

		NPCs[0].phrase = 1;
		NPCs[1].phrase = 2;
		NPCs[2].phrase = 3;
		NPCs[3].phrase = 4;
	}
	else
		NPCs = (NPC*)malloc(NPC_AMOUNT_1 * sizeof(NPC));
	return NPCs;
}
QuestNPC* createQuestNPCs(int location) {
	QuestNPC* NPCs;

	int questsCount;

	Quest* ALLQuestsList = createAllQuests(questsCount);

	if (location == 1) {
		NPCs = (QuestNPC*)malloc(QUEST_NPC_AMOUNT_1 * sizeof(QuestNPC));
		NPCs[0].position = { 5, 10 };

		NPCs[0].texture = generateTextureFromPNG("Textures\\Older.png");

		NPCs[0].quest = ALLQuestsList[0];
	}
	else
		NPCs = (QuestNPC*)malloc(QUEST_NPC_AMOUNT_1 * sizeof(QuestNPC));
	free(ALLQuestsList);
	
	return NPCs;
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
QuestItem createEmptyQuestItem() {
	QuestItem empty;
	empty.ID = 0;
	for (int i = 0; i < 15; i++)
		empty.name[i] = ' ';
	return empty;
}
Quest createEmptyQuest() {
	Quest empty;
	empty.requiredItem = createEmptyQuestItem();
	for (int i = 0; i < 15; i++)
		empty.name[i] = ' ';
	empty.expReward = 0;
	empty.moneyReward = 0;
	return empty;
}
Hero createEmptyHero() {
	Hero empty;
	for (int i = 0; i < MAX_ABILITIES; i++) {
		empty.abilities[i] = createEmptyAbility();
	}
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
Enemy createEmptyEnemy() {
	Enemy empty;
	/*for (int i = 0; i < MAX_ABILITIES; i++) {
	}*/
	empty.ability = createEmptyAbility();
	empty.armor = 0;
	empty.damage = 0;
	empty.IDarmorDrop = 0;
	empty.IDpotionDrop = 0;
	empty.health = 0;
	empty.mana = 0;
	empty.stamina = 0;
	empty.IDweaponDrop = 0;
	empty.ID = 0;
	empty.moneyDrop = 0;

	for (int i = 0; i < MAX_NAME_LENGTH; i++)
		empty.name[i] = ' ';
	return empty;
}





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

	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		player.questItems[i] = createEmptyQuestItem();
	}
	for (int i = 0; i < MAX_QUESTS; i++) {
		player.quests[i] = createEmptyQuest();
	}
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
Quest findQuestInList(Quest* ALLQuestsList, int ID, int numQuests) {
	if (ID == 0) return createEmptyQuest();
	for (int i = 0; i < numQuests; i++)
		if (ALLQuestsList[i].requiredItem.ID == ID) return ALLQuestsList[i];
}
QuestItem findInQuestItemsList(QuestItem* ALLQuestItemsList, int ID, int numQuestItems) {
	if (ID == 0) return createEmptyQuestItem();
	for (int i = 0; i < numQuestItems; i++)
		if (ALLQuestItemsList[i].ID == ID) return ALLQuestItemsList[i];
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
		printf_s("Openning file error weapons!!!\a");
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
		printf_s("Openning file error armors!!!\a");
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
QuestItem* createAllQuestItems(int& amount) {

	FILE* file;

	if (fopen_s(&file, "Items\\QuestItems.txt", "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	fscanf_s(file, "%d", &amount, sizeof(int));
	QuestItem* questItemList = (QuestItem*)malloc(amount * sizeof(QuestItem));
	for (int i = 0; i < amount; i++) {
		fscanf_s(file, "%d ", &questItemList[i].ID, sizeof(int));
		fscanf_s(file, "%s ", &questItemList[i].name, sizeof(questItemList[0].name) / sizeof(char));

	}

	fclose(file);
	return questItemList;
}
Quest* createAllQuests(int& amount) {

	FILE* file;
	int itemID;
	int qountOfQustItems;
	QuestItem* ALLQuestItemsList = createAllQuestItems(qountOfQustItems);



	if (fopen_s(&file, "Quests\\Quests.txt", "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	fscanf_s(file, "%d", &amount, sizeof(int));
	Quest* questsList = (Quest*)malloc(amount * sizeof(Quest));
	for (int i = 0; i < amount; i++) {
		fscanf_s(file, "%d ", &itemID, sizeof(int));
		questsList[i].requiredItem = findInQuestItemsList(ALLQuestItemsList, itemID, qountOfQustItems);
		fscanf_s(file, "%s ", &questsList[i].name, sizeof(questsList[0].name) / sizeof(char));
		fscanf_s(file, "%d ", &questsList[i].moneyReward, sizeof(int));
		fscanf_s(file, "%d ", &questsList[i].expReward, sizeof(int));
		questsList[i].isCompleted = false;

	}

	fclose(file);
	return questsList;
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
Enemy* createAllEnemies(int& amount) {

	int qountOfAbilities;
	Ability* ALLAbilitiesList = createAllAbilities(qountOfAbilities);
	FILE* file;
	if (fopen_s(&file, "Enemies\\Enemies.txt", "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	fscanf_s(file, "%d", &amount, sizeof(int));
	Enemy* enemiesList = (Enemy*)malloc(amount * sizeof(Enemy));
	for (int i = 0; i < amount; i++) {
		fscanf_s(file, "%d ", &enemiesList[i].ID, sizeof(int));
		fscanf_s(file, "%s ", &enemiesList[i].name, sizeof(enemiesList[0].name) / sizeof(char));
		fscanf_s(file, "%d ", &enemiesList[i].health, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].mana, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].stamina, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].lvl, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].damage, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].armor, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].IDweaponDrop, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].IDarmorDrop, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].IDpotionDrop, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].moneyDrop, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].expDrop, sizeof(int));
		fscanf_s(file, "%d ", &enemiesList[i].ability.ID, sizeof(int));
		enemiesList[i].status = NORMAL;
		enemiesList[i].ability = findInAbilitiesList(ALLAbilitiesList, enemiesList[i].ability.ID, qountOfAbilities);
		enemiesList[i].texture = generateTextureFromPNG("Textures\\Older.png");
	}

	fclose(file);
	return enemiesList;
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
bool addQuestToList(Quest quest, Quest* quests) {
	for (int i = 0; i < MAX_QUESTS; i++)
		if (quests[i].requiredItem.ID == 0) {
			quests[i] = quest;
			return true;
		}
	return false;
}
bool addQuestItemToInventory(QuestItem item, QuestItem* items) {
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++)
		if (items[i].ID == 0) {
			items[i] = item;
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
Quest takeQuestFromList(Quest* questsList, int questIndex) {

	Quest quest = questsList[questIndex];
	questsList[questIndex] = createEmptyQuest();
	return quest;


}
QuestItem takeQuestItemFromInventory(QuestItem* items, int itemIndex) {
	QuestItem item = items[itemIndex];
	items[itemIndex] = createEmptyQuestItem();
	return item;
}
Ability takeAbilityFromList(Ability* abilities, int abilityIndex) {

	Ability ability = abilities[abilityIndex];
	abilities[abilityIndex] = createEmptyAbility();
	return ability;

}

