#include "Menues.h"





bool startMenu() {
	int coursorPosition = 0, choice;
	bool inStartMenu = true;
	SDL_Event ev;

	while (inStartMenu) {
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type) {
			case SDL_QUIT:
				return false;
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
					choice = coursorPosition;
					inStartMenu = false;
					break;
				}
				break;
			}
		}

		drawStartMenu(coursorPosition);

	}

	switch (choice) {
	case 0: break;
	case 1: break;
	case 2: break;
	
	
	case 3:
		return false;
		break;
	}



}