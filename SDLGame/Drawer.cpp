#include "Drawer.h"
Coordinates fromMapCoordinatesToScreen(Coordinates mapCoord) {
	Coordinates screenCoord = mapCoord;

	while (screenCoord.X >= (SCREEN_SIZE_X - 1)) screenCoord.X -= (SCREEN_SIZE_X - 1);
	while (screenCoord.Y >= SCREEN_SIZE_Y) screenCoord.Y -= SCREEN_SIZE_Y;

	return screenCoord;

}

void drawScreen(char** map, Coordinates playerPos) {


	SDL_Rect unit = { 0,0, UNIT_SIZE, UNIT_SIZE };

	int leftBorder = 0, uppperBorder = 0;

	while (playerPos.X >= (WINDOW_WIDTH - 1) / UNIT_SIZE) {
		playerPos.X -= (WINDOW_WIDTH - 1) / UNIT_SIZE;
		leftBorder += (WINDOW_WIDTH - 1) / UNIT_SIZE;
	}
	while (playerPos.Y >= WINDOW_HEIGHT / UNIT_SIZE) {
		playerPos.Y -= WINDOW_HEIGHT / UNIT_SIZE;
		uppperBorder += WINDOW_HEIGHT / UNIT_SIZE;
	}

	for (int i = 0; i < WINDOW_HEIGHT / UNIT_SIZE; i++) {

		for (int j = 0; j < WINDOW_WIDTH / UNIT_SIZE; j++) {
			if (uppperBorder + i >= MAP_SIZE_Y || leftBorder + j >= MAP_SIZE_X) SDL_SetRenderDrawColor(ren, 0, 162, 232, 255);
			else if (map[uppperBorder + i][leftBorder + j] == '\n') SDL_SetRenderDrawColor(ren, 0, 162, 232, 255);
			else
			{
				if (map[uppperBorder + i][leftBorder + j] == '#') SDL_SetRenderDrawColor(ren, 0, 162, 232, 255);
				if (map[uppperBorder + i][leftBorder + j] == ' ') SDL_SetRenderDrawColor(ren, 181, 230, 29, 255);
				if (map[uppperBorder + i][leftBorder + j] == 'K') SDL_SetRenderDrawColor(ren, 255, 242, 0, 255);
				if (map[uppperBorder + i][leftBorder + j] == 'D') SDL_SetRenderDrawColor(ren, 185, 122, 87, 255);
				if (map[uppperBorder + i][leftBorder + j] == 'Q') SDL_SetRenderDrawColor(ren, 237, 28, 36, 255);
				if (map[uppperBorder + i][leftBorder + j] == 'N') SDL_SetRenderDrawColor(ren, 255, 128, 128, 255);
				if (map[uppperBorder + i][leftBorder + j] == 'C') SDL_SetRenderDrawColor(ren, 255, 128, 0, 255);
				if (map[uppperBorder + i][leftBorder + j] == 'S') SDL_SetRenderDrawColor(ren, 128, 128, 0, 255);
				if (map[uppperBorder + i][leftBorder + j] == 'I') SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);

			}

			SDL_RenderFillRect(ren, &unit);
			unit.x += unit.w;
		}
		unit.x = 0;
		unit.y += unit.h;
	}

}

void drawPlayer(Coordinates playerPosition) {

	playerPosition = fromMapCoordinatesToScreen(playerPosition);


	SDL_FRect playerUnit = { playerPosition.X * UNIT_SIZE, playerPosition.Y * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE };

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	SDL_RenderFillRectF(ren, &playerUnit);

}