// 迷宫.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"MG.h"
#include"InterFace.h"
#include<Windows.h>
#include<iostream>

int main()
{

	Maze A;
	A.Get_XY();
	A.Init_Lize();
	A.Create_Map();
	A.Find_Way_1();
	A.Find_Way_2();
//	A.Print_Map();
	system("pause");
    return 0;
}