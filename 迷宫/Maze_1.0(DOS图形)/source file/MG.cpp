#include"stdafx.h"
#include"MG.h"
#include"InterFace.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<Windows.h>

using std::cout;
using std::cin;
using std::endl;

void Maze::Create_Map()
{
	int a, b;
	srand(time(NULL));
	a = rand() % (line - 2) + 1;
	b = rand() % (col- 2) + 1;
	if (a % 2 == 0)
		a++;
	if (b % 2 == 0)
		b++;
	stock A;
	A.St = new m_node[((col-1)/2)*((line-1)/2)];
	A.top = -1;
	m_node temp;
	temp.x = a; temp.y = b; temp.dir = 0;
	for (int i = 0; i < 4; i++)
		temp.DIR[i] = i + 1;
	A.St[++A.top] = temp; 
	Flag_Way(temp,MAP); // 标记四个方向上的可走墙
	Print_Way(temp.x, temp.y);
	MAP[temp.x][temp.y] = WAY; // 走过的路标记为-1
	int dir = A.St[A.top].dir;
	int Dir = A.St[A.top].DIR[dir];
	int find, x, y;
	while (A.top > -1) {
		find = 0;
		while (dir < 4 && find == 0) {
			switch (Dir) {
			case 1:
				x = A.St[A.top].x - 1;
				y = A.St[A.top].y;
				if (MAP[x][y] == 2) {
					x = A.St[A.top].x - 2;
					y = A.St[A.top].y;
					if (MAP[x][y] == 1) { 
						find = 1;
						MAP[x + 1][y] = -1;
						Print_Way(x+1,y);
						Print_Way(x,y);
					}
					else {
						MAP[x + 1][y] = WALL;
					}
				}
				else {
					dir++;
					Dir = A.St[A.top].DIR[dir];
				}
				break;
			case 2:
				x = A.St[A.top].x;
				y = A.St[A.top].y - 1;
				if (MAP[x][y] == 2) {
					x = A.St[A.top].x;
					y = A.St[A.top].y - 2;
					if (MAP[x][y] == 1) {
						find = 1;
						MAP[x][y + 1] = -1;
						Print_Way(x, y + 1);
						Print_Way(x, y);
					}
					else {
						MAP[x][y + 1] = WALL;
					}
				}
				else {
					dir++;
					Dir = A.St[A.top].DIR[dir];
				}
				break;
			case 3:
				x = A.St[A.top].x + 1;
				y = A.St[A.top].y;
				if (MAP[x][y] == 2) {
					x = A.St[A.top].x + 2;
					y = A.St[A.top].y;
					if (MAP[x][y] == 1) {
						find = 1;
						MAP[x - 1][y] = -1;
						Print_Way(x - 1, y);
						Print_Way(x, y);
					}
					else {
						MAP[x - 1][y] = WALL;
					}
				}
				else {
					dir++;
					Dir = A.St[A.top].DIR[dir];
				}
				break;
			case 4:
				x = A.St[A.top].x ;
				y = A.St[A.top].y + 1;
				if (MAP[x][y] == 2) {
					x = A.St[A.top].x;
					y = A.St[A.top].y + 2;
					if (MAP[x][y] == 1) {
						find = 1;
						MAP[x][y - 1] = -1;
						Print_Way(x, y-1);
						Print_Way(x, y);
					}
					else {
						MAP[x][y - 1] = WALL;
					}
				}
				else {
					dir++;
					Dir = A.St[A.top].DIR[dir];
				}
				break;
			}
		}
		if (find == 1) {
			A.St[A.top].dir = dir;
			temp.x = x; temp.y = y; temp.dir = 0; Get_Dir(temp.DIR);
			Flag_Way(temp, MAP);
			MAP[x][y] = WAY;
 			A.St[++A.top] = temp;
			dir = A.St[A.top].dir;
			Dir = A.St[A.top].DIR[dir];
		}
		else {
			temp = A.St[A.top--];
			Print_Space(temp.x, temp.y);
			Print_Space((temp.x + A.St[A.top].x) / 2, (temp.y + A.St[A.top].y) / 2);
			if (A.top > -1) {
				dir = A.St[A.top].dir + 1;
				Dir = A.St[A.top].DIR[dir];
			}
		}
	}
	delete[] A.St;
}

void Maze::Get_Dir(int *Dir)
{
	srand(time(NULL));
	int p, temp;
	for (int i = 0; i < 77; i++) {
		p = rand() % 4;
		temp = Dir[0];
		Dir[0] = Dir[p];
		Dir[p] = temp;
	}
}

