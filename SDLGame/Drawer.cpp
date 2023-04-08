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


SDL_Texture* generateTextureFromText(const char* str, TTF_Font* font, SDL_Rect& rect, SDL_Color fg) {

	SDL_Surface* surfaceFont = TTF_RenderText_Blended(font, str, fg);
	rect.w = surfaceFont->w;
	rect.h = surfaceFont->h;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surfaceFont);
	SDL_FreeSurface(surfaceFont);

	return texture;


}

void drawScreen(char** map, Coordinates playerPos) {

	SDL_SetRenderDrawColor(ren, 0, 162, 232, 255);
	SDL_RenderClear(ren);

	SDL_Rect npcFrame = { 0,0,0,0 };


	SDL_Texture* woodWall = generateTextureFromPNG("Textures\\wooden_wall.png");
	SDL_Texture* grass = generateTextureFromPNG("Textures\\grass.png");
	SDL_Texture* wood = generateTextureFromPNG("Textures\\wood.png");
	SDL_Texture* stoneWall = generateTextureFromPNG("Textures\\Stonewall.png");
	SDL_Texture* key = generateTextureFromPNG("Textures\\Key.png");
	SDL_Texture* door = generateTextureFromPNG("Textures\\door.png");
	SDL_Texture* chest = generateTextureFromPNG("Textures\\chest.png");
	SDL_Texture* goldChest = generateTextureFromPNG("Textures\\Golden_chest.png");
	SDL_Texture* npc = generateTextureFromPNG("Textures\\NPC.png");
	SDL_Texture* inkeeper = generateTextureFromPNG("Textures\\Inkeeper.png");
	SDL_Texture* weaponsSeller = generateTextureFromPNG("Textures\\Sell_weapon.png");
	SDL_Texture* armorsSeller = generateTextureFromPNG("Textures\\Sell_armor.png");
	SDL_Texture* potionsSeller = generateTextureFromPNG("Textures\\Sell_potion.png");
	SDL_Texture* abilitiesSeller = generateTextureFromPNG("Textures\\Sell_magic.png");


	SDL_Rect unit = { 0,0, UNIT_SIZE_X, UNIT_SIZE_Y };

	int leftBorder = 0, uppperBorder = 0;

	int x = 0, y = 0;

	while (playerPos.X >= (window_width - 1) / UNIT_SIZE_X) {
		playerPos.X -= (window_width - 1) / UNIT_SIZE_X;
		leftBorder += (window_width - 1) / UNIT_SIZE_X;
	}
	while (playerPos.Y >= window_height / UNIT_SIZE_Y) {
		playerPos.Y -= window_height / UNIT_SIZE_Y;
		uppperBorder += window_height / UNIT_SIZE_Y;
	}
	if (window_height / UNIT_SIZE_Y > mapSizeY) y = mapSizeY;
	else y = window_height / UNIT_SIZE_Y;
	if (window_width / UNIT_SIZE_X > mapSizeX) x = mapSizeX;
	else x = window_width / UNIT_SIZE_X;


	for (int i = 0; i < y; i++) {

		for (int j = 0; j < x; j++) {
			npcFrame.x = 0;
			npcFrame.y = 0;
			if (uppperBorder + i >= mapSizeY || leftBorder + j >= mapSizeX) SDL_SetRenderDrawColor(ren, 0, 162, 232, 255);
			else if (map[uppperBorder + i][leftBorder + j] == '\n') SDL_SetRenderDrawColor(ren, 0, 162, 232, 255);
			else
			{
				if (map[uppperBorder + i][leftBorder + j] == EMPTY) {
					unit.x += unit.w;
					continue;
				}

				if (map[uppperBorder + i][leftBorder + j] == NPC_QUEST) {
					SDL_SetRenderDrawColor(ren, 237, 28, 36, 255);
					SDL_RenderFillRect(ren, &unit);
				}

				if (map[uppperBorder + i][leftBorder + j] == SHOP)
				{
					SDL_SetRenderDrawColor(ren, 128, 128, 0, 255);
				}


			}
			if (map[uppperBorder + i][leftBorder + j] == WOODEN_WALL) {
				SDL_RenderCopy(ren, woodWall, NULL, &unit);
			}

			if (map[uppperBorder + i][leftBorder + j] == CHEST) {
				SDL_RenderCopy(ren, chest, NULL, &unit);
			}

			if (map[uppperBorder + i][leftBorder + j] == QUEST_CHEST) {
				SDL_RenderCopy(ren, goldChest, NULL, &unit);
			}

			if (map[uppperBorder + i][leftBorder + j] == DOOR) {
				if (map[uppperBorder + i - 1][leftBorder + j] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i - 1][leftBorder + j] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);
				SDL_RenderCopy(ren, door, NULL, &unit);
			}

			if (map[uppperBorder + i][leftBorder + j] == NPC) {
				if (map[uppperBorder + i][leftBorder + j - 1] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i][leftBorder + j - 1] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);
				npcFrame.w = 40;
				npcFrame.h = 70;
				npcFrame.x += npcFrame.w;
				int different = npcFrame.h - unit.h;
				unit.y -= different;
				unit.h = npcFrame.h;
				SDL_RenderCopy(ren, npc, &npcFrame, &unit);
				unit.h = UNIT_SIZE_Y;
				unit.y += different;
			}

			if (map[uppperBorder + i][leftBorder + j] == INKEEPER) {
				if (map[uppperBorder + i][leftBorder + j + 1] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i][leftBorder + j + 1] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);
				npcFrame.w = 40;
				npcFrame.h = 70;
				npcFrame.x += npcFrame.w;
				int different = npcFrame.h - unit.h;
				unit.y -= different;
				unit.h = npcFrame.h;
				SDL_RenderCopy(ren, inkeeper, NULL, &unit);
				unit.h = UNIT_SIZE_Y;
				unit.y += different;
			}

			if (map[uppperBorder + i][leftBorder + j] == WEAPON_SELLER) {
				if (map[uppperBorder + i][leftBorder + j + 1] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i][leftBorder + j + 1] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);
				npcFrame.w = 40;
				npcFrame.h = 70;
				npcFrame.x += npcFrame.w;
				int different = npcFrame.h - unit.h;
				unit.y -= different;
				unit.h = npcFrame.h;
				SDL_RenderCopy(ren, weaponsSeller, NULL, &unit);
				unit.h = UNIT_SIZE_Y;
				unit.y += different;
			}
			if (map[uppperBorder + i][leftBorder + j] == ARMOR_SELLER) {
				if (map[uppperBorder + i][leftBorder + j + 1] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i][leftBorder + j + 1] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);
				npcFrame.w = 40;
				npcFrame.h = 70;
				npcFrame.x += npcFrame.w;
				int different = npcFrame.h - unit.h;
				unit.y -= different;
				unit.h = npcFrame.h;
				SDL_RenderCopy(ren, armorsSeller, NULL, &unit);
				unit.h = UNIT_SIZE_Y;
				unit.y += different;
			}
			if (map[uppperBorder + i][leftBorder + j] == POTION_SELLER) {
				if (map[uppperBorder + i][leftBorder + j + 1] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i][leftBorder + j + 1] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);
				npcFrame.w = 40;
				npcFrame.h = 70;
				npcFrame.x += npcFrame.w;
				int different = npcFrame.h - unit.h;
				unit.y -= different;
				unit.h = npcFrame.h;
				SDL_RenderCopy(ren, potionsSeller, NULL, &unit);
				unit.h = UNIT_SIZE_Y;
				unit.y += different;
			}
			if (map[uppperBorder + i][leftBorder + j] == ABILITIES_SELLER) {
				if (map[uppperBorder + i][leftBorder + j + 1] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i][leftBorder + j + 1] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);
				npcFrame.w = 40;
				npcFrame.h = 70;
				npcFrame.x += npcFrame.w;
				int different = npcFrame.h - unit.h;
				unit.y -= different;
				unit.h = npcFrame.h;
				SDL_RenderCopy(ren, abilitiesSeller, NULL, &unit);
				unit.h = UNIT_SIZE_Y;
				unit.y += different;
			}

			if (map[uppperBorder + i][leftBorder + j] == KEY) {
				if (map[uppperBorder + i][leftBorder + j - 1] == GRASS)SDL_RenderCopy(ren, grass, NULL, &unit);
				if (map[uppperBorder + i][leftBorder + j - 1] == WOOD)SDL_RenderCopy(ren, wood, NULL, &unit);

				SDL_RenderCopy(ren, key, NULL, &unit);
			}

			if (map[uppperBorder + i][leftBorder + j] == GRASS) {
				SDL_RenderCopy(ren, grass, NULL, &unit);
			}

			if (map[uppperBorder + i][leftBorder + j] == WOOD) {
				SDL_RenderCopy(ren, wood, NULL, &unit);
			}

			if (map[uppperBorder + i][leftBorder + j] == STONE_WALL) {
				SDL_RenderCopy(ren, stoneWall, NULL, &unit);
			}


			unit.x += unit.w;
		}
		unit.x = 0;
		unit.y += unit.h;
	}
	SDL_DestroyTexture(woodWall);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(wood);
	SDL_DestroyTexture(stoneWall);
	SDL_DestroyTexture(key);
	SDL_DestroyTexture(door);
	SDL_DestroyTexture(chest);
	SDL_DestroyTexture(goldChest);
	SDL_DestroyTexture(npc);
	SDL_DestroyTexture(inkeeper);
	SDL_DestroyTexture(weaponsSeller);
	SDL_DestroyTexture(armorsSeller);
	SDL_DestroyTexture(potionsSeller);
	SDL_DestroyTexture(abilitiesSeller);

}
void drawPlayer(Coordinates playerPosition, int diraction, int frame) {




	playerPosition = fromMapCoordinatesToScreen(playerPosition);

	SDL_Rect playerFrame = { 0,0,0,0 };
	SDL_FRect playerUnit = { playerPosition.X * UNIT_SIZE_X, playerPosition.Y * UNIT_SIZE_Y, UNIT_SIZE_X, UNIT_SIZE_Y };
	SDL_Texture* player = generateTextureFromPNG("Textures\\Player.png");

	playerFrame.w = 54;
	playerFrame.h = 70;
	if (diraction == DOWN) playerFrame.y = 0;
	if (diraction == UP) playerFrame.y = playerFrame.h * 3;
	if (diraction == LEFT) playerFrame.y = playerFrame.h * 1;
	if (diraction == RIGHT) playerFrame.y = playerFrame.h * 2;
	playerFrame.x = playerFrame.w * frame;
	playerUnit.h = 60;
	playerUnit.y -= playerFrame.h - playerUnit.h + 10;

	SDL_RenderCopyF(ren, player, &playerFrame, &playerUnit);

	SDL_DestroyTexture(player);

}

