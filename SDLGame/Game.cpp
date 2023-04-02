#include "Basic.h"
#include "Drawer.h"
#include "Mover.h"


SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

bool isRunning = true;



void DeInit(int error) {
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}

void Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf_s("Error: %s!", SDL_GetError());
		DeInit(1);
	}
	win = SDL_CreateWindow("Just Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL) {
		printf_s("Create window error: %s!", SDL_GetError());
		DeInit(1);
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if (ren == NULL) {
		printf_s("Create render error: %s!", SDL_GetError());
		DeInit(1);
	}
}


char** createMapArray(int size_x, int size_y) {
	char** map = (char**)malloc(size_y * sizeof(char*));
	for (int i = 0; i < size_y; i++)
		map[i] = (char*)malloc(size_x * sizeof(char));
	return map;
}



int main(int argc, char* argv[]) {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	char** map = createMapArray(MAP_SIZE_X, MAP_SIZE_Y);
	SDL_Event ev;
	Player player;
	player.keys = 0;
	player.position = { 3.f, 1.f };
	readMap(map, "GlobalMap1.txt", MAP_SIZE_X, MAP_SIZE_Y);
	Init();
	SDL_SetRenderDrawColor(ren, 255, 242, 100, 255);
	SDL_RenderClear(ren);


	while(isRunning){
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;

				}
				
				break;
			
			}
		}

		if (state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]) movePlayer(map, player, { 0, -0.05f });
		if (!state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN]) movePlayer(map, player, { 0, 0.05f });
		if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT]) movePlayer(map, player, { -0.05f, 0 });
		if (!state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT]) movePlayer(map, player, { 0.05f, 0 });
		
		
		drawScreen(map, player.position);
		drawPlayer(player.position);

		SDL_RenderPresent(ren);
		SDL_Delay(10);
	}
	DeInit(0);
	return 0;
}

	//printf_s("x: %f, y: %f\n", player.position.X, player.position.Y);