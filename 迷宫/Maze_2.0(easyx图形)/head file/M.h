#pragma once
const int  NUM_MAP = 400;
typedef struct box_1 
{
	int x;
	int y;
	int Dir[4];
	int dir;
}box_1;

typedef struct box_2 
{
	int x;
	int y;
	char dir;
}box_2;

typedef struct {
	int top;
	box_1 *St;
}stock;         // 栈数据结构

typedef struct {
	box_1 Qu[1600];
	int rear;
	int prior;
}queue;
int Maze_inti();
int Maze_Init_GameEnd(int Time = 0);
int Maze_Slove_Mouse();
int Maze_Input();
void Maze_Inti_Game();
void Maze_Print_Box(int x, int y);
void Maze_Print_Start_End(int x_1, int y_1, int x_2, int y_2);
void Maze_Game_Move(box_2 &A,char ch);
void Maze_Print_user(int x, int y);
void Maze_Print_Map(int xyz[][NUM_MAP]);
void Maze_Print_Clear(int x, int y); 
void Maze_Game();
void Maze_Game_GetStartEnd(box_2 &start, box_2 &end, int MAP[][NUM_MAP]);
void Maze_MakeMaze_Random(int MAP[][NUM_MAP], bool play);
void Maze_MakeMaze_Random_init(int MAP[][NUM_MAP]);
void Maze_Meum_Play();  
void Maze_MakeMaze_Random_GetStart(box_2 &start);
void Maze_MakeMaze_Random_GetDir(int Dir[4]);
void Maze_MakeMaze_Random_PrintWay(int x, int y);
void Maze_MakeMaze_Random_PrintClean(int x, int y);
void Maze_MakeMaze_Random_Fuzhi(box_1 &A, box_1 &B);
void Maze();
void Maze_DFS();
void Maze_BFS();
void Maze_DFS_Solve(int MAP[][NUM_MAP], bool play, bool CreateMaze);
void Maze_BFS_Solve(int MAP[][NUM_MAP], bool play, bool CreateMaze);
void Maze_Solve_GetStartEnd(box_1 &start, box_1 &end, int MAP[][NUM_MAP]);
bool Maze_Is_Way(int Map[][NUM_MAP], box_2 &re);
void Maze_DFS_Button();
void Maze_BFS_Button();
void Maze_MakeMaze_Random_1(int MAP[][NUM_MAP], bool play);
void Maze_MakeMaze_Random_1_FindWall(box_1 temp, int MAP[][NUM_MAP], box_1 *A,int &p);
bool Maze_MakeMaze_Random_1_FindWay(int q, box_1 *A,int MAP[][NUM_MAP],box_1 &tem);
void Maze_MakeMaze_Random_1_Dele(int q, box_1 *A,int &p);
void Maze_Caloulater_Num();
void Maze_Map_clear();
