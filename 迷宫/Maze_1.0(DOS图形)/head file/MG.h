#pragma once
#define START 5
#define END 6
#define WALL 0
#define WAY -1
#define FIND_FLAG 7
#define MAX_SIZE 5000
typedef struct D
{
	int Dx;
	int Dy;
	int dir;
} Data;
typedef struct 
{
	Data pos[MAX_SIZE];
	int top;
} STA;
typedef struct 
{
	Data data[MAX_SIZE];
	int prior;//队头指针
	int rear;//队尾指针
}QUE;
// 以上为求解时方块数据结构
typedef struct {
	int x;
	int y;
	int DIR[4];
	int dir; 
} m_node;       // 每个可走方块的数据结构

typedef struct {
	int top;
	m_node *St;
}stock;         // 栈数据结构

class Maze
{
private:
	int ** MAP; // 地图
	int line;   // 行数
	int col;    // 列数
public:
	Maze();
	~Maze();
	void Init_Lize();
	void Get_XY();
	void Print_Way(int x, int y);
	void Print_Space(int x, int y);
	void Create_Map();
	void Get_Dir(int *Dir);
	void Flag_Way(m_node temp, int **MAP);
	void Find_Way_1();
	void Find_Way_1(Data start,Data end);
	void Find_Way_2();
	void Find_Way_2(Data start, Data end);
	void Out();
	void Print_Data_1(int top);
	void Print_Map();
};
void Push_In(STA &p, Data e);
bool Is_Equal(Data A, Data B);