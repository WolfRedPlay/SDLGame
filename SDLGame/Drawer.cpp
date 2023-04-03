#include "Drawer.h"
Coordinates fromMapCoordinatesToScreen(Coordinates mapCoord) {
	Coordinates screenCoord = mapCoord;

	while (screenCoord.X >= (SCREEN_SIZE_X - 1)) screenCoord.X -= (SCREEN_SIZE_X - 1);
	while (screenCoord.Y >= SCREEN_SIZE_Y) screenCoord.Y -= SCREEN_SIZE_Y;

	return screenCoord;

}
void mathCoordsToScreen(double x, double y, int centerx, int centery, int& sx, int& sy) {

	sx = centerx + x;
	sy = centery - y;


}
void drawCircledAngle(double x1, double y1, double radius, double left, double right) {
	int sx1, sy1;
	int sx2, sy2;
	for (double alpha = left; alpha <= right; alpha += 0.5) {

		sx1 = radius * cos(alpha * M_PI / 180.0);
		sy1 = radius * sin(alpha * M_PI / 180.0);

		sx2 = radius * cos((alpha + 0.1) * M_PI / 180.0);
		sy2 = radius * sin((alpha + 0.1) * M_PI / 180.0);

		mathCoordsToScreen(sx1, sy1, x1, y1, sx1, sy1);
		mathCoordsToScreen(sx2, sy2, x1, y1, sx2, sy2);
		SDL_RenderDrawLine(ren, sx1, sy1, sx2, sy2);
	}
	SDL_RenderPresent(ren);
}






void drawCircledRect(double x, double y, double w, double h, double rad) {

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_Rect filling = { x + rad / 2 - 1, y + rad / 2 - 1, w - rad / 1.5, h - rad / 1.5 };
	SDL_RenderFillRect(ren, &filling);


	SDL_SetRenderDrawColor(ren, 0, 128, 255, 255);

	for (int i = 0; i <= rad / 2; i++) {
		drawCircledAngle(x + rad, y + rad, rad, 90, 180);
		drawCircledAngle(x + w - rad, y + rad, rad, 0, 90);
		drawCircledAngle(x + rad, y + h - rad, rad, 180, 270);
		drawCircledAngle(x + w - rad, y + h - rad, rad, 270, 360);

		SDL_RenderDrawLineF(ren, x + rad, y, x + w - rad, y);
		SDL_RenderDrawLineF(ren, x + rad, y + h, x + w - rad, y + h);
		SDL_RenderDrawLineF(ren, x, y + rad, x, y + h - rad);
		SDL_RenderDrawLineF(ren, x + w, y + rad, x + w, y + h - rad);

		x += 1;
		y += 1;
		h -= 2;
		w -= 2;
		rad -= 1;
	}



}

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
SDL_Texture* generateTextureFromText(const char* str, TTF_Font* font, SDL_Rect& rect, SDL_Color fg) {

	SDL_Surface* surfaceFont = TTF_RenderText_Blended(font, str, fg);
	rect.w = surfaceFont->w;
	rect.h = surfaceFont->h;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surfaceFont);
	SDL_FreeSurface(surfaceFont);

	return texture;


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


