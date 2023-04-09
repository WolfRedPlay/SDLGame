#include "Fighting.h"

enum Result {
	CONTINUE,
	WIN,
	LOSE,
	ESCAPE
};


bool freeHeroes[4];
bool freeEnemies[4];

SDL_Event ev;



int playerAct(Player& player, EnemiesSquad& enemies) {
	int coursorPosition = 0, heroChoice, choice, enemyChoice;

	bool inHeroChoosing = true, inActionChoosing = false, inAction = false, inEnemyChoosing = false, inChoosing = false;

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
						if (freeHeroes[coursorPosition])
						{
							choice = coursorPosition;
							inActionChoosing = false;
							inAction = true;
							coursorPosition = 0;
						}
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

									//attack();
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
								choice = coursorPosition;
								inChoosing = false;
								inEnemyChoosing = true;

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
									//cast();
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
									//использовать зелье
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
				//увеличить защиту
				break;
			case 4:
				//попытаться убежать
				break;
			}
		}
	}
	return CONTINUE;
}

int enemiesAct(Player& player, EnemiesSquad& enemies) {
	int heroChoice, enemyCoice = 0;

	while (freeEnemies[0] || freeEnemies[1] || freeEnemies[2] || freeEnemies[3]) {
		for (int i = 0; i < 4; i++)
			if (enemies.enemies[i].status == DEAD || enemies.enemies[i].status == ESCAPED) freeEnemies[i] = false;
		
		if (player.team[0].status == DEAD && player.team[1].status == DEAD && 
			player.team[2].status == DEAD && player.team[3].status == DEAD) {
			//поражение
			return LOSE;
		}
		do {
			enemyCoice = random(0, 3);

		} while (freeEnemies[enemyCoice]);
		
		if (enemies.enemies[enemyCoice].ability.cooldown != 0) {
			do {
				heroChoice = random(0,3);
			} while (player.team[heroChoice].status != DEAD && player.team[heroChoice].status != ESCAPED);
			//enemyCast();
			freeEnemies[enemyCoice] = false;
		}
		else if (enemies.enemies[enemyCoice].health <= 5) {
			//пытается убежать
			freeEnemies[enemyCoice] = false;
		}
		else {
			do {
				heroChoice = random(0, 3);
			} while (player.team[heroChoice].status != DEAD && player.team[heroChoice].status != ESCAPED);
			//атакует
			freeEnemies[enemyCoice] = false;
		}

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

		if (chance >= 60)
			for (int i = 0; i < 4; i++) freeHeroes[i] = true;
			result = playerAct(player, enemies);
		
		if (result == WIN) {
			//победа
			return;
		}
		if (result == ESCAPE) {
			//побег
			return;
		}
		if (result == CONTINUE) {
			for (int i = 0; i < 4; i++) freeEnemies[i] = true;
			result = enemiesAct(player, enemies);
		}
		chance = 100;







	}



}