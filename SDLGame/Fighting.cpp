#include "Fighting.h"

bool freeHeroes[4] = { true, true, true, true };
bool freeEnemies[4] = { true, true, true, true };

SDL_Event ev;



void playerAct(Player& player, EnemiesSquad& enemies) {
	int coursorPosition = 0, heroChoice;

	while (freeHeroes[0] || freeHeroes[1] || freeHeroes[2] || freeHeroes[3]) {
		for (int i = 0; i < 4; i++) {
			if (player.team[i].status == DEAD || player.team[i].status == ESCAPED) freeHeroes[i] = false;
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
						if (freeHeroes[coursorPosition]) heroChoice = coursorPosition;
						break;
					}
					
					break;
				}


		}
		



	}
}





void startFight(Player& player, EnemiesSquad enemies) {

	int chance = random(1, 100);

	while (true) {



		if (chance >= 60) {
			playerAct(player, enemies);
		}

		chance = 100;







	}



}