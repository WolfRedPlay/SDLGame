#include "Save.h"

Weapon* scanIDWeapons(FILE* file, int& size) {
	fscanf_s(file, "%d", &size, sizeof(int));
	Weapon* weaponsList = (Weapon*)malloc(size * sizeof(Weapon));
	for (int i = 0; i < size; i++)
		fscanf_s(file, "%d ", &weaponsList[i].ID, sizeof(int));


	return weaponsList;
}
Armor* scanIDArmors(FILE* file, int& size) {

	fscanf_s(file, "%d", &size, sizeof(int));
	Armor* armorsList = (Armor*)malloc(size * sizeof(Armor));
	for (int i = 0; i < size; i++)
		fscanf_s(file, "%d ", &armorsList[i].ID, sizeof(int));


	return armorsList;
}
Potion* scanIDPotions(FILE* file, int& size) {

	fscanf_s(file, "%d ", &size, sizeof(int));
	Potion* potionsList = (Potion*)malloc(size * sizeof(Potion));
	for (int i = 0; i < size; i++) {
		fscanf_s(file, "%d ", &potionsList[i].ID, sizeof(int));
	}


	return potionsList;
}
Ability* scanIDAbilities(FILE* file, int& size) {
	fscanf_s(file, "%d ", &size);
	Ability* list = (Ability*)malloc(size * sizeof(Ability));
	for (int i = 0; i < size; i++)
		fscanf_s(file, "%d ", &list[i].ID);

	return list;
}
//Quest* scanQuests(FILE* file, int& size) {
//	fscanf_s(file, "%d ", &size);
//	Quest* list = (Quest*)malloc(size * sizeof(Quest));
//	for (int i = 0; i < size; i++)
//		fscanf_s(file, "%d ", &list[i].requiredItem.ID);
//
//	return list;
//}
//QuestItem* ScanIDQuestItems(FILE* file, int& size) {
//	fscanf_s(file, "%d", &size);
//	QuestItem* list = (QuestItem*)malloc(size * sizeof(QuestItem));
//	for (int i = 0; i < size; i++)
//		fscanf_s(file, "%d", &list[i].ID);
//
//	return list;
//}














void fillPlayerWeapons(Player& player, int currentWeaponInventorySize, Weapon* currentWeapons) {
	for (int i = 0; i < currentWeaponInventorySize; i++)
		addWeaponToInventory(findInWeaponsList(ALLWeaponsList, currentWeapons[i].ID, qountOfWeapons), player.weapons);
}
void fillPlayerArmors(Player& player, int currentArmorInventorySize, Armor* currentArmors) {
	for (int i = 0; i < currentArmorInventorySize; i++)
		addArmorToInventory(findInArmorsList(ALLArmorsList, currentArmors[i].ID, qountOfArmors), player.armors);
}
void fillPlayerPotions(Player& player, int currentPotionInventorySize, Potion* currentPotions) {
	for (int i = 0; i < currentPotionInventorySize; i++)
		addPotionToInventory(findInPotionsList(ALLPotionsList, currentPotions[i].ID, qountOfPotions), player.potions);
}
void fillHeroAbilities(Hero& hero, int currentAbilityInventorySize, Ability* currentAbilities) {
	for (int i = 0; i < currentAbilityInventorySize; i++)
		addAbilityToAbilities(findInAbilitiesList(ALLAbilitiesList, currentAbilities[i].ID, qountOfAbilities), hero.abilities);
}
//void fillPlayerQuestItems(Player& player, int currentQuestItemInventorySize, QuestItem* currentQuestItems) {
//
//	int qountOfQuestItems;
//
//	QuestItem* ALLQuestItemsList = createAllQuestItems(qountOfQuestItems);
//	for (int i = 0; i < currentQuestItemInventorySize; i++)
//		addQuestItemToInventory(findInQuestItemsList(ALLQuestItemsList, currentQuestItems[i].ID, qountOfQuestItems), player.questItems);
//}
//void fillPlayerQuests(Player& player, int currentQuestInventorySize, Quest* currentQuests) {
//
//	int qountOfQuests;
//	Quest* ALLQuestsList = createAllQuests(qountOfQuests);
//	for (int i = 0; i < currentQuestInventorySize; i++)
//		addQuestToList(findQuestInList(ALLQuestsList, currentQuests[i].requiredItem.ID, qountOfQuests), player.quests);
//}





