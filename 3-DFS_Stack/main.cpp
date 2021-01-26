#include<iostream>
#include<ctime>
#include<cstdlib>
#include"dfsStack.h"
using namespace std;
bool dfs(char map[7][7], Stack<point>& sp);// non-recrusion DFS by using stack
void gener_bar(char map[7][7]);//generate random barriers
void DisplayMaze(const char map[7][7]);
void DisplayRoute(Stack<point>& sp);
int main()
{
	Stack<point> sp;
	char maze[7][7];
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			maze[i][j] = '#';//initialization of the maze, availabe dots are '#'
		}
	}
	gener_bar(maze);
	if (dfs(maze,sp))
	{
		maze[0][0] = '*';
		DisplayMaze(maze);
		DisplayRoute(sp);
		cout << endl;
	}
	else
	{
		DisplayMaze(maze);
		cerr << "无有效路径！\n";
	}
	system("pause");
	return 0;
}
void gener_bar(char map[7][7])//generate 7 random barriers
{
	int ct = 0,x,y;
	srand(unsigned(time(NULL)));
	while (ct < 7)
	{
		x = rand() % 7;
		y = rand() % 7;
		if (map[x][y] == '#'&&(x!=0||y!=0)&&(x!=6||y!=6))
		{
			map[x][y] = '0';//barriers are '0'
			ct++;
		}
	}
}
void DisplayMaze(const char map[7][7])
{
	cout.setf(ios::left);
	cout << "迷宫地图：\n";
	cout << '\t';
	for (int i = 0; i < 7; i++)
	{
		cout << i << "列\t";
	}
	cout << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << i << "行\t";
		for (int j = 0; j < 7; j++)
		{
			cout << map[i][j] << '\t';
		}
		cout << endl;
	}
	return;
}// Display the maze on the screen
void DisplayRoute(Stack<point>& sp)
{
	int i = 0;
	int sz = sp.size();
	point* pp = new point[sz];
	cout << "迷宫路径：\n";
	while (!sp.isEmpty())
	{
		pp[i] = sp.top();
		i++;
		sp.pop();
	}
	cout.setf(ios::left);
	for (int j = i-1; j >= 0; j--)//reverse output,since it is a stack
	{
		printf("(%d, %d)", pp[j].x, pp[j].y);
		if ((i - 1 - j) % 4 == 3)
			cout << endl;
		if (j != 0)
			cout << "--->";
	}// 4 points in one line
	delete[]pp;
	return;
}//Display the route
bool dfs(char map[7][7], Stack<point>& sp)
{
	int visited[7][7];
	point temp;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			visited[i][j] = 0;
	}//array 'visited' marks the point that has been visited(marked '1')
	visited[0][0] = 1;// the start can't be visited again
	temp.x = 0;
	temp.y = 0;
	sp.push(temp);//push the start point into the stack
	while (!sp.isEmpty()&&(sp.top().x!=6||sp.top().y!=6))
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			temp.x = sp.top().x + MOVX[i];
			temp.y = sp.top().y + MOVY[i];// try different point
			if (temp.x >= 0 && temp.x < 7 && temp.y >= 0 && temp.y < 7)// if in the maze
			{
				if (map[temp.x][temp.y] == '#' && visited[temp.x][temp.y] == 0)// if available
				{
					visited[temp.x][temp.y] = 1;//visited
					map[temp.x][temp.y] = '*';// arrived dots are '*'
					sp.push(temp);// the new start(recrusion)
					break;//end the loop
				}
			}
		}
		if (i == 4)// no matching position
		{
			map[sp.top().x][sp.top().y] = '#';//not available, marked '#'
			sp.pop();// delete it from the stack
		}
	}
	if (sp.top().x == 6 && sp.top().y == 6)//to the finish
	{
		return true;
	}
	else
	{
		return false;
	}
}