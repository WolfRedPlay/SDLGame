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
int burnTimers[8] = { 0 };
int poisonTimers[8] = { 0 };

SDL_Event ev;

void saveMaxColldowns(Ability* abilities, int* cooldowns) {
	for (int i = 0; i < MAX_ABILITIES; i++) {
		if (abilities[i].ID != 0) cooldowns[i] = abilities[i].cooldown + 1;
	}
}
void setCooldownsToZero(Ability* abilities) {
	for (int i = 0; i < MAX_ABILITIES; i++) {
		if (abilities[i].ID != 0)abilities[i].cooldown = 0;
	}
}
void setCooldownsToMax(Ability* abilities, int* cooldowns) {
	for (int i = 0; i < MAX_ABILITIES; i++) {
		if (abilities[i].ID != 0)abilities[i].cooldown = cooldowns[i] - 1;
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
void cast(Hero& attacker, Ability& ability, EnemiesSquad& defender) {
	for (int i = 0; i < 4; i++) {
		if (defender.enemies[i].status != DEAD && defender.enemies[i].status != ESCAPED)
		{
			defender.enemies[i].health -= ability.damage;
			if (ability.effect != NORMAL) defender.enemies[i].status = ability.effect;
			if (defender.enemies[i].health <= 0) {
				defender.enemies[i].health = 0;
				defender.enemies[i].status = DEAD;
			}
		}
	}
	attacker.mana -= ability.manaCost;
	attacker.stamina -= ability.staminaCost;


}
void cast(Hero& buffer, Ability& ability, Hero& buffed) {
	buffer.mana -= ability.manaCost;
	buffer.stamina -= ability.staminaCost;
	if (ability.buffedCharacteristic == HEALTH) {
		if (buffed.health <= buffed.maxHealth - ability.buff)buffed.health += ability.buff;
		else buffed.health = buffed.maxHealth;
	}
	if (ability.buffedCharacteristic == ARMOR) {
		if (buffed.armor <= 100 - ability.buff)buffed.armor += ability.buff;
		else buffed.armor = 100;
	}
	if (ability.buffedCharacteristic == DAMAGE) {
		buffed.damage += ability.buff;
	}
}
void cast(Hero& buffer, Ability& ability, Hero buffed[4]) {
	buffer.mana -= ability.manaCost;
	buffer.stamina -= ability.staminaCost;
	if (ability.buffedCharacteristic == HEALTH)
		for (int i = 0; i < 4; i++)
		{
			if (buffed[i].status != DEAD && buffed[i].status != ESCAPED)
			{
				if (buffed[i].health <= buffed[i].maxHealth - ability.buff)buffed[i].health += ability.buff;
				else buffed[i].health = buffed[i].maxHealth;
			}
		}
	if (ability.buffedCharacteristic == ARMOR)
		for (int i = 0; i < 4; i++) {
			if (buffed[i].status != DEAD && buffed[i].status != ESCAPED)
			{
				if (buffed[i].armor <= 100 - ability.buff)buffed[i].armor += ability.buff;
				else buffed[i].armor = 100;
			}
		}
	if (ability.buffedCharacteristic == DAMAGE)
		for (int i = 0; i < 4; i++)
		{
			if (buffed[i].status != DEAD && buffed[i].status != ESCAPED)
				buffed[i].damage += ability.buff;
		}
}
void cast(Enemy& attacker, Ability& ability, Hero& defender) {
	defender.health -= ability.damage;
	attacker.mana -= ability.manaCost;
	attacker.stamina -= ability.staminaCost;
	if (ability.effect != NORMAL) defender.status = ability.effect;
	if (defender.health <= 0) {
		defender.health = 0;
		defender.status = DEAD;
	}

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
		if (player.team[i].status == BURN) {
			if (burnTimers[i] == 5)
			{
				burnTimers[i] = 0;
				player.team[i].status = NORMAL;
			}
			else burnTimers[i]++;
			player.team[i].health -= 10;
		}
		if (player.team[i].status == POISONED) {
			if (poisonTimers[i] == 8)
			{
				poisonTimers[i] = 0;
				player.team[i].status = NORMAL;
			}
			else poisonTimers[i]++;
			player.team[i].health -= 6;
		}
		if (player.team[i].status == STUNED) {
			freeHeroes[i] = false;

		}
	}

	for (int i = 0; i < 4; i++) {
		if (enemies.enemies[i].status == STUNED) enemies.enemies[i].status = NORMAL;
	}

	for (int i = 0; i < 4; i++)
		if (player.team[i].status == DEAD || player.team[i].status == ESCAPED) freeHeroes[i] = false;

	while (freeHeroes[0] || freeHeroes[1] || freeHeroes[2] || freeHeroes[3]) {

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
								if (coursorPosition != 3) coursorPosition++;
								break;
							case SDL_SCANCODE_RETURN:
								if (enemies.enemies[coursorPosition].status != DEAD && enemies.enemies[coursorPosition].status != ESCAPED)
								{
									enemyChoice = coursorPosition;
									inEnemyChoosing = false;
									inAction = false;
									inHeroChoosing = true;
									freeHeroes[heroChoice] = false;
									attackAnimation(player, enemies, heroChoice, enemyChoice);
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
				{
					if (player.team[heroChoice].abilities[choice].aoe) {
						inEnemyChoosing = false;
						inAction = false;
						inHeroChoosing = true;
						freeHeroes[heroChoice] = false;
						coursorPosition = 0;
						cast(player.team[heroChoice], player.team[heroChoice].abilities[choice], enemies);
						player.team[heroChoice].abilities[choice].cooldown = heroesCooldowns[heroChoice][choice];
					}
					else
					{
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
					}
				}
				else
				{
					if (player.team[heroChoice].abilities[choice].aoe) {
						inEnemyChoosing = false;
						inAction = false;
						inHeroChoosing = true;
						freeHeroes[heroChoice] = false;
						coursorPosition = 0;
						cast(player.team[heroChoice], player.team[heroChoice].abilities[choice], player.team);
						player.team[heroChoice].abilities[choice].cooldown = heroesCooldowns[heroChoice][choice];
					}
					else {
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
										if (player.team[coursorPosition].status != DEAD && player.team[coursorPosition].status != ESCAPED)
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
					}
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
				freeHeroes[heroChoice] = false;
				inAction = false;
				inHeroChoosing = true;
				break;
			case 4:
				tryToEscape(player.team[heroChoice]);
				freeHeroes[heroChoice] = false;
				inAction = false;
				inHeroChoosing = true;
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
int playerAct(Player& player, Enemy& boss) {
	int coursorPosition = 0, heroChoice, choice, enemyChoice;

	bool inHeroChoosing = true, inActionChoosing = false, inAction = false, inEnemyChoosing = false, inChoosing = false, isChoosen = false;


	for (int i = 0; i < 4; i++) {
		if (player.team[i].status == BURN) {
			if (burnTimers[i] == 5)
			{
				burnTimers[i] = 0;
				player.team[i].status = NORMAL;
			}
			else burnTimers[i]++;
			player.team[i].health -= 10;
		}
		if (player.team[i].status == POISONED) {
			if (poisonTimers[i] == 8)
			{
				poisonTimers[i] = 0;
				player.team[i].status = NORMAL;
			}
			else poisonTimers[i]++;
			player.team[i].health -= 6;
		}
		if (player.team[i].status == STUNED) {
			freeHeroes[i] = false;

		}
	}

	for (int i = 0; i < 4; i++) {
		if (boss.status == STUNED) boss.status = NORMAL;
	}

	for (int i = 0; i < 4; i++)
		if (player.team[i].status == DEAD || player.team[i].status == ESCAPED) freeHeroes[i] = false;

	while (freeHeroes[0] || freeHeroes[1] || freeHeroes[2] || freeHeroes[3]) {

		if (boss.status == DEAD) {
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

			drawFightingScene(player, boss, coursorPosition, 0);
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

			drawFightingScene(player, boss, coursorPosition, 1);

		}
		coursorPosition = 0;
		while (inAction) {

			switch (choice) {
			case 0:
#pragma region ATTACK
				inAction = false;
				inHeroChoosing = true;
				freeHeroes[heroChoice] = false;
				attack(player.team[heroChoice], boss);
				//анимация
#pragma endregion
				break;
			case 1:
#pragma region ABILITY
				inChoosing = true;
				isChoosen = false;
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
									isChoosen = true;
									inEnemyChoosing = true;
								}

								break;
							case SDL_SCANCODE_ESCAPE:
								inChoosing = false;
								isChoosen = false;
								inAction = false;
								inActionChoosing = true;
								break;
							}


							break;
						}

					drawHeroAbilities(player.team[heroChoice], coursorPosition);


				}
				if (isChoosen){
					if (player.team[heroChoice].abilities[choice].type == ATTACKING)
					{
						inAction = false;
						inHeroChoosing = true;
						freeHeroes[heroChoice] = false;
						coursorPosition = 0;
						cast(player.team[heroChoice], player.team[heroChoice].abilities[choice], boss);
						player.team[heroChoice].abilities[choice].cooldown = heroesCooldowns[heroChoice][choice];
					}
					else
					{
						if (player.team[heroChoice].abilities[choice].aoe) {
							inEnemyChoosing = false;
							inAction = false;
							inHeroChoosing = true;
							freeHeroes[heroChoice] = false;
							coursorPosition = 0;
							cast(player.team[heroChoice], player.team[heroChoice].abilities[choice], player.team);
							player.team[heroChoice].abilities[choice].cooldown = heroesCooldowns[heroChoice][choice];
						}
						else {
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
											if (player.team[coursorPosition].status != DEAD && player.team[coursorPosition].status != ESCAPED)
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

								drawFightingScene(player, boss, coursorPosition, 0);
							}
						}
					}
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
				freeHeroes[heroChoice] = false;
				inAction = false;
				inHeroChoosing = true;
				break;
			case 4:
				tryToEscape(player.team[heroChoice]);
				freeHeroes[heroChoice] = false;
				inAction = false;
				inHeroChoosing = true;
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


	for (int i = 0; i < 4; i++) {
		if (enemies.enemies[i].status == BURN) {
			if (burnTimers[i + 4] == 5)
			{
				burnTimers[i + 4] = 0;
				enemies.enemies[i].status = NORMAL;
			}
			else burnTimers[i + 4]++;
			enemies.enemies[i].health -= 10;
		}
		if (enemies.enemies[i].status == POISONED) {
			if (poisonTimers[i + 4] == 8)
			{
				poisonTimers[i + 4] = 0;
				enemies.enemies[i].status = NORMAL;
			}
			else poisonTimers[i + 4]++;
			enemies.enemies[i].health -= 6;
		}
		if (enemies.enemies[i].status == STUNED) {
			freeEnemies[i] = false;

		}
	}

	for (int i = 0; i < 4; i++) {
		if (player.team[i].status == STUNED) player.team[i].status = NORMAL;
	}

	for (int i = 0; i < 4; i++)
		if (enemies.enemies[i].status == DEAD || enemies.enemies[i].status == ESCAPED) freeEnemies[i] = false;
	while (freeEnemies[0] || freeEnemies[1] || freeEnemies[2] || freeEnemies[3]) {

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
			enemies.enemies[enemyCoice].ability.cooldown = enemiesCooldowns[enemyCoice];
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
int enemiesAct(Player& player, Enemy& boss) {
	int heroChoice;


		if (boss.status == BURN) {
			if (burnTimers[4] == 5)
			{
				burnTimers[4] = 0;
				boss.status = NORMAL;
			}
			else burnTimers[4]++;
			boss.health -= 10;
		}
		if (boss.status == POISONED) {
			if (poisonTimers[4] == 8)
			{
				poisonTimers[4] = 0;
				boss.status = NORMAL;
			}
			else poisonTimers[4]++;
			boss.health -= 6;
		}
		if (boss.status == STUNED) {
			freeEnemies[0] = false;

		}


	for (int i = 0; i < 4; i++) {
		if (player.team[i].status == STUNED) player.team[i].status = NORMAL;
	}

		if (boss.status == DEAD) freeEnemies[0] = false;
	while (freeEnemies[0]) {

		if ((player.team[0].status == DEAD || player.team[0].status == ESCAPED) &&
			(player.team[1].status == DEAD || player.team[1].status == ESCAPED) &&
			(player.team[2].status == DEAD || player.team[2].status == ESCAPED) &&
			(player.team[3].status == DEAD || player.team[3].status == ESCAPED)) {
			break;
		}

		if (boss.ability.cooldown != 0 &&
			boss.mana >= boss.ability.manaCost &&
			boss.stamina >= boss.ability.staminaCost) {
			do {
				heroChoice = random(0, 3);
			} while (player.team[heroChoice].status == DEAD || player.team[heroChoice].status == ESCAPED);
			cast(boss, boss.ability, player.team[heroChoice]);
			boss.ability.cooldown = enemiesCooldowns[0];
			freeEnemies[0] = false;
		}
		else {
			do {
				heroChoice = random(0, 3);
			} while (player.team[heroChoice].status == DEAD || player.team[heroChoice].status == ESCAPED);
			attack(boss, player.team[heroChoice]);
			freeEnemies[0] = false;
		}
		drawFightingScene(player, boss, 0, -1);
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

void win(Player& player, EnemiesSquad& enemies) {
	int chance = 0;
	bool deadEnemies[4];
	for (int i = 0; i < 4; i++) {
		if (enemies.enemies[i].status == DEAD) deadEnemies[i] = true;
		else deadEnemies[i] = false;
	}

	for (int i = 0; i < 4; i++) {
		if (deadEnemies[i]) {
			chance = random(1, 100);
			if (chance >= 50) {
				Weapon givedWeapon = findInWeaponsList(ALLWeaponsList, enemies.enemies[i].IDweaponDrop, qountOfWeapons);
				addWeaponToInventory(givedWeapon, player.weapons);
			}
			chance = random(1, 100);
			if (chance >= 50) {
				Armor givedArmor = findInArmorsList(ALLArmorsList, enemies.enemies[i].IDarmorDrop, qountOfArmors);
				addArmorToInventory(givedArmor, player.armors);
			}

			chance = random(1, 100);
			if (chance >= 50) {
				Potion givedPotion = findInPotionsList(ALLPotionsList, enemies.enemies[i].IDpotionDrop, qountOfPotions);
				addPotionToInventory(givedPotion, player.potions);
			}

			player.money += enemies.enemies[i].moneyDrop;



		}
	}






	for (int i = 0; i < 4; i++) {
		if (player.team[i].status != DEAD && player.team[i].status != ESCAPED) {
			for (int j = 0; j < 4; j++) {
				if (deadEnemies[j]) {
					player.team[i].exp += enemies.enemies[j].expDrop;
				}
			}
		}



	}
}
void win(Player& player, Enemy& boss) {
	int chance = 0;


	chance = random(1, 100);
	if (chance >= 50) {
		Weapon givedWeapon = findInWeaponsList(ALLWeaponsList, boss.IDweaponDrop, qountOfWeapons);
		addWeaponToInventory(givedWeapon, player.weapons);
	}
	chance = random(1, 100);
	if (chance >= 50) {
		Armor givedArmor = findInArmorsList(ALLArmorsList, boss.IDarmorDrop, qountOfArmors);
		addArmorToInventory(givedArmor, player.armors);
	}

	chance = random(1, 100);
	if (chance >= 50) {
		Potion givedPotion = findInPotionsList(ALLPotionsList, boss.IDpotionDrop, qountOfPotions);
		addPotionToInventory(givedPotion, player.potions);
	}

	player.money += boss.moneyDrop;

	for (int i = 0; i < 4; i++) {
		if (player.team[i].status != DEAD && player.team[i].status != ESCAPED) {
			player.team[i].exp += boss.expDrop;
		}
	}

	boss.position.X = -100;
	boss.position.Y = -100;
}



void startBattle(Player& player, EnemiesSquad enemies) {

	int result = CONTINUE;
	int chance = random(1, 100);

	for (int i = 0; i < 4; i++) {
		enemiesCooldowns[i] = enemies.enemies[i].ability.cooldown + 1;
		enemies.enemies[i].ability.cooldown = 0;
		saveMaxColldowns(player.team[i].abilities, heroesCooldowns[i]);
		setCooldownsToZero(player.team[i].abilities);
	}

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
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			win(player, enemies);
			return;
		}
		if (result == ESCAPE) {
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			return;
		}
		if (result == LOSE) {
			inGame = false;
			return;
		}

		if (chance >= 60) 
		{
			drawFightingScene(player, enemies, 0, -1);
			SDL_Delay(2500);
		}
		chance = 100;
		if (result == CONTINUE) {
			for (int i = 0; i < 4; i++) freeEnemies[i] = true;
			result = enemiesAct(player, enemies);
		}

		if (result == WIN) {
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			win(player, enemies);
			return;
		}

		if (result == ESCAPE) {
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			return;
		}

		if (result == LOSE) {
			inGame = false;
			return;
		}
		for (int i = 0; i < 4; i++) {
			enemies.enemies[i].ability.cooldown--;
			for (int j = 0; j < MAX_ABILITIES; j++) {
				if (player.team[i].abilities[j].ID != 0 && player.team[i].abilities[j].cooldown != 0) player.team[i].abilities[j].cooldown--;
			}
		}





	}



}
void startBattle(Player& player, Enemy& boss) {

	int result = CONTINUE;
	int chance = random(1, 100);

	enemiesCooldowns[0] = boss.ability.cooldown + 1;
	boss.ability.cooldown = 0;
	for (int i = 0; i < 4; i++) {
		saveMaxColldowns(player.team[i].abilities, heroesCooldowns[i]);
		setCooldownsToZero(player.team[i].abilities);
	}

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
			result = playerAct(player, boss);
		}

		if (result == WIN) {
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			win(player, boss);
			return;
		}
		if (result == ESCAPE) {
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			return;
		}
		if (result == LOSE) {
			inGame = false;
			return;
		}

		if (chance >= 60) 
		{
			drawFightingScene(player, boss, 0, -1);
			SDL_Delay(2500);
		}
		chance = 100;
		if (result == CONTINUE) {
			for (int i = 0; i < 4; i++) freeEnemies[i] = true;
			result = enemiesAct(player, boss);
		}

		if (result == WIN) {
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			win(player, boss);
			return;
		}

		if (result == ESCAPE) {
			for (int i = 0; i < 4; i++) {
				setCooldownsToMax(player.team[i].abilities, heroesCooldowns[i]);
			}
			return;
		}

		if (result == LOSE) {
			inGame = false;
			return;
		}
		boss.ability.cooldown--;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < MAX_ABILITIES; j++) {
				if (player.team[i].abilities[j].ID != 0 && player.team[i].abilities[j].cooldown != 0) player.team[i].abilities[j].cooldown--;
			}
		}
	}
}