void Maze::Flag_Way(m_node temp, int ** MAP)
{
	int x = temp.x;
	int y = temp.y;
	if (x - 2 > 0) {
		if(MAP[x - 1][y] == 0)
			MAP[x - 1][y] = 2; // 可走墙标记为2
	}
	if (y - 2 > 0) {
		if(MAP[x][y - 1] == 0)
			MAP[x][y - 1] = 2;
	}
	if (x + 2 < line ) {
		if(MAP[x + 1][y] == 0)
			MAP[x + 1][y] = 2;
	}
	if (y+2<col) {
		if(MAP[x][y + 1] == 0)
			MAP[x][y + 1] = 2;
	}
}

void Maze::Find_Way_1()
{
	Data start, end;
	cout << " 求解迷宫DFS:\n";
	cout << " 请输入起点坐标:\t";
	cin >> start.Dx >> start.Dy;
	if (start.Dx % 2 == 0)
		start.Dx++;
	if (start.Dy % 2 == 0)
		start.Dy++;
	cout << " 请输入终点坐标:\t";
	cin >> end.Dx >> end.Dy;
	if (end.Dx % 2 == 0)
		end.Dx--;
	if (end.Dy % 2 == 0)
		end.Dy--;
	gotoxy(start.Dx, start.Dy);
	cout << "☆";
	gotoxy(end.Dx, end.Dy);
	cout << "★";
	gotoxy(line + 1, 0);
	Find_Way_1(start,end);
}

void Maze::Find_Way_1(Data start, Data end)
{
	STA sta;
	sta.top = -1;
	Push_In(sta,start); // 起点进栈
	Data temp;
	temp.dir = 1;
	MAP[sta.pos[sta.top].Dx][sta.pos[sta.top].Dy] = FIND_FLAG;
	while (sta.top > -1 && !Is_Equal(sta.pos[sta.top], end)) {
		int find = 0;
		while (find == 0 && temp.dir <= 4)
		{
			switch (temp.dir)
			{
			case 1:
				temp.Dx = sta.pos[sta.top].Dx - 1;
				temp.Dy = sta.pos[sta.top].Dy;
				break;
			case 2:
				temp.Dx = sta.pos[sta.top].Dx;
				temp.Dy = sta.pos[sta.top].Dy + 1;
				break;
			case 3:
				temp.Dx = sta.pos[sta.top].Dx + 1;
				temp.Dy = sta.pos[sta.top].Dy;
				break;
			case 4:
				temp.Dx = sta.pos[sta.top].Dx;
				temp.Dy = sta.pos[sta.top].Dy - 1;
				break;
			}
			if (MAP[temp.Dx][temp.Dy] == WAY)
				find = 1;
			else
				temp.dir++;
		}
		if (find == 1) {
			Push_In(sta, temp);
			Print_Way(temp.Dx, temp.Dy);
			MAP[temp.Dx][temp.Dy] = FIND_FLAG;
			temp.dir = 1;
		}
		else {
			MAP[sta.pos[sta.top].Dx][sta.pos[sta.top].Dy] = WAY;
			Print_Space(sta.pos[sta.top].Dx, sta.pos[sta.top].Dy);
			temp.dir = sta.pos[--sta.top].dir+1;
		}
	}
	gotoxy(line + 4, 0);
	system("pause");
	for (int i = sta.top; i >= 0; i--) {
		MAP[sta.pos[i].Dx][sta.pos[i].Dy] = WAY;
		Print_Space(sta.pos[i].Dx,sta.pos[i].Dy);
	}
	gotoxy(line+6, 0);
	system("pause");
}

void Maze::Find_Way_2()
{
	Data start, end;
	cout << "求解迷宫BFS\n";
	cout << " 请输入起点坐标:\t";
	cin >> start.Dx >> start.Dy;
	if (start.Dx % 2 == 0)
		start.Dx++;
	if (start.Dy % 2 == 0)
		start.Dy++;
	cout << " 请输入终点坐标:\t";
	cin >> end.Dx >> end.Dy;
	if (end.Dx % 2 == 0)
		end.Dx--;
	if (end.Dy % 2 == 0)
		end.Dy--;
	gotoxy(start.Dx, start.Dy);
	cout << "☆";
	gotoxy(end.Dx, end.Dy);
	cout << "★";
	gotoxy(line + 1, 0);
	Find_Way_2(start, end);
}

