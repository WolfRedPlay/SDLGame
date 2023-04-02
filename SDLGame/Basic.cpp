#include "Basic.h"

void readMap(char** map, const char* fileName, int size_x, int size_y) {
	FILE* file;
	if (fopen_s(&file, fileName, "rt+") != 0) {
		system("cls");
		printf_s("Openning file error!!!\a");
		exit(-1);
	}
	for (int i = 0; i < size_y; i++)
		for (int j = 0; j < size_x; j++)
			fscanf_s(file, "%c", &map[i][j], sizeof(char));

	fclose(file);
}
