#include "Dialogs.h"

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

void QuestDialog(QuestNPC npc) {
	SDL_Event ev;
	int coursorPosition;
	int dialogeStage = 0;
	
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

		drawQuestDialogWindow(npc, dialogeStage, coursorPosition);
	}

}