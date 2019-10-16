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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    Coord start(sr, sc);
    Coord   end(er, ec);
    
    coordQueue.push(start);
    maze[sr][sc] = 'O';     // initialize start point
    
    while (!coordQueue.empty())
    {
        Coord curr = coordQueue.front();
        coordQueue.pop();
        if (curr.r() == end.r() && curr.c() == end.c())
            return true;
        
        Coord north(curr.r() - 1, curr.c());
        Coord  west(curr.r(), curr.c() - 1);
        Coord south(curr.r() + 1, curr.c());
        Coord  east(curr.r(), curr.c() + 1);
        if (maze[north.r()][north.c()] == '.')
        {
            coordQueue.push(north);
            maze[north.r()][north.c()] = 'O';
        }
        if (maze[west.r()][west.c()] == '.')
        {
            coordQueue.push(west);
            maze[west.r()][west.c()] = 'O';
        }
        if (maze[south.r()][south.c()] == '.')
        {
            coordQueue.push(south);
            maze[south.r()][south.c()] = 'O';
        }
        if (maze[east.r()][east.c()] == '.')
        {
            coordQueue.push(east);
            maze[east.r()][east.c()] = 'O';
        }
    }
    return false;
}






#include <iostream>
#include <cassert>
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    //assert(pathExists(maze, 6,5, 6,5));   // test these one at a time (changes maze)
    assert(pathExists(maze, 6,5, 1,8));
    //assert(pathExists(maze, 6,5, 7,1));
    //assert(pathExists(maze, 6,5, 1,1));
    //assert(!pathExists(maze, 6,5, 8,8));
    //assert(!pathExists(maze, 6,5, 8,6));
    //assert(!pathExists(maze, 6,5, 1,0));
    
    cerr << "All tests passed!" << endl;
}