void Maze::Find_Way_2(Data start, Data end)
{
	QUE dui;
	dui.prior = -1; dui.rear = -1;
	int find = 0;
	Data temp;
	dui.data[++dui.rear].Dx = start.Dx;
	dui.data[dui.rear].Dy = start.Dy;
	dui.data[dui.rear].dir = start.dir;
	MAP[dui.data[dui.rear].Dx][dui.data[dui.rear].Dy] = FIND_FLAG;
	Print_Way(dui.data[dui.rear].Dx, dui.data[dui.rear].Dy);
	Sleep(20);
	//队不为空时进入循环
	while (dui.rear > -1) {
		dui.prior++;//出队
		for (int i = 1; i <= 4; ++i) {
			switch (i)
			{
			case 1:
				temp.Dy = dui.data[dui.prior].Dy - 1;
				temp.Dx = dui.data[dui.prior].Dx;
				temp.dir = dui.prior;
				break;
			case 2:
				temp.Dy = dui.data[dui.prior].Dy;
				temp.Dx = dui.data[dui.prior].Dx + 1;
				temp.dir = dui.prior;
				break;
			case 3:
				temp.Dy = dui.data[dui.prior].Dy + 1;
				temp.Dx = dui.data[dui.prior].Dx;
				temp.dir = dui.prior;
				break;
			case 4:
				temp.Dy = dui.data[dui.prior].Dy;
				temp.Dx = dui.data[dui.prior].Dx - 1;
				temp.dir = dui.prior;
				break;
			}
			if (MAP[temp.Dx][temp.Dy] == WAY) {
				dui.rear++;
				dui.data[dui.rear].Dx = temp.Dx;
				dui.data[dui.rear].Dy = temp.Dy;
				dui.data[dui.rear].dir = temp.dir;
				Print_Way(dui.data[dui.rear].Dx, dui.data[dui.rear].Dy);
				Sleep(20);
				MAP[temp.Dx][temp.Dy] = FIND_FLAG;//;路径为-1
				if (dui.data[dui.rear].Dx == end.Dx && dui.data[dui.rear].Dy == end.Dy) {
					find = 1;
					break;
				}
			}
		}
		if (find == 1)
			break;
	}
	for (int i = 0; i < dui.rear; i++) {
		Print_Space(dui.data[i].Dx, dui.data[i].Dy);
	}
	int T = dui.rear;
	for (; T > -1;) {
		Print_Way(dui.data[T].Dx, dui.data[T].Dy);
		T = dui.data[T].dir;
	}
}

void Maze::Out()
{
	for (int i = 0; i < line; i++) {
		for (int k = 0; k < col; k++) {
			if (MAP[i][k] == -1)
				cout << "  ";
			if(MAP[i][k] == 0)
				cout << "■";
		}
		cout << endl;
	}
}

Maze::Maze()
{
	MAP = NULL;
}

Maze::~Maze()
{
	for (int i = 0; i < line; i++) {
		delete[] MAP[i];
	}
	delete[] MAP;
}

void Maze::Init_Lize()
{
	MAP = new int*[line];
	for (int i = 0; i < line; i++) {
		MAP[i] = new int[col];
	}
	for (int i = 0; i < line; i++) {
		for (int k = 0; k < col; k++) {
			if (i % 2 != 0 && k % 2 != 0)
				MAP[i][k] = 1;
			else
				MAP[i][k] = 0;
		}
	}
	for (int i = 0; i < line; i++) {
		for (int k = 0; k < col; k++) {
			if (MAP[i][k] == 0)
				cout << "■";
			else
				cout << "  ";
		}
		cout << endl;
	}
}

void Maze::Get_XY()
{
	cout << "请输入地图行数 ： ";
	cin >> line;
	if (line % 2 == 0)
		line++;
	cout << "\n请输入列数：";
	cin >> col;
	if (col % 2 == 0)
		col++;
	cout << endl;
	system("cls");
}

void Maze::Print_Way(int x, int y)
{
	gotoxy(x, y);
	cout << "☆";
	Sleep(40);
	gotoxy(line + 1, 0);
}

void Maze::Print_Space(int x, int y)
{
	gotoxy(x, y);
	cout << "  ";
	Sleep(40);
	gotoxy(line + 1, 0);
}

void Push_In(STA &p, Data e)
{
	p.top++;
	p.pos[p.top].Dx = e.Dx;
	p.pos[p.top].Dy = e.Dy;
	p.pos[p.top - 1].dir = e.dir;
}

bool Is_Equal(Data A, Data B)
{
	if (A.Dx == B.Dx && A.Dy == B.Dy)
		return true;
	else
		return false;
}

void Maze::Print_Data_1(int top) 
{
	gotoxy(line + 3, 0);
	cout << "top = " << top;
}

void Maze::Print_Map()
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < line; j++) {
			if (MAP[i][j] == 0)
				cout << "1" << " ,";
			else
				cout << "0" << " ,";
		}
		cout << endl;
	}
}