#include <stdio.h>
#include <Windows.h>
#define WIDTH 14        //가로
#define HEIGHT 22        //세로
int x = 10, y = 0;
int blockForm;
int blockRotation = 0;

typedef struct
{
	int x;
	int y;
}Block;

Block block;

int block[7][4][4] = {
{	//일자 'ㅣ' 
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
},
//L
{
{1,0,0,0},
{1,0,0,0},
{1,1,0,0},
{0,0,0,0},
},
//ㅓ
{
{0,1,0,0},
{1,1,0,0},
{0,1,0,0},
{0,0,0,0},
},
//ㅁ 
{
{1,1,0,0},
{1,1,0,0},
{0,0,0,0},
{0,0,0,0},
},
//L반대 
{
{0,1,0,0},
{0,1,0,0},
{1,1,0,0},
{0,0,0,0},
},
//z반대 
{
{0,1,1,0},
{1,1,0,0},
{0,0,0,0},
{0,0,0,0},
},
//z
{
{1,1,0,0},
{0,1,1,0},
{0,0,0,0},
{0,0,0,0},
}

};

int isKeyDown(int key)
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}



void gotoxy(int x, int y)
{

	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Move()
{

	if (isKeyDown(VK_LEFT))
		block.x--;
	if (isKeyDown(VK_RIGHT))
		block.x++;

	if (block.x < 0)
		block.x = 0;
	if (block.x > WIDTH - 1)
		block.x = WIDTH - 1;
}


	int arr[22][14] = {
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1}
};

	void CreateBlockForm() {
		blockForm = rand() % 7;
	}


	void RemoveLine() {
		for (int i = 21; i >= 0; i--) {
			int cnt = 0;
			for (int j = 1; j < 13; j++) {
				if (arr[i][j] == 2) {
					cnt++;
				}
			}
			if (cnt >= 12) {
				for (int j = 0; i - j >= 0; j++) {
					for (int x = 1; x < 13; x++) {
						if (i - j - 1 >= 0)
							arr[i - j][x] = arr[i - j - 1][x];
						else
							arr[i - j][x] = 0;
					}
				}
			}
		}
	}
	
	void Map() {
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 14; j++) {
			if (arr[i][j] == 1) {
				printf("■");
			}
			else if (arr[i][j] == 0) {
				printf("  ");
			}
		}
		printf("\n");
	}

}

void DrawBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				printf("■");
			}
		}
	}
}


int main() {
	Map();
}