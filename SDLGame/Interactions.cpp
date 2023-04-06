#include "Interactions.h"


void interact(char** map, Player& player) {


	int tempX1 = 0, tempX2 = 0;
	int tempY1 = 0, tempY2 = 0;
	if (player.diraction == UP) {
		tempY1 = floorf(player.position.Y) - 1;
		tempX1 = floorf(player.position.X);
		tempX2 = ceilf(player.position.X);

		if (map[tempY1][tempX1] == NPC || map[tempY1][tempX2] == NPC) player.position.Y += 5;
		if (map[tempY1][tempX1] == NPC || map[tempY1][tempX2] == NPC) player.position.Y += 5;
		if (map[tempY1][tempX1] == NPC || map[tempY1][tempX2] == NPC) player.position.Y += 5;
	}
	if (player.diraction == LEFT) {
		tempX1 = floorf(player.position.X) - 1;
		tempY1 = floorf(player.position.Y);
		tempY2 = ceilf(player.position.Y);

		if (map[tempY1][tempX1] == NPC || map[tempY2][tempX1] == NPC) player.position.X += 5;

	}
	if (player.diraction == RIGHT) {
		tempX1 = floorf(player.position.X) + 1;
		tempY1 = floorf(player.position.Y);
		tempY2 = ceilf(player.position.Y);

		if (map[tempY1][tempX1] == NPC || map[tempY2][tempX1] == NPC) player.position.X += 5;



	}



}