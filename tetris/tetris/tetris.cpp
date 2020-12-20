#pragma warning (disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define maximum(a,b) (((a)>(b))?(a):(b))
#define LEFT 75
#define VER 2
#define RIGHT 77
#define HOR 3
#define UP 72
#define HEI 24
#define DOWN 80
#define WID 10

typedef enum { NOCURSOR } CURSOR_TYPE;
void EntirePrt();
int keyinput(); 
void PrtCombo(int); 
void PrtScore(int, int); 
void Exline();  
void PrtIn(); 
void PrtNB(int); 
void PrtBlock(int); 
void PrtShade(int); 
void Prtstage(); 
int ExSur(int, int, int, int); 
int Downonce();  
void Prtbreak(); 

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void removecursor(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int block[7][4][8] = { {{0,-1,1,-1,-1,0,0,0},{-1,-1,-1,0,0,0,0,1},{0,-1,1,-1,-1,0,0,0},{-1,-1,-1,0,0,0,0,1}}, // ㄹ
					  {{0,0,1,0,0,-1,-1,-1},{-1,1,-1,0,0,0,0,-1},{0,0,1,0,0,-1,-1,-1},{-1,1,-1,0,0,0,0,-1}}, // ㄹ-1
					  {{-2,1,-1,1,0,1,1,1},{-1,2,-1,1,-1,0,-1,-1},{-2,1,-1,1,0,1,1,1},{-1,2,-1,1,-1,0,-1,-1}}, // ㅣ 
					  {{-1,1,0,1,1,1,-1,0},{-1,1,0,1,0,0,0,-1},{0,1,0,0,-1,0,-2,0},{-1,2,-1,1,-1,0,0,0}}, // ㄴ 
					  {{-1,1,0,1,-1,0,0,0},{-1,1,0,1,-1,0,0,0},{-1,1,0,1,-1,0,0,0},{-1,1,0,1,-1,0,0,0}}, // ㅁ 
					  {{-2,1,-1,1,0,1,0,0},{0,2,0,1,0,0,-1,0},{-1,1,-1,0,0,0,1,0},{-1,1,0,1,-1,0,-1,-1}},// ㄴ-1
					  {{0,1,-1,0,0,0,1,0},{0,1,0,0,1,0,0,-1},{-1,0,0,0,1,0,0,-1},{0,1,0,0,-1,0,0,-1}} }; // ㅗ 

FILE *f,*ff;
int Block, Shape, n_Block, n_Shape;  
int nx, ny; 
int Speed = 20, Stay; 
int score = 0;
int level = 1, breaks = 0;
int Sh = 1; 
int board[WID + 2][HEI + 2];
enum { EMPTY, BLOCK, nBLOCK, WALL, Shadow };
const char *BStates[5] = { "  ","■","■","▒","□" };

int main() {
	char buffer[22];
	int comp, i, j;
	char ch;
	system("cls");
	for (i = 0; i < WID + 2; i++) for (j = 0; j < HEI + 2; j++)board[i][j] = (i == 0 || i == WID + 1 || j == HEI + 1) ? WALL : EMPTY;
	removecursor(NOCURSOR);
	EntirePrt();
	srand((unsigned)time(NULL));
	Block = rand() % 7;
	Shape = rand() % 4;
	

	for (; 1;) {
		n_Block = rand() % 7;
		n_Shape = rand() % 4; 
		nx = WID / 2;
		ny = 1;
		PrtNB(TRUE);
		if (Sh == TRUE)PrtShade(TRUE);
		PrtBlock(TRUE);
		if (ExSur(nx, ny, Block, Shape) != 0)break;
		Stay = Speed;
		for (; 2;) {
			if (--Stay == 0) {
				Stay = Speed;
				if (Downonce())break;
			}
			if (keyinput())break;

			Sleep(50);
		}
		PrtNB(FALSE);
		Block = n_Block;
		Shape = n_Shape;
	}
	char over;
	system("cls");
	gotoxy(21, 10);printf("▣      G a m e    O v e r      ▣");
	ff = fopen("score.txt", "r");
	fgets(buffer, 22, ff);
	comp = atoi(buffer);
	score = score > comp ? score : comp;
	fclose(ff);
	f = fopen("score.txt", "w");
	fprintf(f, "%d",score);
	fclose(f);
	over = getch();
	return 0;
}

void PrtBlock(int tmp) {
	int i;
	for (i = 0; i < 8; i += 2) {
		gotoxy(HOR + (block[Block][Shape][i] + nx) * 2, VER + block[Block][Shape][i + 1] + ny);
		puts(BStates[tmp ? BLOCK : EMPTY]);
	}
}

void EntirePrt() { 
	int i, j;
	for (i = 0; i < WID + 2; i++) {
		for (j = 0; j < HEI + 2; j++) {
			gotoxy(HOR + i * 2, VER + j);
			puts(BStates[board[i][j]]);
		}
	}
	gotoxy(34, 2);printf("──  next block ──\n");
	PrtScore(0, 0);
	Prtstage();
	Prtbreak();
}

int ExSur(int x, int y, int z, int r) { 
	int i, k = EMPTY;
	for (i = 0; i < 8; i += 2) k = maximum(k, board[x + block[z][r][i]][y + block[z][r][i + 1]]); 
	return k; 
}

int Downonce() { 
	if (ExSur(nx, ny + 1, Block, Shape) != EMPTY) {
		Exline();
		return TRUE;
	}
	PrtBlock(FALSE);
	ny++;
	PrtBlock(TRUE);
	return FALSE;
}

void Exline() { 
	int i, j, x, y, combo = 0, n = 0;
	for (i = 0; i < 8; i += 2) {
		board[nx + block[Block][Shape][i]][ny + block[Block][Shape][i + 1]] = nBLOCK;
		gotoxy(HOR + (block[Block][Shape][i] + nx) * 2, VER + block[Block][Shape][i + 1] + ny);
		puts(BStates[nBLOCK]);
	}
	for (i = 1; i < HEI + 1; i++) {
		for (j = 1; j < WID + 1; j++) if (board[j][i] != nBLOCK)break; 
		if (j == WID + 1) {
			n++;
			PrtCombo(++combo);
			for (x = i; x > 1; x--) for (y = 1; y < WID + 1; y++) board[y][x] = board[y][x - 1];
			breaks++;
			Prtbreak();
			Sleep(400);
			PrtIn();
		}
	}
	combo = 0;
	if (breaks >= 10)Prtstage();
}

int keyinput() {
	char ch;
	if (kbhit()) {
		ch = getch();
		switch (ch) {
		case LEFT:
			if (ExSur(nx - 1, ny, Block, Shape) == EMPTY) {
				PrtBlock(FALSE);
				if (Sh == TRUE) PrtShade(FALSE);
				nx--;
				if (Sh == TRUE)PrtShade(TRUE);
				PrtBlock(TRUE);
			}
			break;
		case RIGHT:
			if (ExSur(nx + 1, ny, Block, Shape) == EMPTY) {
				PrtBlock(FALSE);
				if (Sh == TRUE)PrtShade(FALSE);
				nx++;
				if (Sh == TRUE)PrtShade(TRUE);
				PrtBlock(TRUE);
			}
			break;
		case UP:
			if (ExSur(nx, ny, Block, (Shape + 1) % 4) == EMPTY) {
				PrtBlock(FALSE);
				if (Sh == TRUE)PrtShade(FALSE);
				Shape = (Shape + 1) % 4;
				if (Sh == TRUE)PrtShade(TRUE);
				PrtBlock(TRUE);
			}
			break;
		case DOWN:
			if (Downonce()) return TRUE;
			break;
		case ' ':
			while (Downonce() == FALSE);
			return TRUE;
		}
	}
	return FALSE;
}

void PrtIn() { 
	int i, j;
	for (i = 1; i < WID + 1; i++) {
		for (j = 1; j < HEI + 1; j++) {
			gotoxy(HOR + i * 2, VER + j);
			puts(BStates[board[i][j]]);
		}
	}
}

void PrtNB(int tmp) { 
	int i;
	for (i = 0; i < 8; i += 2) {
		gotoxy(43 + block[n_Block][n_Shape][i] * 2, 5 + block[n_Block][n_Shape][i + 1]);
		puts(BStates[tmp ? BLOCK : EMPTY]);  
	}
}

void PrtScore(int x, int y) { 
	char buffer[22];
	FILE *f = fopen("score.txt", "r");
	fgets(buffer, 22, f);
	gotoxy(28, 24);
	printf("  Best score : %s", buffer);
	score += x; score += y;
	gotoxy(28, 26);
	printf("  Score : %d", score);
}

void PrtShade(int tmp) {
	int i;
	int yy;
	for (yy = ny; ExSur(nx, yy, Block, Shape) == EMPTY; yy++);
	for (i = 0; i < 8; i += 2) {
		gotoxy(HOR + (block[Block][Shape][i] + nx) * 2, VER + block[Block][Shape][i + 1] + yy - 1);
		puts(BStates[tmp ? Shadow : EMPTY]);
	}
}

void PrtCombo(int x) {
	gotoxy(HOR + 8, 8);
	printf("%d combo", x);
	gotoxy(HOR + 16, 9);
	printf("+%d", x*x * 100);
	gotoxy(HOR + 16, 10);
	printf("+%d", level*x * 100);
	PrtScore(x*x * 100, level*x * 100);
}

void Prtbreak() {
	gotoxy(30, 25);
	printf("Breaks : %d/10", breaks);
}

void Prtstage() {
	int i, j;
	if (breaks >= 10) {
		gotoxy(HOR + 8, 8);
		printf("next stage");
		breaks = 0;

		for (i = HEI; i > HEI - level; i--) {
			for (j = 1; j < WID + 1; j++) {
				gotoxy(HOR + j * 2, VER + i);
				puts("♠");
				Sleep(40);
			}
		}
		Sleep(99);
		for (i = HEI; i > level - 1; i--) for (j = 1; j < WID + 1; j++) board[j][i] = board[j][i - level];
		Sleep(250);
		PrtIn();
		if (Speed > 4)Speed -= 4;
		else Speed = 2;
		level++;
		if (level == 7)Sh = FALSE;
	}
	gotoxy(30, 27);
	printf("Level : %d", level);
	Prtbreak();
}