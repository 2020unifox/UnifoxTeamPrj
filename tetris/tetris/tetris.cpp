#include <Windows.h>
#include <iostream>

#define U 72
#define D 80
#define L 75
#define R 77
#define S 32
#define MAP_X 12
#define MAP_Y 22

void keycheck();
void gamecheck();
void pause();
void drop();
void clear();
void removeCursor();
void gotoxy(int, int);

typedef struct blocks {
	int tmp[3][3];
	char colors;
	char blocktype;
};

int main()
{
	char map[MAP_X][MAP_Y] = { 0 };
	int key;
	blocks b;
	removeCursor();
}

void removeCursor()
{
	CONSOLE_CURSOR_INFO cf;
	cf.bVisible = 0;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cf);
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
