#include "Fighting.h"

enum Result {
	CONTINUE,
	WIN,
	LOSE,
	ESCAPE
};


bool freeHeroes[4];
bool freeEnemies[4];
int heroesCooldowns[4][MAX_ABILITIES] = { 0 };
int enemiesCooldowns[4] = { 0 };

SDL_Event ev;

void saveMaxColldowns(Ability* abilities, int* cooldowns) {
	for (int i = 0; i < MAX_ABILITIES; i++) {
		if (abilities[i].ID != 0) cooldowns[i] = abilities[i].cooldown + 1;
	}
}
void setCooldownsToZero(Ability* abilities) {
	for (int i = 0; i < MAX_ABILITIES; i++) {
		abilities[i].cooldown = 0;
	}
}
void setCooldownsToMax(Ability* abilities, int* cooldowns) {
	for (int i = 0; i < MAX_ABILITIES; i++) {
		abilities[i].cooldown = cooldowns[i] - 1;
	}
}


void attack(Hero& attacker, Enemy& defender) {
	if (defender.armor == 0) defender.health -= attacker.damage + attacker.equipedWeapon.damage;
	else defender.health -= (attacker.damage + attacker.equipedWeapon.damage) * (100 - defender.armor) / 100;

	if (defender.health <= 0)
	{
		defender.health = 0;
		defender.status = DEAD;
	}
}
void attack(Enemy& attacker, Hero& defender) {
	if (defender.armor == 0) defender.health -= attacker.damage;
	else defender.health -= attacker.damage * (100 - defender.armor) / 100;

	if (defender.health <= 0)
	{
		defender.health = 0;
		defender.status = DEAD;
	}
}


void cast(Hero& attacker, Ability& ability, Enemy& defender) {
	defender.health -= ability.damage;
	attacker.mana -= ability.manaCost;
	attacker.stamina -= ability.staminaCost;
	if (ability.effect != NORMAL) defender.status = ability.effect;
	if (defender.health <= 0) {
		defender.health = 0;
		defender.status = DEAD;
	}

}
void cast(Hero& buffer, Ability& ability, Hero& duffed) {

}

void cast(Enemy& attacker, Ability& ability, Hero& defender) {

}

void usePotion(Hero& hero, Potion potion) {
	if (hero.health <= hero.maxHealth - potion.health) hero.health += potion.health;
	else hero.health = hero.maxHealth;
	if (hero.mana <= hero.maxMana - potion.mana) hero.mana += potion.mana;
	else hero.mana = hero.maxMana;
}

void increaseProtection(Hero& hero) {
	int increasing = 10;
	if (hero.heroClass == KNIGHT) increasing = 20;
	if (hero.armor + increasing >= 90) hero.armor = 90;
	else hero.armor += increasing;


}

void tryToEscape(Hero& hero) {
	int chance = random(1, 100);
	if (chance >= 50) hero.status == ESCAPED;
}
void tryToEscape(Enemy& enemy) {
	int chance = random(1, 100);
	if (chance >= 65) enemy.status == ESCAPED;
}

int playerAct(Player& player, EnemiesSquad& enemies) {
	int coursorPosition = 0, heroChoice, choice, enemyChoice;

	bool inHeroChoosing = true, inActionChoosing = false, inAction = false, inEnemyChoosing = false, inChoosing = false;

	for (int i = 0; i < 4; i++) {
		enemiesCooldowns[i] = enemies.enemies[i].ability.cooldown + 1;
		enemies.enemies[i].ability.cooldown = 0;
		saveMaxColldowns(player.team[i].abilities, heroesCooldowns[i]);
		setCooldownsToZero(player.team[i].abilities);
	}



	while (freeHeroes[0] || freeHeroes[1] || freeHeroes[2] || freeHeroes[3]) {
		for (int i = 0; i < 4; i++)
			if (player.team[i].status == DEAD || player.team[i].status == ESCAPED) freeHeroes[i] = false;

		if ((enemies.enemies[0].status == DEAD || enemies.enemies[0].status == ESCAPED) &&
			(enemies.enemies[1].status == DEAD || enemies.enemies[1].status == ESCAPED) &&
			(enemies.enemies[2].status == DEAD || enemies.enemies[2].status == ESCAPED) &&
			(enemies.enemies[3].status == DEAD || enemies.enemies[3].status == ESCAPED)) {
			//победа
			return WIN;
		}
		coursorPosition = 0;

		while (inHeroChoosing) {
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
						if (coursorPosition != 3) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						if (freeHeroes[coursorPosition])
						{
							heroChoice = coursorPosition;
							inHeroChoosing = false;
							inActionChoosing = true;


						}
						break;
					}

					break;
				}

			drawFightingScene(player, enemies, coursorPosition, 0);
		}
		coursorPosition = 0;
		while (inActionChoosing) {

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
						if (coursorPosition != 4) coursorPosition++;
						break;
					case SDL_SCANCODE_RETURN:
						choice = coursorPosition;
						inActionChoosing = false;
						inAction = true;
						coursorPosition = 0;
						break;
					case SDL_SCANCODE_ESCAPE:
						inActionChoosing = false;
						inHeroChoosing = true;
						break;
					}

					break;
				}

			drawFightingScene(player, enemies, coursorPosition, 1);

		}
		coursorPosition = 0;
		while (inAction) {

			switch (choice) {
			case 0:
#pragma region ATTACK
				inEnemyChoosing = true;
				while (inEnemyChoosing) {
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
								if (coursorPosition != 4) coursorPosition++;
								break;
							case SDL_SCANCODE_RETURN:
								if (enemies.enemies[coursorPosition].status != DEAD && enemies.enemies[coursorPosition].status != ESCAPED)
								{
									enemyChoice = coursorPosition;
									inEnemyChoosing = false;
									inAction = false;
									inHeroChoosing = true;
									freeHeroes[heroChoice] = false;

									attack(player.team[heroChoice], enemies.enemies[enemyChoice]);
								}
								break;
							case SDL_SCANCODE_ESCAPE:
								inEnemyChoosing = false;
								inAction = false;
								inActionChoosing = true;
								coursorPosition = 0;
								break;
							}

							break;
						}

					drawFightingScene(player, enemies, coursorPosition, 2);
				}