void drawChestOpenning(Weapon givedWeapon, Armor givedArmor, Potion givedPotion, int givedMoney) {
	SDL_Rect window = { 0, 0, 500, 400 };
	window.x = window_width / 2 - window.w / 2;
	window.y = window_height / 2 - window.h;
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 30);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Texture* texture;
	char text[50];

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("CONGRATULATIONS!", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + 30;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);
	ttfRect.y += 80;
	if (givedWeapon.ID != 0)
	{
		sprintf_s(text, "You've received: %s", givedWeapon.name);
		texture = generateTextureFromText(text, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
		ttfRect.y += 30;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}
	if (givedArmor.ID != 0)
	{
		sprintf_s(text, "You've received: %s", givedArmor.name);
		texture = generateTextureFromText(text, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
		ttfRect.y += 30;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}
	if (givedPotion.ID != 0)
	{
		sprintf_s(text, "You've received: %s", givedPotion.name);
		texture = generateTextureFromText(text, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
		ttfRect.y += 30;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}
	sprintf_s(text, "You've received: %d coins", givedMoney);
	texture = generateTextureFromText(text, choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
	ttfRect.y += 30;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);


	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
	SDL_RenderPresent(ren);
	SDL_Delay(2000);
}

void drawHeroChoice(Player player, int coursorPosition) {
	SDL_Rect window = { 0, 0, 1000, 300 };
	window.x = window_width / 2 - window.w / 2;
	window.y = window_height / 2 - window.h;

	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 50);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Rect choice = { 0,0, 100, 100 };
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 0, 64, 128, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("CHOOSE HERO", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + 10;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);




	for (int i = 0; i < 4; i++) {
		choice.x = window.x + 100 + (choice.w + 133) * i;
		choice.y = window.y + 100;
		if (i == 0 || i == 2) SDL_RenderCopy(ren, player.team[i].texture, NULL, &choice);
		if (coursorPosition == i) {	
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
			SDL_RenderDrawRect(ren, &choice);
		}
		texture = generateTextureFromText(player.team[i].name, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = (100 - ttfRect.w) / 2 + choice.x;
		ttfRect.y = window.y + 225;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}
void drawConfirmation() {
	SDL_Rect window = { 0, 0, 900, 300 };
	window.x = window_width / 2 - window.w / 2;
	window.y = window_height / 2 - window.h;

	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 80);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 0, 64, 128, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("ARE YOU SURE?", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + 100;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	texture = generateTextureFromText("(Press 'Y' to confirm/ Press 'N' to reject)", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + 190;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}
void drawSaveSlots(int coursorPosition) {
	SDL_Rect window;

	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 30);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	window.w = UNIT_SIZE_X * 15;
	window.h = UNIT_SIZE_Y * 7;
	window.x = window_width / 2 - window.w / 2;
	window.y = window_height / 2 - window.h / 2;

	SDL_SetRenderDrawColor(ren, 0, 181, 160, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("CHOOSE SAVE SLOT", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + 30;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 0)texture = generateTextureFromText(">Save slot 1", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Save slot 1", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + 150;
	ttfRect.y += 80;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 1)texture = generateTextureFromText(">Save slot 2", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Save slot 2", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + 150;
	ttfRect.y += 40;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 2)texture = generateTextureFromText(">Save slot 3", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Save slot 3", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + 150;
	ttfRect.y += 40;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
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
	rect.x = window_width / 2 - rect.w / 2;
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
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
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
	TTF_CloseFont(headerFont);
}
void drawHeroNameChoice(int coursorPosition) {
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 30);
	SDL_Texture* texture;

	//drawCircledRect(300, 500, window_width - 600, 300, 25);

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_Rect filling = { 300, 500, window_width - 600, 300 };
	SDL_RenderFillRect(ren, &filling);


	texture = generateTextureFromText("How do you want to chose this hero name?", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
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

	//drawCircledRect(300, 500, window_width - 600, 300, 25);

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_Rect filling = { 300, 500, window_width - 600, 300 };
	SDL_RenderFillRect(ren, &filling);



	texture = generateTextureFromText("Press hero's name", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
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

	//drawCircledRect(300, 500, window_width - 600, 300, 25);

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_Rect filling = { 300, 500, window_width - 600, 300 };
	SDL_RenderFillRect(ren, &filling);


	texture = generateTextureFromText("Is it a good name?", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
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
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 700;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	SDL_RenderPresent(ren);
	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}

void drawGameMenu(int coursorPosition) {
	SDL_Rect window;

	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 70);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	window.w = UNIT_SIZE_X * 20;
	window.h = UNIT_SIZE_Y * 10;
	window.x = window_width / 2 - window.w / 2;
	window.y = window_height / 2 - window.h / 2;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("GAME MENU", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + window.w / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + 10;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 0)texture = generateTextureFromText(">Continue", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Continue", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + 250;
	ttfRect.y += 150;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 1)texture = generateTextureFromText(">Save game", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Save game", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.y += 50;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 2)texture = generateTextureFromText(">Load game", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Load game", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.y += 50;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 3)texture = generateTextureFromText(">Start menu", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Start menu", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.y += 50;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}

void drawPlayerMenu(int coursorPosition) {
	SDL_Rect window = { 100, 50, window_width - 200, window_height - 100 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 80);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);



	texture = generateTextureFromText("PLAYER MENU", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 70;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 0)texture = generateTextureFromText(">Heros' stats", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Heros' stats", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 700;
	ttfRect.y = 300;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 1)texture = generateTextureFromText(">Weapons", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Weapons", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 700;
	ttfRect.y = 350;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 2)texture = generateTextureFromText(">Armors", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Armors", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 700;
	ttfRect.y = 400;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 3)texture = generateTextureFromText(">Potions", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Potions", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 700;
	ttfRect.y = 450;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 4)texture = generateTextureFromText(">Abilities", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Abilities", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 700;
	ttfRect.y = 500;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 5)texture = generateTextureFromText(">Quests list", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Quests List", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 700;
	ttfRect.y = 550;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 6)texture = generateTextureFromText(">Quest items", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Quest items", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = 700;
	ttfRect.y = 600;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	SDL_RenderPresent(ren);
	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}
void drawHeroesStats(Player& player) {
	SDL_Rect window = { 100, 50, window_width - 200, window_height - 100 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 80);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("HEROES' STATS", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 70;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char heroStats[100];

	for (int i = 0; i < 4; i++) {
		sprintf_s(heroStats, "NAME: %s", player.team[i].name);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 400;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "HP: %d", player.team[i].health);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 440;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "MP: %d", player.team[i].mana);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 480;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "SP: %d", player.team[i].stamina);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 520;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "Protection: %d", player.team[i].armor);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 560;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "Basic damage: %d", player.team[i].damage);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 600;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "Weapon: %s | DMG: %d", player.team[i].equipedWeapon.name, player.team[i].equipedWeapon.damage);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 640;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "Armor: %s | PRT: %d", player.team[i].equipedArmor.name, player.team[i].equipedArmor.armor);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 680;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "LVL: %d", player.team[i].lvl);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 720;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(heroStats, "EXP: %d", player.team[i].exp);
		texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = 200 + i * 400;
		ttfRect.y = 760;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
		if (player.team[i].status == DEAD)
		{
			sprintf_s(heroStats, "DEAD");
			texture = generateTextureFromText(heroStats, choicesFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = 200 + i * 400;
			ttfRect.y = 800;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
		}
	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}
void drawPlayerWeapons(Player& player, int coursorPosition) {


	SDL_Rect window = { 100, 50, window_width - 200, window_height - 100 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 50);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	SDL_Rect itemRect = { 0,0,264,265 };
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("WEAPONS INVENTORY", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 70;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char money[30];

	ttfRect.x += ttfRect.w;
	sprintf_s(money, "MONEY: %d coins", player.money);
	texture = generateTextureFromText(money, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.y = window.y + window.h - ttfRect.h - UNIT_SIZE_Y * 2;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char textureWay[100], weaponName[22], weaponDMG[10], weaponPrice[30];

	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		sprintf_s(textureWay, "Textures\\%d.png", player.weapons[i].ID);
		if (player.weapons[i].ID != 0) texture = generateTextureFromPNG(textureWay);

		if (i <= (MAX_PLAYER_INVENTORY_SIZE / 2) - 1)
		{
			itemRect.x = window.x + 200 + itemRect.w * i;
			itemRect.y = window.y + 100;
		}
		else {
			itemRect.x = window.x + 200 + itemRect.w * (i % 5);
			itemRect.y = window.y + 100 + itemRect.h;
		}
		if (i == coursorPosition) SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		else SDL_SetRenderDrawColor(ren, 0, 200, 192, 255);
		SDL_RenderDrawRect(ren, &itemRect);
		SDL_RenderCopy(ren, texture, NULL, &itemRect);
		if (player.weapons[i].ID != 0) SDL_DestroyTexture(texture);
	}

	if (player.weapons[coursorPosition].ID != 0) {
		sprintf_s(weaponName, "NAME: %s", player.weapons[coursorPosition].name);
		sprintf_s(weaponDMG, "DMG: %d", player.weapons[coursorPosition].damage);
		sprintf_s(weaponPrice, "PRICE: %d", player.weapons[coursorPosition].price);
		texture = generateTextureFromText(weaponName, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 200;
		ttfRect.y = 780;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		texture = generateTextureFromText(weaponDMG, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 200;
		ttfRect.y += 50;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		texture = generateTextureFromText(weaponPrice, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 200;
		ttfRect.y += 50;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}
void drawPlayerArmors(Player& player, int coursorPosition) {


	SDL_Rect window = { 100, 50, window_width - 200, window_height - 100 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 50);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	SDL_Rect itemRect = { 0,0,264,265 };
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("ARMOS INVENTORY", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 70;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char money[30];

	ttfRect.x += ttfRect.w;
	sprintf_s(money, "MONEY: %d coins", player.money);
	texture = generateTextureFromText(money, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.y = window.y + window.h - ttfRect.h - UNIT_SIZE_Y * 2;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char textureWay[100], armorName[22], armorPRT[10];

	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		sprintf_s(textureWay, "Textures\\%d.png", player.armors[i].ID);
		if (player.armors[i].ID != 0) texture = generateTextureFromPNG(textureWay);

		if (i <= (MAX_PLAYER_INVENTORY_SIZE / 2) - 1)
		{
			itemRect.x = window.x + 200 + itemRect.w * i;
			itemRect.y = window.y + 100;
		}
		else {
			itemRect.x = window.x + 200 + itemRect.w * (i % 5);
			itemRect.y = window.y + 100 + itemRect.h;
		}
		if (i == coursorPosition) SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		else SDL_SetRenderDrawColor(ren, 0, 200, 192, 255);
		SDL_RenderDrawRect(ren, &itemRect);
		SDL_RenderCopy(ren, texture, NULL, &itemRect);
		if (player.armors[i].ID != 0) SDL_DestroyTexture(texture);
	}
	if (player.armors[coursorPosition].ID != 0) {
		sprintf_s(armorName, "NAME: %s", player.armors[coursorPosition].name);
		sprintf_s(armorPRT, "PRT: %d", player.armors[coursorPosition].armor);
		texture = generateTextureFromText(armorName, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 200;
		ttfRect.y = 780;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		texture = generateTextureFromText(armorPRT, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 200;
		ttfRect.y = 830;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(ren);
	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);
}
void drawPlayerPotions(Player& player, int coursorPosition) {


	SDL_Rect window = { 100, 50, window_width - 200, window_height - 100 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 50);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	SDL_Rect ttfRect;
	SDL_Rect itemRect = { 0,0,264,265 };
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("POTIONS INVENTORY", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 70;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char money[30];

	ttfRect.x += ttfRect.w;
	sprintf_s(money, "MONEY: %d coins", player.money);
	texture = generateTextureFromText(money, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.y = window.y + window.h - ttfRect.h - UNIT_SIZE_Y * 2;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char textureWay[100], potionName[22], potionREG[15];

	for (int i = 0; i < MAX_PLAYER_INVENTORY_SIZE; i++) {
		sprintf_s(textureWay, "Textures\\%d.png", player.potions[i].ID);
		if (player.potions[i].ID != 0) texture = generateTextureFromPNG(textureWay);

		if (i <= (MAX_PLAYER_INVENTORY_SIZE / 2) - 1)
		{
			itemRect.x = window.x + 200 + itemRect.w * i;
			itemRect.y = window.y + 100;
		}
		else {
			itemRect.x = window.x + 200 + itemRect.w * (i % 5);
			itemRect.y = window.y + 100 + itemRect.h;
		}
		if (i == coursorPosition) SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		else SDL_SetRenderDrawColor(ren, 0, 200, 192, 255);
		SDL_RenderDrawRect(ren, &itemRect);
		SDL_RenderCopy(ren, texture, NULL, &itemRect);
		if (player.potions[i].ID != 0) SDL_DestroyTexture(texture);
	}

	if (player.potions[coursorPosition].ID != 0) {
		sprintf_s(potionName, "NAME: %s", player.potions[coursorPosition].name);
		texture = generateTextureFromText(potionName, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 200;
		ttfRect.y = 780;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		if (player.potions[coursorPosition].health != 0)sprintf_s(potionREG, "HP Regen: %d", player.potions[coursorPosition].health);
		if (player.potions[coursorPosition].mana != 0)sprintf_s(potionREG, "MP Regen: %d", player.potions[coursorPosition].mana);
		texture = generateTextureFromText(potionREG, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 200;
		ttfRect.y = 830;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}
void drawHeroAbilities(Hero& hero, int coursorPosition) {


	SDL_Rect window = { 100, 50, window_width - 200, window_height - 100 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 80);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Rect itemRect = { 0,0,300,300 };
	SDL_Texture* texture;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);

	texture = generateTextureFromText("ABILITIES LIST", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 70;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char textureWay[100], characteristic[30];

	for (int i = 0; i < MAX_ABILITIES; i++) {
		sprintf_s(textureWay, "Textures\\%d.png", hero.abilities[i].ID);
		if (hero.abilities[i].ID != 0) texture = generateTextureFromPNG(textureWay);

		if (i <= (MAX_ABILITIES / 2) - 1)
		{
			itemRect.x = window.x + 210 + itemRect.w * i;
			itemRect.y = window.y + 100;
		}
		else {
			itemRect.x = window.x + 210 + itemRect.w * (i % 4);
			itemRect.y = window.y + 100 + itemRect.h;
		}
		if (i == coursorPosition) SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		else SDL_SetRenderDrawColor(ren, 0, 200, 192, 255);
		SDL_RenderDrawRect(ren, &itemRect);
		SDL_RenderCopy(ren, texture, NULL, &itemRect);
		if (hero.abilities[i].ID != 0) SDL_DestroyTexture(texture);
	}

	if (hero.abilities[coursorPosition].ID != 0) {
		sprintf_s(characteristic, "NAME: %s", hero.abilities[coursorPosition].name);
		texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 210;
		ttfRect.y = 780;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
		if (hero.abilities[coursorPosition].type == ATTACKING)sprintf_s(characteristic, "TYPE: Attacking");
		if (hero.abilities[coursorPosition].type == BUFFING)sprintf_s(characteristic, "TYPE: Buff");
		texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 210;
		ttfRect.y = 810;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		if (hero.abilities[coursorPosition].type == ATTACKING) {

			sprintf_s(characteristic, "DMG: %d", hero.abilities[coursorPosition].damage);
			texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + 210;
			ttfRect.y = 840;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

			switch (hero.abilities[coursorPosition].effect) {
			case NORMAL:
				sprintf_s(characteristic, "DEBUFF: None");
				break;
			case STUNED:
				sprintf_s(characteristic, "DEBUFF: Stun");
				break;
			case BURN:
				sprintf_s(characteristic, "DEBUFF: Burn");
				break;
			case POISONED:
				sprintf_s(characteristic, "DEBUFF: Poison");
				break;
			case MARKED:
				sprintf_s(characteristic, "DEBUFF: Mark");
				break;
			}
			texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + 210;
			ttfRect.y = 870;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

		}

		if (hero.abilities[coursorPosition].type == BUFFING) {

			sprintf_s(characteristic, "BUFF: %d", hero.abilities[coursorPosition].buff);
			texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + 210;
			ttfRect.y = 840;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

			switch (hero.abilities[coursorPosition].buffedCharacteristic) {
			case HEALTH:
				sprintf_s(characteristic, "STAT: Health");
				break;
			case ARMOR:
				sprintf_s(characteristic, "STAT: Armor");
				break;
			case DAMAGE:
				sprintf_s(characteristic, "STAT: Damage");
				break;
			}
			texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + 210;
			ttfRect.y = 870;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

		}

		sprintf_s(characteristic, "MANACOST: %d", hero.abilities[coursorPosition].manaCost);
		texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 210;
		ttfRect.y = 900;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(characteristic, "STAMINACOST: %d", hero.abilities[coursorPosition].staminaCost);
		texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 210;
		ttfRect.y = 930;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

		sprintf_s(characteristic, "COOLDOWN: %d", hero.abilities[coursorPosition].cooldown);
		texture = generateTextureFromText(characteristic, choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + 210;
		ttfRect.y = 960;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);

	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}



void drawSeller(int typeOfSeller, int coursorPosition) {
	SDL_Rect window = { 0,0,UNIT_SIZE_X * 20,UNIT_SIZE_Y * 20 };
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 30);
	SDL_Texture* texture;
	SDL_Rect ttfRect;


	window.x = UNIT_SIZE_X * 2;
	window.y = window_height - window.h - UNIT_SIZE_Y * 2;

	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);
	SDL_Rect seller = {0, 0, UNIT_SIZE_X * 12, UNIT_SIZE_X * 12 };
	seller.x = window.x + window.w / 2 - seller.w / 2;
	seller.y = window.y + UNIT_SIZE_X * 4;

	if (typeOfSeller == 1) texture = generateTextureFromPNG("Textures\\Sell_weaponF.png");
	else
	if (typeOfSeller == 2) texture = generateTextureFromPNG("Textures\\Sell_armorF.png");
	else
	if (typeOfSeller == 3) texture = generateTextureFromPNG("Textures\\Sell_potionF.png");
	else texture = generateTextureFromPNG("Textures\\Sell_magicF.png");
	SDL_RenderCopy(ren, texture, NULL, &seller);
	SDL_DestroyTexture(texture);



	if (coursorPosition == 0)texture = generateTextureFromText(">Buy", choicesFont, ttfRect, { 0,0,0,255 });
	else texture = generateTextureFromText("Buy", choicesFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window.x + UNIT_SIZE_X * 3;
	ttfRect.y = 900;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (typeOfSeller != 4)
	{
		if (coursorPosition == 1)texture = generateTextureFromText(">Sell", choicesFont, ttfRect, { 0,0,0,255 });
		else texture = generateTextureFromText("Sell", choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + UNIT_SIZE_X * 3;
		ttfRect.y += 40;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}
	else
	{
		if (coursorPosition == 1)texture = generateTextureFromText(">Forget", choicesFont, ttfRect, { 0,0,0,255 });
		else texture = generateTextureFromText("Forget", choicesFont, ttfRect, { 0,0,0,255 });
		ttfRect.x = window.x + UNIT_SIZE_X * 3;
		ttfRect.y += 40;
		SDL_RenderCopy(ren, texture, NULL, &ttfRect);
		SDL_DestroyTexture(texture);
	}



	SDL_RenderPresent(ren);
	TTF_CloseFont(choicesFont);

}

void drawSellerChoice(int coins, SellerOfWeapons seller, int coursorPosition) {

	SDL_Rect window = { 0,0,UNIT_SIZE_X * 20,UNIT_SIZE_Y * 20 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 35);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	window.x = UNIT_SIZE_X * 2;
	window.y = window_height - window.h - UNIT_SIZE_Y * 2;



	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);
	SDL_Rect choiceRect = { window.x + 49,0,650, 22 };

	choiceRect.y = window.y + 79 + coursorPosition * 30;
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
	SDL_RenderFillRect(ren, &choiceRect);

	texture = generateTextureFromText("WEAPONS", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = (window.x + window.w) / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + UNIT_SIZE_Y;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char money[30];


	sprintf_s(money, "MONEY: %d coins", coins);
	texture = generateTextureFromText(money, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = (window.x + window.w) / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + window.h - ttfRect.h - UNIT_SIZE_Y * 2;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char weaponName[30], weaponDMG[20], weaponPrice[20];


	for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {

		if (seller.weapons[i].ID != 0) {
			sprintf_s(weaponName, "NAME: %-15s", seller.weapons[i].name);
			texture = generateTextureFromText(weaponName, choicesFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + 50;
			ttfRect.y = window.y + 80 + i * 30;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 300;
			sprintf_s(weaponDMG, "DMG: %-3d", seller.weapons[i].damage);
			texture = generateTextureFromText(weaponDMG, choicesFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 150;
			sprintf_s(weaponPrice, "PRICE: %d coins", seller.weapons[i].price);
			texture = generateTextureFromText(weaponPrice, choicesFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

		}

	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}
void drawSellerChoice(int coins, SellerOfArmors seller, int coursorPosition) {

	SDL_Rect window = { 0,0,UNIT_SIZE_X * 20,UNIT_SIZE_Y * 20 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 35);
	TTF_Font* choicesFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	window.x = UNIT_SIZE_X * 2;
	window.y = window_height - window.h - UNIT_SIZE_Y * 2;



	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);
	SDL_Rect choiceRect = { window.x + 49,0,650, 22 };

	choiceRect.y = window.y + 79 + coursorPosition * 30;
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
	SDL_RenderFillRect(ren, &choiceRect);

	texture = generateTextureFromText("ARMORS", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = (window.x + window.w) / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + UNIT_SIZE_Y;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char money[30];

	sprintf_s(money, "MONEY: %d coins", coins);
	texture = generateTextureFromText(money, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = (window.x + window.w) / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + window.h - ttfRect.h - UNIT_SIZE_Y * 2;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char armorName[30], armorPRT[20], armorPrice[20];


	for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {

		if (seller.armors[i].ID != 0) {
			sprintf_s(armorName, "NAME: %-15s", seller.armors[i].name);
			texture = generateTextureFromText(armorName, choicesFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + 50;
			ttfRect.y = window.y + 80 + i * 30;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 300;
			sprintf_s(armorPRT, "PRT: %-3d", seller.armors[i].armor);
			texture = generateTextureFromText(armorPRT, choicesFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 150;
			sprintf_s(armorPrice, "PRICE: %d coins", seller.armors[i].price);
			texture = generateTextureFromText(armorPrice, choicesFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

		}

	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(choicesFont);

}
void drawSellerChoice(int coins, SellerOfPotions seller, int coursorPosition) {

	SDL_Rect window = { 0,0,UNIT_SIZE_X * 20,UNIT_SIZE_Y * 20 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 35);
	TTF_Font* basicFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	window.x = UNIT_SIZE_X * 2;
	window.y = window_height - window.h - UNIT_SIZE_Y * 2;



	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);
	SDL_Rect choiceRect = { window.x + 49,0,650, 22 };

	choiceRect.y = window.y + 79 + coursorPosition * 30;
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
	SDL_RenderFillRect(ren, &choiceRect);

	texture = generateTextureFromText("POTIONS", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = (window.x + window.w) / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + UNIT_SIZE_Y;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char money[30];

	sprintf_s(money, "MONEY: %d coins", coins);
	texture = generateTextureFromText(money, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = (window.x + window.w) / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + window.h - ttfRect.h - UNIT_SIZE_Y * 2;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char potionName[30], potionHeal[20], potionPrice[20];


	for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {

		if (seller.potions[i].ID != 0) {
			sprintf_s(potionName, "NAME: %-15s", seller.potions[i].name);
			texture = generateTextureFromText(potionName, basicFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + 50;
			ttfRect.y = window.y + 80 + i * 30;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 300;
			if (seller.potions[i].health != 0) sprintf_s(potionHeal, "HP: %-3d", seller.potions[i].health);
			if (seller.potions[i].health != 0) sprintf_s(potionHeal, "MP: %-3d", seller.potions[i].mana);
			texture = generateTextureFromText(potionHeal, basicFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 150;
			sprintf_s(potionPrice, "PRICE: %d coins", seller.potions[i].price);
			texture = generateTextureFromText(potionPrice, basicFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

		}

	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(basicFont);

}
void drawSellerChoice(int coins, SellerOfAbilities seller, int coursorPosition) {

	SDL_Rect window = { 100, 50, window_width - 200, window_height - 100 };
	TTF_Font* headerFont = TTF_OpenFont("Fonts\\basicFont.ttf", 40);
	TTF_Font* basicFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Rect ttfRect;
	SDL_Texture* texture;

	window.x = UNIT_SIZE_X * 2;
	window.y = window_height - window.h - UNIT_SIZE_Y * 2;



	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);
	SDL_Rect choiceRect = { window.x + UNIT_SIZE_X - 1, 0,window.w - UNIT_SIZE_X * 3, 22 };

	choiceRect.y = window.y + UNIT_SIZE_Y * 2.5 - 1 + coursorPosition * 30;
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
	SDL_RenderFillRect(ren, &choiceRect);

	texture = generateTextureFromText("ABILITIES", headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = window_width / 2 - ttfRect.w / 2;
	ttfRect.y = 70;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	char money[30];

	sprintf_s(money, "MONEY: %d coins", coins);
	texture = generateTextureFromText(money, headerFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = (window.x + window.w) / 2 - ttfRect.w / 2;
	ttfRect.y = window.y + window.h - ttfRect.h - UNIT_SIZE_Y * 2;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);



	char  characteristic[30];

	
	for (int i = 0; i < MAX_ABILITIES; i++) {

		if (seller.abilities[i].ID != 0) {
			sprintf_s(characteristic, "%-15s", seller.abilities[i].name);
			texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
			ttfRect.x = window.x + UNIT_SIZE_X;
			ttfRect.y = window.y + UNIT_SIZE_Y * 2.5 + i * 30;
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 150;
			if (seller.abilities[i].type == ATTACKING) {
				texture = generateTextureFromText("TYPE: ATTACK", basicFont, ttfRect, { 0,0,0,255 });
				SDL_RenderCopy(ren, texture, NULL, &ttfRect);
				SDL_DestroyTexture(texture);
				ttfRect.x += 200;
				sprintf_s(characteristic, "DMG: %-3d", seller.abilities[i].damage);
				texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
				SDL_RenderCopy(ren, texture, NULL, &ttfRect);
				SDL_DestroyTexture(texture);
				ttfRect.x += 150;
				switch (seller.abilities[i].effect) {
				case NORMAL:
					sprintf_s(characteristic, "DEBUFF: None");
					break;
				case STUNED:
					sprintf_s(characteristic, "DEBUFF: Stun");
					break;
				case BURN:
					sprintf_s(characteristic, "DEBUFF: Burn");
					break;
				case POISONED:
					sprintf_s(characteristic, "DEBUFF: Poison");
					break;
				case MARKED:
					sprintf_s(characteristic, "DEBUFF: Mark");
					break;
				}
				texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
				SDL_RenderCopy(ren, texture, NULL, &ttfRect);
				SDL_DestroyTexture(texture);
				ttfRect.x += 200;

			}
			else {
				texture = generateTextureFromText("TYPE: BUFF", basicFont, ttfRect, { 0,0,0,255 });
				SDL_RenderCopy(ren, texture, NULL, &ttfRect);
				SDL_DestroyTexture(texture);
				ttfRect.x += 200;
				sprintf_s(characteristic, "BUFF: %-3d", seller.abilities[i].buff);
				texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
				SDL_RenderCopy(ren, texture, NULL, &ttfRect);
				SDL_DestroyTexture(texture);
				ttfRect.x += 150;
				switch (seller.abilities[i].buffedCharacteristic) {
				case HEALTH:
					sprintf_s(characteristic, "STAT: Health");
					break;
				case ARMOR:
					sprintf_s(characteristic, "STAT: Armor");
					break;
				case DAMAGE:
					sprintf_s(characteristic, "STAT: Damage");
					break;
				}
				texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
				SDL_RenderCopy(ren, texture, NULL, &ttfRect);
				SDL_DestroyTexture(texture);
				ttfRect.x += 200;
			}
			
			sprintf_s(characteristic, "MANACOST: %d", seller.abilities[i].manaCost);
			texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 200; 
			
			sprintf_s(characteristic, "STAMINACOST: %d", seller.abilities[i].staminaCost);
			texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 250;
			
			sprintf_s(characteristic, "COOLDOWN: %d", seller.abilities[i].cooldown);
			texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);
			ttfRect.x += 200;
			
			sprintf_s(characteristic, "PRICE: %d coins", seller.abilities[i].price);
			texture = generateTextureFromText(characteristic, basicFont, ttfRect, { 0,0,0,255 });
			SDL_RenderCopy(ren, texture, NULL, &ttfRect);
			SDL_DestroyTexture(texture);

		}
		
	}

	SDL_RenderPresent(ren);

	TTF_CloseFont(headerFont);
	TTF_CloseFont(basicFont);

}

void drawInkeeperDialog(int restorePrice, int revivePrice, int money, int coursorPosition) {
	SDL_Rect window = {0,0,window_width - 500,150};
	TTF_Font* basicFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Texture* texture;
	SDL_Rect ttfRect;
	SDL_Texture* face = generateTextureFromPNG("Textures\\InkeeperF.png");


	char text[35];

	window.x = (window_width - window.w) / 2;
	window.y = window_height - 50 - window.h;


	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);
	SDL_Rect faceRect = { window.x + 10, window.y + 10, 130, 130 };
	SDL_RenderCopy(ren, face, NULL, &faceRect);
	SDL_DestroyTexture(face);
	

	texture = generateTextureFromText("Hello adventure! Do you need my help?", basicFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = faceRect.x + faceRect.w + 50;
	ttfRect.y = faceRect.y + 10;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	if (coursorPosition == 0) sprintf_s(text, ">Restore heroes healthes(%d coins)", restorePrice);
	else sprintf_s(text, "Restore heroes healthes(%d coins)", restorePrice);
	texture = generateTextureFromText(text, basicFont, ttfRect, { 0,0,0,255 });
	ttfRect.y += 60;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);
	
	if (coursorPosition == 1) sprintf_s(text, ">Revive 1 hero(%d coins)", revivePrice);
	else sprintf_s(text, "Revive 1 hero(%d coins)", revivePrice);
	texture = generateTextureFromText(text, basicFont, ttfRect, { 0,0,0,255 });
	ttfRect.y += 30;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);

	sprintf_s(text, "MONEY: %d", money);
	texture = generateTextureFromText(text, basicFont, ttfRect, { 0,0,0,255 });
	ttfRect.y = window.y + window.h - ttfRect.h - 10;
	ttfRect.x = window.x + window.w - ttfRect.w - 10;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);
	
	SDL_RenderPresent(ren);
}

void drawInkeeperReject() {
	SDL_Rect window = { 0,0,window_width - 500,150 };
	TTF_Font* basicFont = TTF_OpenFont("Fonts\\basicFont.ttf", 20);
	SDL_Texture* texture;
	SDL_Rect ttfRect;
	SDL_Texture* face = generateTextureFromPNG("Textures\\InkeeperF.png");


	window.x = (window_width - window.w) / 2;
	window.y = window_height - 50 - window.h;


	SDL_SetRenderDrawColor(ren, 28, 181, 192, 255);
	SDL_RenderFillRect(ren, &window);
	SDL_Rect faceRect = { window.x + 10, window.y + 10, 130, 130 };
	SDL_RenderCopy(ren, face, NULL, &faceRect);
	SDL_DestroyTexture(face);


	texture = generateTextureFromText("You don't need my help with this...", basicFont, ttfRect, { 0,0,0,255 });
	ttfRect.x = faceRect.x + faceRect.w + 50;
	ttfRect.y = faceRect.y + 10;
	SDL_RenderCopy(ren, texture, NULL, &ttfRect);
	SDL_DestroyTexture(texture);


	SDL_RenderPresent(ren);
	SDL_Delay(2000);
}