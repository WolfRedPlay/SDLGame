#include "Dialogs.h"

bool checkForRequiredItem(QuestItem item, QuestItem* items) {
	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++)
		if (items[i].ID == item.ID) return true;
	return false;
}

void giveReward(Player& player, QuestNPC npc) {
	int aliveHeroCount = 4;
	player.money += npc.quest.moneyReward;
	for (int i = 0; i < 4; i++)
		if (player.team[i].status == DEAD) aliveHeroCount--;

	int expReward = npc.quest.expReward / aliveHeroCount;
	for (int i = 0; i < 4; i++) 
		if (player.team[i].status == DEAD) player.team[i].exp += expReward;
	

}




void NPCDialog(NPC npc) {
	SDL_Event ev;


	while (true) {
		while (SDL_PollEvent(&ev))
			switch (ev.type) {
			case SDL_QUIT:
				DeInit(0);
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_RETURN:
					return;

				case SDL_SCANCODE_ESCAPE:
					return;
				}
				break;
			}

		drawNPCDialogWindow(npc);
	}

}

void QuestDialog(QuestNPC npc, Player& player) {
	SDL_Event ev;
	int coursorPosition, choice;
	int dialogeStage = 0;

	bool inStartPhrase = true, inAnswering = false;

	while (true) {
		coursorPosition = 0;
		if (!npc.quest.isCompleted)
		{

			if (!checkForRequiredItem(npc.quest.requiredItem, player.questItems)){
				while (inStartPhrase) {
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
								if (coursorPosition != 2) coursorPosition++;
								break;
							case SDL_SCANCODE_1:
								choice = 0;
								inStartPhrase = false;
								inAnswering = true;
								dialogeStage = 1;
								break;
							case SDL_SCANCODE_2:
								choice = 1;
								inStartPhrase = false;
								inAnswering = true;
								dialogeStage = 2;
								break;
							case SDL_SCANCODE_3:
								choice = 2;
								inStartPhrase = false;
								inAnswering = true;
								dialogeStage = 3;
								break;

							case SDL_SCANCODE_RETURN:
								choice = coursorPosition;
								dialogeStage = choice + 1;
								inStartPhrase = false;
								inAnswering = true;
								break;

							case SDL_SCANCODE_ESCAPE:
								return;
							}
							break;
						}

					drawQuestDialogWindow(npc, dialogeStage, coursorPosition);
				}

				while (inAnswering) {
					while (SDL_PollEvent(&ev))
						switch (ev.type) {
						case SDL_QUIT:
							DeInit(0);
							break;
						case SDL_KEYDOWN:
							switch (ev.key.keysym.scancode) {
							case SDL_SCANCODE_RETURN:
								inStartPhrase = true;
								inAnswering = false;
								if (dialogeStage == 1) {
									if (addQuestToList(npc.quest, player.quests)) return;
									else {
										dialogeStage = 4;
										drawQuestDialogWindow(npc, dialogeStage, coursorPosition);
										SDL_Delay(2500);
										return;
									}
								}
								dialogeStage = 0;
								break;

							case SDL_SCANCODE_ESCAPE:
								return;
							}
							break;
						}

					drawQuestDialogWindow(npc, dialogeStage, coursorPosition);
				}
			}
			else {
				while (inStartPhrase) {
					while (SDL_PollEvent(&ev))
						switch (ev.type) {
						case SDL_QUIT:
							DeInit(0);
							break;
						case SDL_KEYDOWN:
							switch (ev.key.keysym.scancode) {
							case SDL_SCANCODE_RETURN:
								inStartPhrase = false;
								giveReward(player, npc);
								return;

							case SDL_SCANCODE_ESCAPE:
								inStartPhrase = false;
								giveReward(player, npc);
								return;
							}
							break;
						}

					drawQuestDialogWindow(npc, 5, 0);
				}
			}
		}
		else {
			while (inStartPhrase) {
				while (SDL_PollEvent(&ev))
					switch (ev.type) {
					case SDL_QUIT:
						DeInit(0);
						break;
					case SDL_KEYDOWN:
						switch (ev.key.keysym.scancode) {
						case SDL_SCANCODE_RETURN:
							inStartPhrase = false;
							giveReward(player, npc);
							return;

						case SDL_SCANCODE_ESCAPE:
							inStartPhrase = false;
							giveReward(player, npc);
							return;
						}
						break;
					}

				drawQuestDialogWindow(npc, 6, 0);
			}
		}
	}
}

bool banditDialog(Enemy boss) {
	int coursorPosition = 0, choice;

	bool inDialog = true;

	SDL_Event ev;
	while (inDialog)
	{
		while(SDL_PollEvent(&ev))
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
					if (coursorPosition != 1) coursorPosition++;
					break;

					case SDL_SCANCODE_1:
						choice = 0;
						inDialog = false;
					break;
					case SDL_SCANCODE_2:
						choice = 1;
						inDialog = false;
					break;

				case SDL_SCANCODE_RETURN:
					choice = coursorPosition;
					inDialog = false;
					break;

				case SDL_SCANCODE_ESCAPE:
					return false;
				}
				break;
			}



		drawBanditLeaderDialogWindow(boss, 0, coursorPosition);

	}

	if (choice == 0) {
		while (true){
			while (SDL_PollEvent(&ev))
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;
				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					
					case SDL_SCANCODE_RETURN:

						return true;

					case SDL_SCANCODE_ESCAPE:
						return true;
					}
					break;
				}

			drawBanditLeaderDialogWindow(boss, 1, 0);
		}
		
	}

	if (choice == 1) {
		while (true) {
			while (SDL_PollEvent(&ev))
				switch (ev.type) {
				case SDL_QUIT:
					DeInit(0);
					break;
				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {

					case SDL_SCANCODE_RETURN:
						return false;

					case SDL_SCANCODE_ESCAPE:
						return false;
					}
					break;
				}

			drawBanditLeaderDialogWindow(boss, 2, 0);
		}
	}


}






bool BossDialog(Enemy boss){
	switch (boss.ID) {
	case BANDIT_LEADER:
		return banditDialog(boss);
		break;

	}
}