#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	queue<Coord> coordQueue;
	Coord start(sr, sc);
	coordQueue.push(start);
	maze[sr][sc] = '#';

	while (!coordQueue.empty())
	{
		Coord a = coordQueue.front();
		coordQueue.pop();
		if (a.r() == er && a.c() == ec)
			return true;
		if (maze[a.r()][a.c() + 1] == '.') //east
		{
			maze[a.r()][a.c() + 1] = '#';
			coordQueue.push(Coord(a.r(), a.c() + 1));
		}
		if (maze[a.r() + 1][a.c()] == '.') //south
		{
			maze[a.r() + 1][a.c()] = '#';
			coordQueue.push(Coord(a.r() + 1, a.c()));
		}
		if (maze[a.r()][a.c() - 1] == '.') //west
		{
			maze[a.r()][a.c() - 1] = '#';
			coordQueue.push(Coord(a.r(), a.c() - 1));
		}
		if (maze[a.r() - 1][a.c()] == '.') //north
		{
			maze[a.r() - 1][a.c()] = '#';
			coordQueue.push(Coord(a.r() - 1, a.c()));
		}
	}
	return false;
}

/*
int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X..XX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
*/