void drawStartMenu(int coursorPosition) {
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 100);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 50);
	SDL_Rect rect;
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 255, 242, 100, 255);
	SDL_RenderClear(ren);


	//название игры
	texture = generateTextureFromText("GAME", headerFont, rect, { 0,0,0,255 });
	rect.x = WINDOW_WIDTH / 2 - rect.w / 2;
	rect.y = 50;
	SDL_RenderCopy(ren, texture, NULL, &rect);
	SDL_DestroyTexture(texture);

	//пункты]
	if (coursorPosition == 0) texture = generateTextureFromText(">New Game", choicesFont, rect, { 0,0,0,255 });
	else texture = generateTextureFromText("New Game", choicesFont, rect, { 0,0,0,255 });
	rect.x = 800;
	rect.y = 300;
	SDL_RenderCopy(ren, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	if (coursorPosition == 1) texture = generateTextureFromText(">Load Game", choicesFont, rect, { 0,0,0,255 });
	else texture = generateTextureFromText("Load Game", choicesFont, rect, { 0,0,0,255 });
	rect.x = 800;
	rect.y = 400;
	SDL_RenderCopy(ren, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	if (coursorPosition == 2) texture = generateTextureFromText(">Guide", choicesFont, rect, { 0,0,0,255 });
	else texture = generateTextureFromText("Guide", choicesFont, rect, { 0,0,0,255 });
	rect.x = 800;
	rect.y = 500;
	SDL_RenderCopy(ren, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	if (coursorPosition == 3) texture = generateTextureFromText(">Exit", choicesFont, rect, { 0,0,0,255 });
	else texture = generateTextureFromText("Exit", choicesFont, rect, { 0,0,0,255 });
	rect.x = 800;
	rect.y = 600;
	SDL_RenderCopy(ren, texture, NULL, &rect);
	SDL_DestroyTexture(texture);



	SDL_RenderPresent(ren);
	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}

void drawHeroCreatingMenu(int heroNum, int coursorPosition) {
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 50);
	SDL_Rect pngRect;
	SDL_Rect ttfRect;
	SDL_Rect classChoice = { 0, 0, 500, 450 };
	SDL_SetRenderDrawColor(ren, 255, 242, 100, 255);
	SDL_RenderClear(ren);
	SDL_Texture* heroClass;
	char headerText[31];
	sprintf_s(headerText, "CHOOSE A CLASS FOR YOUR %d HERO", heroNum);

	SDL_Texture* header = generateTextureFromText(headerText, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = WINDOW_WIDTH / 2 - ttfRect.w / 2;
	ttfRect.y = 50;
	SDL_RenderCopy(ren, header, NULL, &ttfRect);
	SDL_DestroyTexture(header);


	heroClass = generateTextureFromPNG("Textures\\ClassKnight.png");
	pngRect.x = 300;
	pngRect.y = 200;
	pngRect.w = 400;
	pngRect.h = 400;
	SDL_RenderCopy(ren, heroClass, NULL, &pngRect);
	SDL_DestroyTexture(heroClass);

	heroClass = generateTextureFromPNG("Textures\\ClassRogue.png");
	pngRect.x = 1100;
	pngRect.y = 200;
	pngRect.w = 500;
	pngRect.h = 400;
	SDL_RenderCopy(ren, heroClass, NULL, &pngRect);
	SDL_DestroyTexture(heroClass);

	heroClass = generateTextureFromPNG("Textures\\ClassMage.png");
	pngRect.x = 150;
	pngRect.y = 500;
	pngRect.w = 700;
	pngRect.h = 700;
	SDL_RenderCopy(ren, heroClass, NULL, &pngRect);
	SDL_DestroyTexture(heroClass);


	heroClass = generateTextureFromPNG("Textures\\ClassHealer.png");
	pngRect.x = 1050;
	pngRect.y = 625;
	pngRect.w = 600;
	pngRect.h = 425;
	SDL_RenderCopy(ren, heroClass, NULL, &pngRect);
	SDL_DestroyTexture(heroClass);

	if (coursorPosition == 0) {
		classChoice.x = 250;
		classChoice.y = 175;

	}
	if (coursorPosition == 1) {
		classChoice.x = 1095;
		classChoice.y = 175;

	}
	if (coursorPosition == 2) {
		classChoice.x = 245;
		classChoice.y = 625;

	}
	if (coursorPosition == 3) {
		classChoice.x = 1095;
		classChoice.y = 625;

	}
	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);

	for (int i = 0; i < 8; i++) {
		classChoice.x += 1;
		classChoice.y += 1;
		classChoice.w -= 2;
		classChoice.h -= 2;
		SDL_RenderDrawRect(ren, &classChoice);
	}


	SDL_RenderPresent(ren);
}

void drawHeroNameChoice(int coursorPosition) {
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 30);
	SDL_Texture* texture;

	//drawCircledRect(300, 500, WINDOW_WIDTH - 600, 300, 25);

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_Rect filling = { 300, 500, WINDOW_WIDTH - 600, 300 };
	SDL_RenderFillRect(ren, &filling);


	texture = generateTextureFromText("How do you want to chose this hero name?", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = WINDOW_WIDTH / 2 - ttfRect.w / 2;
	ttfRect.y = 520;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 0) texture = generateTextureFromText(">Myself", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Myself", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 750;
	ttfRect.y = 620;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);
	if (coursorPosition == 1) texture = generateTextureFromText(">Randomly", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Randomly", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 750;
	ttfRect.y = 670;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);


	SDL_RenderPresent(ren);
	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}

void drawPlayerNameChoosing(char* name) {
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 30);
	SDL_Texture* texture;

	//drawCircledRect(300, 500, WINDOW_WIDTH - 600, 300, 25);

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_Rect filling = { 300, 500, WINDOW_WIDTH - 600, 300 };
	SDL_RenderFillRect(ren, &filling);



	texture = generateTextureFromText("Press hero's name", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = WINDOW_WIDTH / 2 - ttfRect.w / 2;
	ttfRect.y = 520;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char header[21];
	sprintf_s(header, "Name: %s", name);

	texture = generateTextureFromText(header, choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 750;
	ttfRect.y = 670;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);




	SDL_RenderPresent(ren);
	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}

void drawRandomNameChoosing(char* name) {
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 50);
	SDL_Rect ttfRect;
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 30);
	SDL_Texture* texture;

	//drawCircledRect(300, 500, WINDOW_WIDTH - 600, 300, 25);

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_Rect filling = { 300, 500, WINDOW_WIDTH - 600, 300 };
	SDL_RenderFillRect(ren, &filling);


	texture = generateTextureFromText("Is it a good name?", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = WINDOW_WIDTH / 2 - ttfRect.w / 2;
	ttfRect.y = 520;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture); 
	
	char header[21];
	sprintf_s(header, "Name: %s", name);


	texture = generateTextureFromText(header, choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 825;
	ttfRect.y = 625;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	texture = generateTextureFromText("(Press ENTER to confirm or ARROWS to change)", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = WINDOW_WIDTH / 2 - ttfRect.w / 2;
	ttfRect.y = 700;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	SDL_RenderPresent(ren);
	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}

