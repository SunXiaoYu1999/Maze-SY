/**************五子棋小游戏
**  MAP 代表棋盘，MAP[i][j] = 1代表此处是一个白旗，2代表黑棋，0代表没棋
**
**
**
****/
#include "stdafx.h"
#include "GB.h"
#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;
// 游戏界面
void GoBang_GameInterFace()
{
	initgraph(902, 702);
	setbkcolor(RGB(255, 150, 150));       //主背景颜色 
	cleardevice();

	IMAGE temp, temp1;
	loadimage(&temp, L"五子棋.jpg", 600, 99, false);
	putimage(300, 0, &temp);

	loadimage(&temp1, L"用户1.jpg", 300, 700, false);
	putimage(0, 0, &temp1);

	setfillcolor(RGB(206,175,175));      // 棋盘背景颜色
	solidrectangle(300, 100, 900, 700);

	setlinecolor(RGB(0, 0, 0));         // 线条颜色

	for (int x = 300; x <= 900; x += 40) {
		line(x, 100, x, 700);
	}
	for (int y = 100; y <= 700; y += 40) {
		line(300, y, 900, y);
	}
}
// 游戏逻辑
void GoBang_1()
{
	int MAP[15][15] = { 0 };
	GoBang_GameInterFace();
	POS T = { 1,1 };
	COLOR White = { 255,255,255 };             // 白色棋子
	COLOR Black = { 0,0,0 };                   // 黑色棋子
	MOUSE_ARRAY MOU;                       // 鼠标数组
	MOU.len = 225;
	GoBang_InitMouseArray(MOU);
	int count = 0;
	while (count <= 225)
	{
		count++;
		do {
			T = GoBang_MouseReturn(MOU);
		} while (MAP[T.x][T.y] != 0);
		if (count % 2 == 1) {
			MAP[T.x][T.y] = 1;
			GoBang_DrawPiece(T.x, T.y, White);
		}
		else {
			MAP[T.x][T.y] = 2;
			GoBang_DrawPiece(T.x, T.y, Black);
		}

		if (GoBang_GameWin(MAP,T,(count % 2))) {
			int reply;
			if (count % 2 == 0) {
				Sleep(2000);
				reply = GoBang_GameEnd(L"黑棋胜利");
			}
			else {
				Sleep(2000);

				reply = GoBang_GameEnd(L"白棋胜利");
			}
			if (reply == 1)
				break;
			else 
			{
				count = 0;
				memset(MAP, 0, 225 * sizeof(int));
				GoBang_GameInterFace();
			}
		}
	}
}
// 画棋子
void GoBang_DrawPiece(int x, int y, COLOR C)
{
	x *= 40;
	y *= 40;
	x += 300 + 20;
	y += 100 + 20;
	setfillcolor(RGB(C.R, C.G, C.B));
	solidcircle(x, y, 15);
}
// 鼠标响应函数
POS GoBang_MouseReturn(MOUSE_ARRAY &MOU)
{
	MOUSEMSG mou;
	POS temp;
	while (true)
	{
		if(MouseHit())
		{
			mou = GetMouseMsg();
			if (mou.uMsg == WM_LBUTTONDOWN)
			{
				for (int i = 0; i < MOU.len; i++)
				{
					if (mou.x >= MOU.array[i].x_l && mou.x <= MOU.array[i].x_h)
					{
						if (mou.y >= MOU.array[i].y_l && mou.y <= MOU.array[i].y_h)
						{
							temp.y = i % 15;
							temp.x = i / 15;
							return temp;
						}
					}
				}
			}
		}
	}
}
// 初始化鼠标数组
void GoBang_InitMouseArray(MOUSE_ARRAY &MOU)
{
	for (int x = 300,i = 0; x < 900; x += 40)
	{
		for (int y = 100; y < 700; y += 40)
		{
			MOU.array[i].x_l = x;
			MOU.array[i].x_h = x + 40;
			MOU.array[i].y_l = y;
			MOU.array[i].y_h = y + 40;
			i++;
		}
	}
}
// 判断当前位子有没有赢,user = 0，代表黑棋，user = 1代表白旗
int GoBang_GameWin(int MAP[][15], POS pos, int user)
{
	POS temp;
	if (user == 0)
		user = 2;
	POS Dir[4][2] = { 
		{{ 1 , 0 }  ,{ -1 , 0 }},
		{{ 0 , 1 }  ,{  0 ,-1 }},
		{{ 1 ,-1 }  ,{ -1 , 1 }},
		{{ 1 , 1 }  ,{ -1 ,-1 }} 
	};
	for (int i = 0; i < 4; i++) {
		int count = 0;
		temp = pos;
		do{
			temp.x += Dir[i][0].x;
			temp.y += Dir[i][0].y;
			if (MAP[temp.x][temp.y] == user)
				count++;
			else
				break;
		} while (temp.x >=0 && temp.x < 15 && temp.y >= 0 && temp.y < 15 );
		temp = pos;
		do {
			temp.x += Dir[i][1].x;
			temp.y += Dir[i][1].y;
			if (MAP[temp.x][temp.y] == user)
				count++;
			else
				break;
		} while (temp.x >= 0 && temp.x < 15 && temp.y >= 0 && temp.y < 15);
		if (count == 4)
			return 1;
	}
	return 0;
}
// 游戏结束界面
int GoBang_GameEnd(const wchar_t *str)
{
	initgraph(480, 640);

	setbkcolor(RGB(246,146,212));
	cleardevice();

	setfillcolor(RGB(255,255,255));
	solidroundrect(120, 250, 360, 320, 200,200);
	solidroundrect(120, 400, 360, 470,200, 200);

	settextcolor(RGB(63, 150, 235));
	settextstyle(30, 0, L"宋体", 0, 0, FW_BLACK, 0, 0, 0);
	setbkmode(TRANSPARENT);
	outtextxy(182,270, L"返回菜单");

	settextcolor(RGB(63, 150, 235));
	settextstyle(30, 0, L"宋体", 0, 0, FW_BLACK, 0, 0, 0);
	setbkmode(TRANSPARENT);
	outtextxy(182, 420, L"再来一局");

	MOUSEMSG mou;
	srand((unsigned)time(NULL));
	while (true)
	{
		int R = rand() % 256;
		int G = rand() % 256;
		int B = rand() % 256;
		int T = rand() % 100 + 75;
		settextcolor(RGB(R, G, B));
		settextstyle(60, 0, L"宋体", 0, 0, FW_BLACK, 0, 0, 0);
		setbkmode(TRANSPARENT);
		outtextxy(110, 50, str);
		while (MouseHit())
		{
			mou = GetMouseMsg();
			if (mou.uMsg == WM_LBUTTONDOWN)
			{
				if (mou.x > 120 && mou.x < 360 && mou.y > 250 && mou.y < 320)
					return 1;
				if (mou.x > 120 && mou.x < 360 && mou.y > 400 && mou.y < 470)
					return 2;
			}
		}
		Sleep(T);
	}
}
// 游戏菜单界面
int GoBang_Maze()
{
	initgraph(500, 700);
	setbkcolor(RGB(236,112,161));
	cleardevice();

	settextcolor(RGB(213,234,34));
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, L"华文行楷", 0, 0, 900, 0, 0, 0);
	outtextxy(100, 50, L"主菜单");

	setfillcolor(RGB(213,220,219));
	solidroundrect(125, 250, 375, 330, 200, 200);

	setfillcolor(RGB(213, 220, 219));
	solidroundrect(125, 400, 375, 480, 200, 200);

	setfillcolor(RGB(213, 220, 219));
	solidroundrect(125, 550, 375, 630, 200, 200);

	settextcolor(RGB(150, 170, 242));
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, L"华文行楷", 0, 0, 900, 0, 0, 0);
	outtextxy(150, 265, L"双人对战");

	settextcolor(RGB(150, 170, 242));
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, L"华文行楷", 0, 0, 900, 0, 0, 0);
	outtextxy(150, 415, L"人机对战");

	settextcolor(RGB(150, 170, 242));
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, L"华文行楷", 0, 0, 900, 0, 0, 0);
	outtextxy(150, 565, L"退出游戏");

	MOUSEMSG mou;
	while (true)
	{
		while (MouseHit())
		{
			mou = GetMouseMsg();
			if (mou.uMsg == WM_LBUTTONDOWN)
			{
				if (mou.x > 125 && mou.x < 375 && mou.y > 250 && mou.y < 330)
					return 1;
				if (mou.x > 125 && mou.x < 375 && mou.y > 400 && mou.y < 480)
					return 2;
				if (mou.x > 125 && mou.x < 375 && mou.y > 550 && mou.y < 630)
					return 0;
			}
		}
	}
	return 0;
}
// 菜单界面
void GoBang()
{
	int re;
	do {
		re = GoBang_Maze();
		switch (re)
		{
		case 1:
			GoBang_1();
			break;
		case 2:
			GoBang_2();
			break;
		}
	} while (re != 0);
}

