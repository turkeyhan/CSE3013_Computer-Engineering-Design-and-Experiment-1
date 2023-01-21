#include <bits/stdc++.h>
#include <windows.h>
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define WALL_H 4
#define WALL_W 5 
#define EMPTY 6
#define DOT 7
using namespace std;
int N, M;
int xx[4] = { 0, 2, 0, -2 };
int yy[4] = { 2, 0, -2, 0 };

bool InMap(int y, int x)
{
	return (y > 0 && y < 2*M) && (x > 0 && x < 2*N);
}

void InitializeMap(vector <vector<int>> &Map)
{
	for (int i = 0; i < 2*M + 1; i += 2)
	{
		for (int j = 0; j < 2*N + 1; j += 2)
		{
			Map[i][j] = DOT;
		}
	}

	for (int i = 0; i < 2*M + 1; i += 2)
	{
		for (int j = 1; j < 2*N + 1; j += 2)
		{
			Map[i][j] = WALL_W;
		}
	}

	for (int i = 1; i < 2*M + 1; i+=2)
	{
		for (int j = 0; j < 2*N +1; j += 2)
		{
			Map[i][j] = WALL_H;
		}
	}

	for (int i = 1; i < 2*M + 1; i += 2)
	{
		for (int j = 1; j < 2*N +1; j+=2)
		{
			Map[i][j] = EMPTY;
		}
	}
	return;
}

void input_maze()
{
	cin >> N;
	cin >> M;
	return;
}

void RandDirection(int Direction[])
{
	int tmp, ran;
	for (int i = 0; i < 3; i++)
	{
		ran = i + (rand() % (4 - i));
		tmp = Direction[i];
		Direction[i] = Direction[ran];
		Direction[ran] = tmp;
	}
	return;
}

void CreateMap(int y, int x, vector <vector<int>>& Map, vector <vector<int>> & Visited)
{
	int nx, ny;
	int Direction[4] = { UP, RIGHT, DOWN, LEFT };
	RandDirection(Direction);
	Visited[y / 2][x / 2] = 1;
	for (int i = 0; i < 4; i++)
	{
		nx = x + xx[Direction[i]];
		ny = y + yy[Direction[i]];

		if (InMap(ny, nx) && !Visited[ny / 2][nx / 2])
		{
			
			if (ny > y)
			{
				Map[y+1][x] = EMPTY;
				CreateMap(ny, nx, Map, Visited);
			}
			else if(ny < y)
			{
				Map[y - 1][x] = EMPTY;
				CreateMap(ny, nx, Map, Visited);
			}
			else if (nx > x)
			{
				Map[y][x + 1] = EMPTY;
				CreateMap(ny, nx, Map, Visited);
			}
			else if (nx < x)
			{
				Map[y][x - 1] = EMPTY;
				CreateMap(ny, nx, Map, Visited);
			}
		}
	}
	return;
}

COORD getRandStartPoint()
{
	COORD Pos;
	Pos.X = rand() % (2*N + 1);
	Pos.Y = rand() % (2*M + 1);
	if (Pos.X % 2 == 0)
	{
		if (!Pos.X)
		{
			Pos.X++;
		}
		else
		{
			Pos.X--;
		}
	}
	if (Pos.Y % 2 == 0)
	{
		if (!Pos.Y)
		{
			Pos.Y++;
		}
		else
		{
			Pos.Y--;
		}
	}
	return Pos;
}

void DrawMaze(vector <vector<int>> &Map)
{
	for (int i = 0; i < 2*M + 1; i++)
	{
		for (int j = 0; j < 2*N + 1; j++)
		{
			if (Map[i][j] == WALL_H)
			{
				cout << '|';
			}
			else if(Map[i][j] == WALL_W)
			{
				cout << '-';
			}
			else if (Map[i][j] == EMPTY)
			{
				cout << ' ';
			}
			else if (Map[i][j] == DOT)
			{
				cout << '+';
			}
		}
		cout << '\n';
	}
	return;
}
void OutputMaze(vector <vector<int>> &Map)
{
	FILE* fp;
	fopen_s(&fp, "Result.maz", "wt");
	if (fp == NULL)
	{
		cout << "Cannot write File\n";
		return;
	}
	for (int i = 0; i < 2 * M + 1; i++)
	{
		for (int j = 0; j < 2 * N + 1; j++)
		{
			if (Map[i][j] == WALL_H)
			{
				fprintf(fp, "|");
			}
			else if (Map[i][j] == WALL_W)
			{
				fprintf(fp, "-");
			}
			else if (Map[i][j] == EMPTY)
			{
				fprintf(fp, " ");
			}
			else if (Map[i][j] == DOT)
			{
				fprintf(fp, "+");
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return;
}
int main()
{
	input_maze();
	vector <vector<int>> Map(2 * M + 3, vector<int>(2 * N + 3));
	vector <vector<int>> Visited(M, vector<int>(N + 2));
	InitializeMap(Map);
	COORD StartPoint = getRandStartPoint();
	srand((unsigned int)time(NULL));

	CreateMap(StartPoint.Y, StartPoint.X, Map, Visited);

	DrawMaze(Map);
	

	OutputMaze(Map);
	return 0;
}