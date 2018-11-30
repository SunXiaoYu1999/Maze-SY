#pragma once
#include <Windows.h>
// 鼠标数组，每个按钮的边界
typedef struct
{
	int x_l;
	int x_h;
	int y_l;
	int y_h;
}ARRAY;
typedef struct
{
	ARRAY array[225];
	int len;
}MOUSE_ARRAY;
// 颜色结构
typedef struct
{
	int R;
	int G;
	int B;
}COLOR;
// 坐标结构体
typedef struct 
{
	int x;
	int y;
}POS;


void GoBang_1();  // 模式1，人人对弈
void GoBang_GameInterFace(); // 游戏界面
void GoBang_DrawPiece(int x, int y, COLOR C); //画棋子 
POS GoBang_MouseReturn(MOUSE_ARRAY &MOU); // 鼠标操作
void GoBang_InitMouseArray(MOUSE_ARRAY &MOU); // 初始化鼠标范围
int GoBang_GameWin(int MAP[][15], POS pos, int user); // 判断当前位子有没有赢
int GoBang_GameEnd(const wchar_t *str);  //   游戏结束界面
int GoBang_Maze();// 游戏菜单
void GoBang(); // 菜单逻辑
void GoBang_2();
int GoBang_CalculateValue(int MAP[][15], POS temp, int user); // 计算temp点的权重
int GoBang_JudgeType(int MAP[][15],POS temp,int user,int Dir, bool IsEnemy);
int GoBang_ValueOfType(int type);