void GoBang_2()
{
	int MAP[15][15] = { 0 };
	GoBang_GameInterFace();
	POS T = { 1,1 };
	COLOR White = { 255,255,255 };             // 白色棋子
	COLOR Black = { 0,0,0 };                   // 黑色棋子
	MOUSE_ARRAY MOU;                       // 鼠标数组
	MOU.len = 225;
	GoBang_InitMouseArray(MOU);
	int temp,max;              // 记录最大权值
	int count = 0;
	while (count <= 225)
	{
		count++;
		if (count % 2 == 1)
		{
			do {
				T = GoBang_MouseReturn(MOU);
			} while (MAP[T.x][T.y] != 0);
		}
		else
		{
			max = 0;
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (MAP[i][j] == 0)
					{
						temp = GoBang_CalculateValue(MAP, { i,j }, 2); // 电脑为黑棋，所以user = 2；
						if (max <= temp)
						{
							max = temp;
							T.x = i;
							T.y = j;
						}
					}
				}
			}
		}
		if (count % 2 == 1) {
			MAP[T.x][T.y] = 1;
			GoBang_DrawPiece(T.x, T.y, White);
		}
		else {
			MAP[T.x][T.y] = 2;
			Sleep(500);
			GoBang_DrawPiece(T.x, T.y, Black);
		}
		if (GoBang_GameWin(MAP, T, (count % 2))) {
			int reply;
			if (count % 2 == 0) {
				Sleep(2000);
				reply = GoBang_GameEnd(L"黑棋胜利");
			}
			else {
				reply = GoBang_GameEnd(L"白棋胜利");
				Sleep(2000);
			}
			if (reply == 1)
				break;
			else
			{
				count = 0;
				memset(MAP, 0, 225 * sizeof(int));
				GoBang_GameInterFace();
			}
		}
	}
}
// 计算temp点的权重，并返回，user为电脑的棋色
int GoBang_CalculateValue(int MAP[][15], POS temp, int user)
{
	int type, SumOfValue = 0;
	for (int D = 1; D <= 4; D++)                    // 四个方向统计当前点的权值
	{
		type = GoBang_JudgeType(MAP, temp, user, D,false);
		SumOfValue += GoBang_ValueOfType(type);
		if (user == 1)
			user = 2;
		else
			user = 1;
		type = GoBang_JudgeType(MAP, temp, user, D,true);
		SumOfValue += GoBang_ValueOfType(type);
	}
	return SumOfValue;
}
// user为当前判断的色块，Dir为方向,IsEnemy判断是不是敌方
int GoBang_JudgeType(int MAP[][15], POS temp, int user,int Dir,bool IsEnemy)
{
	MAP[temp.x][temp.y] = user;
	POS D[2];
	switch (Dir)
	{
	case 1:		D[0] = { 1,0 }; D[1] = { -1,0 };
		break;
	case 2:		D[0] = { 0,1 }; D[1] = { 0,-1 };
		break;
	case 3:		D[0] = { 1,-1 }; D[1] = { -1,1 };
		break;
	case 4:		D[0] = { 1,1 }; D[1] = { -1,-1 };
		break;
	}
	POS posL,posR;  // 最左端与最右端
	int len = 0;// 棋子长度
	posL = temp;
	while (posL.x >= 0 && posL.x < 15 && posL.y >= 0 && posL.y < 15 && MAP[posL.x][posL.y] == user)
	{
		posL.x += D[0].x;
		posL.y += D[0].y;
		len++;
	}
	posR = temp;
	while (posR.x >= 0 && posR.x < 15 && posR.y >= 0 && posR.y < 15 && MAP[posR.x][posR.y] == user)
	{
		posR.x += D[1].x;
		posR.y += D[1].y;
		len++;
	}
	len--;       // 加重复一次，所以要减掉
	MAP[temp.x][temp.y] = 0;
	switch (len)
	{
	case 2:
		if (posL.x >= 0 && posL.x < 15 && posL.y >= 0 && posL.y < 15 && posR.x >= 0 && posR.x < 15 && posR.y >= 0 && posR.y < 15)
		{
			if (MAP[posL.x][posL.y] == 0 && MAP[posR.x][posR.y] == 0)
			{
				if (IsEnemy == false)
					return 4;
				else
					return 11;
			}
		}
	case 3:
		if (posL.x >= 0 && posL.x < 15 && posL.y >= 0 && posL.y < 15 && posR.x >= 0 && posR.x < 15 && posR.y >= 0 && posR.y < 15)
		{
			if (MAP[posL.x][posL.y] == 0 && MAP[posR.x][posR.y] == 0)
			{
				if (IsEnemy == false)
					return 3;
				else
					return 10;
			}
		}
		else
		{
			if (IsEnemy == false)
				return 5;
			else
				return 11;
		}	
		break;
	case 4:
		if (posL.x >= 0 && posL.x < 15 && posL.y >= 0 && posL.y < 15 && posR.x >= 0 && posR.x < 15 && posR.y >= 0 && posR.y < 15)
		{
			if (MAP[posL.x][posL.y] == 0 && MAP[posR.x][posR.y] == 0)
			{
				if (IsEnemy == false)
					return 2;
				else
					return 9;
			}
		}
		else
		{
			if (IsEnemy == false)
				return 3;
			else
				return 8;
		}
		break;
	case 5:
		if (IsEnemy == false)
			return 1;
		else
			return 7;
		break;
	default:
		if (IsEnemy == false)
			return 6;
		else
			return 12;
		break;
	}
//	return 0;
}
// 各种棋局类型的权值
int GoBang_ValueOfType(int type)
{
	switch (type)
	{
	case 1:		return 100000;   // 己方五子连线
 		break;                
	case 2:		return 10000;    // 己方活四
		break;
	case 3:		return 1000;     // 己方死四OR活三
		break;
	case 4:		return 100;      // 己方活二
		break;
	case 5:		return 90;       // 己方死三
		break;
	case 6:		return 10;       // 己方其他
		break;
	case 7:		return 50000;    // 敌方五子连线
		break;
	case 8:		return 2000;     // 敌方死四
		break;
	case 9:		return 3000;     // 敌方活四
		break;
	case 10:	return 500;      // 敌方活三
		break;
	case 11:	return 90;       // 敌方活二OR死三
		break;
	case 12:	return 20;       // 敌方其他
		break;
	default:	return 0;
		break;
	}
}


