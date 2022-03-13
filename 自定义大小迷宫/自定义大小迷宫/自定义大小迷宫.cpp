#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int row, col;
void mazeGenerator(int **maze, int x1, int y1, int x2, int y2);
bool righthand(int **maze, int &direction, int &x, int &y);
bool ahead(int **maze, int &direction, int &x, int &y);
void rightforth(int **maze, int &direction, int &x, int &y);
void turnright(int &direction);
void turnleft(int &direction);
void Traverse(int **maze, int &x1, int &y1, int &direction);
int main()
{
	cin >> row >> col;
	
	int **maze = new int *[row];
	for (int i = 0; i < row; i++)//定义
		maze[i] = new int[col];
	
	for (int i = 0; i < row; i++)//初始化
		for (int j = 0; j < col; j++)
			maze[i][j] = 0;
	for (int i = 0; i < row; i++)  //处理边界
	{
		maze[i][0] = 1;
		maze[i][col - 1] = 1;
	}
	for (int i = 0; i < col; i++)  //处理边界
	{
		maze[0][i] = 1;
		maze[row-1][i] = 1;
	}
	maze[1][0] = 0;//起始和结束位置 
	maze[row-2][col-1] = 0;
	
	int a = 1, b = 1, direction = 1;
	mazeGenerator(maze, 1, 1, row-2, col-2);
	Traverse(maze, a, b, direction);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			switch (maze[i][j])
			{
			case 0:cout << "."<<" "; break;
			case 1:cout << "#"<<" "; break;
			case 2:cout << "X" << " "; break;
			}
		}
		cout << endl;
	}
}
void mazeGenerator(int **maze, int x1, int y1, int x2, int y2)
{
	if (x2 - x1 < 2 || y2 - y1 < 2)  //递归结束条件
	{
		return;
	}

	int x0 = rand() % (x2 - x1 - 1) + x1 + 1;
	int y0 = rand() % (y2 - y1 - 1) + y1 + 1;  //随机选取分割起始点 
	for (int i = x1; i <= x2; i++)   //画分割墙
	{
		maze[i][y0] = 1;
	}
	for (int i = y1; i <= y2; i++)
	{
		maze[x0][i] = 1;
	}
	mazeGenerator(maze, x1, y1, x0 - 1, y0 - 1);
	mazeGenerator(maze, x0 + 1, y0 + 1, x2, y2);
	mazeGenerator(maze, x1, y0 + 1, x0 - 1, y2);
	mazeGenerator(maze, x0 + 1, y1, x2, y0 - 1);
	int random[4] = { 1 ,1,1,1 };
	int r = rand() % 4;//随机选取要开洞三面墙
	random[r] = 0;
	int px, py;  //随机选取开口点
	for (int i = 0; i < 4; i++)
	{

		if (random[i] == 1)
		{
			px = x0;
			py = y0;
			switch (i)  //0上 1下 2左 3右
			{
			case 0:
				while (maze[px + 1][py] + maze[px][py + 1] + maze[px - 1][py] + maze[px][py - 1] > 2)  //确保该点能打通一面墙 即周围最多两面墙
				{
					px = x1 + rand() % (x0 - x1);
				}break;
			case 1:
				while (maze[px + 1][py] + maze[px][py + 1] + maze[px - 1][py] + maze[px][py - 1] > 2)
				{
					px = x0 + rand() % (x2 - x0) + 1;
				}break;
			case 2:
				while (maze[px + 1][py] + maze[px][py + 1] + maze[px - 1][py] + maze[px][py - 1] > 2)
				{
					py = y1 + rand() % (y0 - y1);
				}break;
			case 3:
				while (maze[px + 1][py] + maze[px][py + 1] + maze[px - 1][py] + maze[px][py - 1] > 2)
				{
					py = y0 + rand() % (y2 - y0) + 1;
				}break;
			default:
				break;
			}
			maze[px][py] = 0;
		}
	}
}
bool righthand(int **maze, int &direction, int &x, int &y)  //判断右手是否为墙壁
{
	switch (direction)  //1右 2下 3左 4上
	{
	case 1:if (maze[x + 1][y] == 1)
		return true;
		   else return false; break;
	case 2:if (maze[x][y - 1] == 1)
		return true;
		   else return false; break;
	case 3:if (maze[x - 1][y] == 1)
		return true;
		   else return false; break;
	case 4:if (maze[x][y + 1] == 1)
		return true;
		   else return false; break;
	}

}
bool ahead(int **maze, int &direction, int &x, int &y) //判断前面是否为墙壁
{
	switch (direction)
	{
	case 1:if (maze[x][y + 1] == 1)
		return true;
		   else return false; break;
	case 2:if (maze[x + 1][y] == 1)
		return true;
		   else return false; break;
	case 3:if (maze[x][y - 1] == 1)
		return true;
		   else return false; break;
	case 4:if (maze[x - 1][y] == 1)
		return true;
		   else return false; break;
	}
}
void rightforth(int **maze, int &direction, int &x, int &y) //右手不为墙壁时，右转再直走
{
	switch (direction)
	{
	case 1:y += 1; maze[x][y] = 2; break;   //0在迷宫中作为寻路轨迹较为明显
	case 2:x += 1; maze[x][y] = 2; break;
	case 3:y -= 1; maze[x][y] = 2; break;
	case 4:x -= 1; maze[x][y] = 2; break;
	default:break;
	}
}
void turnright(int &direction)
{
	switch (direction)
	{
	case 1:direction = 2; break;
	case 2:direction = 3; break;
	case 3:direction = 4; break;
	case 4:direction = 1; break;
	default:break;
	}
}
void turnleft(int &direction)
{
	switch (direction)
	{
	case 1:direction = 4; break;
	case 2:direction = 1; break;
	case 3:direction = 2; break;
	case 4:direction = 3; break;
	default:break;
	}
}
void Traverse(int **maze, int &x, int &y, int &direction)
{
	if (y == 0 || y == col-1)
	{
		if (y == 0)
		{
			cout << "该迷宫没有通路" << endl;
		}
		return;
	}
	else
		if (righthand(maze, direction, x, y)) //右为墙
		{
			if (ahead(maze, direction, x, y)) //前为墙
			{
				turnleft(direction);
				turnleft(direction);
				Traverse(maze, x, y, direction);
			}
			else
			{
				rightforth(maze, direction, x, y);
				Traverse(maze, x, y, direction);
			}
		}
		else //右不为墙
		{
			turnright(direction);
			rightforth(maze, direction, x, y);
			Traverse(maze, x, y, direction);
		}
}