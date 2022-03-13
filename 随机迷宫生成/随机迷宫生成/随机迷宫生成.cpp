//递归分割算法生成迷宫
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int a[12][12] = { 0 };
void mazeGenerator(char maze[12][12], int x1, int y1, int x2, int y2); //生成
//右手不为墙：右转直走
//右手为墙：前面不为墙：直走     前面为墙：掉头
bool righthand(char maze[12][12],int &direction, int &x, int &y); 
bool ahead(char maze[12][12],int &direction, int &x, int &y);
void rightforth(char maze[12][12], int &direction,int &x,int &y);
void turnright(int &direction);
void turnleft(int &direction);
void Traverse(char maze[12][12], int &x1, int &y1,int &direction);
int main()
{
	srand((unsigned)time(NULL));
	char maze[12][12];

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			maze[i][j] = '.';

	for (int i = 0; i < 12; i++)  //处理边界
	{
		maze[i][0] = '#';
		maze[0][i] = '#';
		maze[i][11] = '#';
		maze[11][i] = '#';
		a[i][0] = 1;
		a[0][i] = 1;
		a[i][11] = 1;
		a[11][i] = 1;
	}
	maze[1][0] = '.';//起始和结束位置 
	maze[10][11] = '.';
	
	int a = 1, b = 1, direction = 1;
	mazeGenerator(maze, 1, 1, 10, 10);
	Traverse(maze, a, b, direction);
	
	for (int i = 0; i < 12; i++) //打印迷宫
	{
		for (int j = 0; j < 12; j++)
		{
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
}
void mazeGenerator(char maze[12][12], int x1, int y1, int x2, int y2) //xy12为边界
{
	if (x2 - x1 < 2 || y2 - y1 < 2)  //递归结束条件
	{
		return;
	}

	int x0 = rand() % (x2 - x1 - 1) + x1 + 1;
	int y0 = rand() % (y2 - y1 - 1) + y1 + 1;  //随机选取分割起始点 
	for (int i = x1; i <= x2; i++)   //画分割墙
	{
		maze[i][y0] = '#';
		a[i][y0] = 1;
	}
	for (int i = y1; i <= y2; i++)
	{
		maze[x0][i] = '#';
		a[x0][i] = 1;
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
				while (a[px + 1][py] + a[px][py + 1] + a[px - 1][py] + a[px][py - 1] > 2)  //确保该点能打通一面墙 即周围最多两面墙
				{
					px = x1 + rand() % (x0 - x1);
				}break;
			case 1:
				while (a[px + 1][py] + a[px][py + 1] + a[px - 1][py] + a[px][py - 1] > 2)
				{
					px = x0 + rand() % (x2 - x0) + 1;
				}break;
			case 2:
				while (a[px + 1][py] + a[px][py + 1] + a[px - 1][py] + a[px][py - 1] > 2)
				{
					py = y1 + rand() % (y0 - y1);
				}break;
			case 3:
				while (a[px + 1][py] + a[px][py + 1] + a[px - 1][py] + a[px][py - 1] > 2)
				{
					py = y0 + rand() % (y2 - y0) + 1;
				}break;
			default:
				break;
			}
			maze[px][py] = '.';
			a[px][py] = 0;
		}
	}
}
bool righthand(char maze[12][12], int &direction, int &x, int &y)  //判断右手是否为墙壁
{
	switch (direction)  //1右 2下 3左 4上
	{
	case 1:if (maze[x+1][y] == '#')
		return true; 
		else return false; break;
	case 2:if (maze[x][y-1] == '#')
		return true; 
		   else return false; break;
	case 3:if (maze[x-1][y] == '#')
		return true; 
		   else return false; break;
	case 4:if (maze[x][y+1] == '#')
		return true; 
		   else return false; break;
	}
	
}
bool ahead(char maze[12][12], int &direction, int &x, int &y) //判断前面是否为墙壁
{
	switch (direction)
	{
	case 1:if (maze[x][y + 1] == '#')
		return true; 
		   else return false; break;
	case 2:if (maze[x+1][y] == '#')
		return true; 
		   else return false; break;
	case 3:if (maze[x][y - 1] == '#')
		return true;
		   else return false; break;
	case 4:if (maze[x-1][y] == '#')
		return true;
		   else return false; break;
	}
}
void rightforth(char maze[12][12], int &direction,int &x,int &y) //右手不为墙壁时，右转再直走
{
	switch (direction)
	{
	case 1:y += 1; maze[x][y] = 'x'; break;   //0在迷宫中作为寻路轨迹较为明显
	case 2:x += 1; maze[x][y] = 'x'; break;
	case 3:y -= 1; maze[x][y] = 'x'; break;
	case 4:x -= 1; maze[x][y] = 'x'; break;
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

void Traverse(char maze[12][12],int &x,int &y,int &direction)
{
	if (y == 0 || y == 11)
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
			Traverse(maze, x, y,direction);
		}
}