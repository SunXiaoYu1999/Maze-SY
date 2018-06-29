#include"stdafx.h"
#include<Windows.h>
#include<conio.h>

void gotoxy(int y, int x)
{
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}