void setSaves(const char* fn, Player player) {
	int currentSize = 0;
	FILE* saveFile;

	if (fopen_s(&saveFile, fn, "wt") != 0) {
		printf_s("Can not find saves\n");
		exit(1);
	}

	for (int i = 0; i < 4; i++) {
		fprintf_s(saveFile, "%s ", player.team[i].name);
		fprintf_s(saveFile, "%d ", player.team[i].heroClass);
		fprintf_s(saveFile, "%d ", player.team[i].maxHealth);
		fprintf_s(saveFile, "%d ", player.team[i].health);
		fprintf_s(saveFile, "%d ", player.team[i].damage);
		fprintf_s(saveFile, "%d ", player.team[i].armor);
		fprintf_s(saveFile, "%d ", player.team[i].maxMana);
		fprintf_s(saveFile, "%d ", player.team[i].mana);
		fprintf_s(saveFile, "%d ", player.team[i].maxStamina);
		fprintf_s(saveFile, "%d ", player.team[i].stamina);
		fprintf_s(saveFile, "%d ", player.team[i].lvl);
		fprintf_s(saveFile, "%d ", player.team[i].exp);
		fprintf_s(saveFile, "%d ", player.team[i].status);
		fprintf_s(saveFile, "%d ", player.team[i].equipedWeapon.ID);
		fprintf_s(saveFile, "%d\n", player.team[i].equipedArmor.ID);

		currentSize = 0;
		for (int j = 0; j < MAX_ABILITIES; j++)
			if (player.team[i].abilities[j].ID != 0)
				currentSize++;
		fprintf_s(saveFile, "%d ", currentSize);
		for (int j = 0; j < currentSize; j++)
			fprintf_s(saveFile, "%d ", player.team[i].abilities[j].ID);
		fprintf_s(saveFile, "\n");
	}



	currentSize = 0;
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++)
		if (player.weapons[i].ID != 0)
			currentSize++;
	fprintf_s(saveFile, "%d ", currentSize);
	for (int i = 0; i < currentSize; i++)
		fprintf_s(saveFile, "%d ", player.weapons[i].ID);
	fprintf_s(saveFile, "\n");

	currentSize = 0;
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++)
		if (player.armors[i].ID != 0)
			currentSize++;
	fprintf_s(saveFile, "%d ", currentSize);
	for (int i = 0; i < currentSize; i++)
		fprintf_s(saveFile, "%d ", player.armors[i].ID);
	fprintf_s(saveFile, "\n");

	currentSize = 0;
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++)
		if (player.potions[i].ID != 0)
			currentSize++;
	fprintf_s(saveFile, "%d ", currentSize);
	for (int i = 0; i < currentSize; i++)
		fprintf_s(saveFile, "%d ", player.potions[i].ID);
	fprintf_s(saveFile, "\n");



	/*currentSize = 0;
	for (int i = 0; i < MAX_QUESTS; i++)
		if (player.quests[i].requiredItem.ID != 0)
			currentSize++;
	fprintf_s(saveFile, "%d ", currentSize);
	for (int i = 0; i < currentSize; i++)
		fprintf_s(saveFile, "%d ", player.quests[i].requiredItem.ID);

	fprintf_s(saveFile, "\n");

	currentSize = 0;
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++)
		if (player.questItems[i].ID != 0)
			currentSize++;
	fprintf_s(saveFile, "%d ", currentSize);
	for (int i = 0; i < currentSize; i++)
		fprintf_s(saveFile, "%d ", player.questItems[i].ID);
	fprintf_s(saveFile, "\n");*/

	fprintf_s(saveFile, "%d ", player.money);
	fprintf_s(saveFile, "%d\n", player.keys);

	fprintf_s(saveFile, "%.3f ", player.position.X);
	fprintf_s(saveFile, "%.3f\n", player.position.Y);
	fprintf_s(saveFile, "%d", player.currentLocation);

	fclose(saveFile);


}
//void setQuestsSaves(const char* fn, Quest* quests, int amountQuests) {
//	FILE* saveFile;
//	int completedQuestsAmount = 0;
//	if (fopen_s(&saveFile, fn, "wt") != 0) {
//		printf_s("Can not find saves\n");
//		exit(1);
//	}
//
//	for (int i = 0; i < amountQuests; i++)
//		if (quests[i].isCompleted) completedQuestsAmount++;
//	fprintf_s(saveFile, "%d\n", completedQuestsAmount);
//	for (int i = 0; i < amountQuests; i++)
//		if (quests[i].isCompleted) fprintf_s(saveFile, "%d ", quests[i].requiredItem.ID);
//
//	fclose(saveFile);
//
//}
void setMapSaves(const char* fn, char** map) {
	FILE* saveFile;

	if (fopen_s(&saveFile, fn, "wt") != 0) {
		printf_s("Can not find saves\n");
		exit(1);
	}

	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X; j++)
			fprintf_s(saveFile, "%c", map[i][j]);
	}

	fclose(saveFile);
}