#pragma endregion
				break;
			case 1:
#pragma region ABILITY
				inChoosing = true;
				while (inChoosing) {

					while (SDL_PollEvent(&ev))
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
								if (player.team[heroChoice].mana >= player.team[heroChoice].abilities[coursorPosition].manaCost &&
									player.team[heroChoice].stamina >= player.team[heroChoice].abilities[coursorPosition].staminaCost &&
									player.team[heroChoice].abilities[coursorPosition].cooldown == 0) {
									choice = coursorPosition;
									inChoosing = false;
									inEnemyChoosing = true;
								}

								break;
							case SDL_SCANCODE_ESCAPE:
								inChoosing = false;
								inAction = false;
								inActionChoosing = true;
								break;
							}


							break;
						}

					drawHeroAbilities(player.team[heroChoice], coursorPosition);


				}
				if (player.team[heroChoice].abilities[choice].type == ATTACKING)
					while (inEnemyChoosing) {
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
									if (coursorPosition != 4) coursorPosition++;
									break;
								case SDL_SCANCODE_RETURN:
									if (enemies.enemies[coursorPosition].status != DEAD && enemies.enemies[coursorPosition].status != ESCAPED)
									{
										enemyChoice = coursorPosition;
										inEnemyChoosing = false;
										inAction = false;
										inHeroChoosing = true;
										freeHeroes[heroChoice] = false;
										coursorPosition = 0;
										cast(player.team[heroChoice], player.team[heroChoice].abilities[choice], enemies.enemies[enemyChoice]);
										player.team[heroChoice].abilities[choice].cooldown = heroesCooldowns[heroChoice][choice];
									}
									break;
								case SDL_SCANCODE_ESCAPE:
									inEnemyChoosing = false;
									inAction = false;
									inActionChoosing = true;
									coursorPosition = 0;
									break;
								}

								break;
							}

						drawFightingScene(player, enemies, coursorPosition, 2);
					}
				else
					while (inEnemyChoosing) {
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
									if (coursorPosition != 4) coursorPosition++;
									break;
								case SDL_SCANCODE_RETURN:
									if (enemies.enemies[coursorPosition].status != DEAD && enemies.enemies[coursorPosition].status != ESCAPED)
									{
										enemyChoice = coursorPosition;
										inEnemyChoosing = false;
										inAction = false;
										inHeroChoosing = true;
										freeHeroes[heroChoice] = false;
										coursorPosition = 0;
										cast(player.team[heroChoice], player.team[heroChoice].abilities[choice], player.team[enemyChoice]);
										player.team[heroChoice].abilities[choice].cooldown = heroesCooldowns[heroChoice][choice];
									}
									break;
								case SDL_SCANCODE_ESCAPE:
									inEnemyChoosing = false;
									inAction = false;
									inActionChoosing = true;
									coursorPosition = 0;
									break;
								}

								break;
							}

						drawFightingScene(player, enemies, coursorPosition, 0);
					}
#pragma endregion
				break;

			case 2:
#pragma region POTION
				inChoosing = true;
				while (inChoosing) {

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
								if ((player.potions[coursorPosition].health != 0 && player.team[heroChoice].health != player.team[heroChoice].maxHealth) ||
									(player.potions[coursorPosition].mana != 0 && player.team[heroChoice].mana != player.team[heroChoice].maxMana)) {
									choice = coursorPosition;
									inChoosing = false;
									inHeroChoosing = true;
									freeHeroes[heroChoice] = false;
									Potion usedPotion = takePotionFromInventory(player.potions, choice);
									usePotion(player.team[heroChoice], usedPotion);
								}

								break;
							case SDL_SCANCODE_ESCAPE:
								inChoosing = false;
								inAction = false;
								inActionChoosing = true;
								break;
							}


							break;
						}

					drawPlayerPotions(player, coursorPosition);


				}
#pragma endregion
				break;
			case 3:
				increaseProtection(player.team[heroChoice]);
				break;
			case 4:
				tryToEscape(player.team[heroChoice]);
				break;
			}
		}
	}
	if ((player.team[0].status == DEAD || player.team[0].status == ESCAPED) &&
		(player.team[1].status == DEAD || player.team[1].status == ESCAPED) &&
		(player.team[2].status == DEAD || player.team[2].status == ESCAPED) &&
		(player.team[3].status == DEAD || player.team[3].status == ESCAPED))
	{
		if (player.team[0].status == ESCAPED || player.team[1].status == ESCAPED || player.team[2].status == ESCAPED || player.team[3].status == ESCAPED) return ESCAPE;
		else return LOSE;
	}
	return CONTINUE;
}

int enemiesAct(Player& player, EnemiesSquad& enemies) {
	int heroChoice, enemyCoice = 0;

	while (freeEnemies[0] || freeEnemies[1] || freeEnemies[2] || freeEnemies[3]) {
		for (int i = 0; i < 4; i++)
			if (enemies.enemies[i].status == DEAD || enemies.enemies[i].status == ESCAPED) freeEnemies[i] = false;

		if ((player.team[0].status == DEAD || player.team[0].status == ESCAPED) &&
			(player.team[1].status == DEAD || player.team[1].status == ESCAPED) &&
			(player.team[2].status == DEAD || player.team[2].status == ESCAPED) &&
			(player.team[3].status == DEAD || player.team[3].status == ESCAPED)) {
			break;
		}
		do {
			enemyCoice = random(0, 3);

		} while (!freeEnemies[enemyCoice]);

		if (enemies.enemies[enemyCoice].ability.cooldown != 0 && 
			enemies.enemies[enemyCoice].mana >= enemies.enemies[enemyCoice].ability.manaCost && 
			enemies.enemies[enemyCoice].stamina >= enemies.enemies[enemyCoice].ability.staminaCost) {
			do {
				heroChoice = random(0, 3);
			} while (player.team[heroChoice].status == DEAD || player.team[heroChoice].status == ESCAPED);
			cast(enemies.enemies[enemyCoice], enemies.enemies[enemyCoice].ability, player.team[heroChoice]);
			freeEnemies[enemyCoice] = false;
		}
		else if (enemies.enemies[enemyCoice].health < 5) {
			tryToEscape(enemies.enemies[enemyCoice]);
			freeEnemies[enemyCoice] = false;
		}
		else {
			do {
				heroChoice = random(0, 3);
			} while (player.team[heroChoice].status == DEAD || player.team[heroChoice].status == ESCAPED);
			attack(enemies.enemies[enemyCoice], player.team[heroChoice]);
			freeEnemies[enemyCoice] = false;
		}
		drawFightingScene(player, enemies, 0, -1);
	}
	if ((player.team[0].status == DEAD || player.team[0].status == ESCAPED) &&
		(player.team[1].status == DEAD || player.team[1].status == ESCAPED) &&
		(player.team[2].status == DEAD || player.team[2].status == ESCAPED) &&
		(player.team[3].status == DEAD || player.team[3].status == ESCAPED)) {
		if (player.team[0].status == DEAD && player.team[1].status == DEAD && player.team[2].status == DEAD && player.team[3].status == DEAD) return LOSE;
		else return ESCAPE;
	}
	return CONTINUE;
}





void startBattle(Player& player, EnemiesSquad enemies) {

	int result = CONTINUE;
	int chance = random(1, 100);

	while (true) {

		//if ((player.team[0].status == DEAD || player.team[0].status == ESCAPED) &&
		//	(player.team[1].status == DEAD || player.team[1].status == ESCAPED) &&
		//	(player.team[2].status == DEAD || player.team[2].status == ESCAPED) &&
		//	(player.team[3].status == DEAD || player.team[3].status == ESCAPED)) {
		//	//победа
		//}

		if (chance >= 60 && result == CONTINUE)
		{
			for (int i = 0; i < 4; i++) freeHeroes[i] = true;
			result = playerAct(player, enemies);
		}

		if (result == WIN) {
			//победа
			return;
		}
		if (result == ESCAPE) {
			//побег
			return;
		}
		if (result == LOSE) {
			//поражение
			return;
		}

		if (chance >= 60) SDL_Delay(2500);
		chance = 100;
		if (result == CONTINUE) {
			for (int i = 0; i < 4; i++) freeEnemies[i] = true;
			result = enemiesAct(player, enemies);
		}

		if (result == WIN) {
			//победа
			return;
		}

		if (result == ESCAPE) {
			//побег
			return;
		}

		if (result == LOSE) {
			//поражение
			return;
		}






	}



}