void loadSaves(const char* fn, Player& player) {


	clearPlayer(player);

	FILE* saveFile;
	int currentWeaponInventorySize, currentArmorInventorySize, currentPotionInventorySize;
	int currentQuestsInentorySize, currentAbilitiesListSize, currentQuestItemInventorySize;



	int weaponID, armorID;


	if (fopen_s(&saveFile, fn, "rt") != 0) {
		printf_s("Can not find saves\n");
		exit(1);
	}

	for (int i = 0; i < 4; i++) {
		fscanf_s(saveFile, "%s ", player.team[i].name, sizeof(player.team[0].name) / sizeof(char));
		fscanf_s(saveFile, "%d ", &player.team[i].heroClass);
		fscanf_s(saveFile, "%d ", &player.team[i].maxHealth);
		fscanf_s(saveFile, "%d ", &player.team[i].health);
		fscanf_s(saveFile, "%d ", &player.team[i].damage);
		fscanf_s(saveFile, "%d ", &player.team[i].armor);
		fscanf_s(saveFile, "%d ", &player.team[i].maxMana);
		fscanf_s(saveFile, "%d ", &player.team[i].mana);
		fscanf_s(saveFile, "%d ", &player.team[i].maxStamina);
		fscanf_s(saveFile, "%d ", &player.team[i].stamina);
		fscanf_s(saveFile, "%d ", &player.team[i].lvl);
		fscanf_s(saveFile, "%d ", &player.team[i].exp);
		fscanf_s(saveFile, "%d ", &player.team[i].status);


		fscanf_s(saveFile, "%d ", &weaponID);
		fscanf_s(saveFile, "%d\n", &armorID);

		player.team[i].equipedWeapon = findInWeaponsList(ALLWeaponsList, weaponID, qountOfWeapons);
		player.team[i].equipedArmor = findInArmorsList(ALLArmorsList, armorID, qountOfArmors);


		Ability* currentAbilities = scanIDAbilities(saveFile, currentAbilitiesListSize);

		fillHeroAbilities(player.team[i], currentAbilitiesListSize, currentAbilities);

		switch (player.team[i].heroClass) {
		case KNIGHT: 
			player.team[i].texture = generateTextureFromPNG("Textures\\Knight.png");
			break;
		case ROGUE: 
			player.team[i].texture = generateTextureFromPNG("Textures\\Inkeeper.png");
			break;
		case MAGE: 
			player.team[i].texture = generateTextureFromPNG("Textures\\Mage.png");
			break;
		case HEALER: 
			player.team[i].texture = generateTextureFromPNG("Textures\\Sell_potion.png");
			break;
		}
	}


	Weapon* currentWeapons = scanIDWeapons(saveFile, currentWeaponInventorySize);
	fillPlayerWeapons(player, currentWeaponInventorySize, currentWeapons);
	Armor* currentArmors = scanIDArmors(saveFile, currentArmorInventorySize);
	fillPlayerArmors(player, currentArmorInventorySize, currentArmors);
	Potion* currentPotions = scanIDPotions(saveFile, currentPotionInventorySize);
	fillPlayerPotions(player, currentPotionInventorySize, currentPotions);
	/*Quest* currentQuests = scanQuests(saveFile, currentQuestsInentorySize);
	fillPlayerQuests(player, currentQuestsInentorySize, currentQuests);
	QuestItem* currentQuestItems = ScanIDQuestItems(saveFile, currentQuestItemInventorySize);
	fillPlayerQuestItems(player, currentQuestItemInventorySize, currentQuestItems);*/
	fscanf_s(saveFile, "%d ", &player.money);
	fscanf_s(saveFile, "%d\n", &player.keys);

	fscanf_s(saveFile, "%f ", &player.position.X);
	fscanf_s(saveFile, "%f\n", &player.position.Y);
	fscanf_s(saveFile, "%d\n", &player.currentLocation);

	fclose(saveFile);


}
