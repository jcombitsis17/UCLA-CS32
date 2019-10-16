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
    if (sr == er && sc == ec)   // start = end
        return true;
    maze[sr][sc] = 'O';         // mark start as visited
    
    if (maze[sr - 1][sc] == '.')    // check north
        if (pathExists(maze, sr - 1, sc, er, ec))
            return true;
    if (maze[sr][sc - 1] == '.')    // check west
        if (pathExists(maze, sr, sc - 1, er, ec))
            return true;
    if (maze[sr + 1][sc] == '.')    // check south
        if(pathExists(maze, sr + 1, sc, er, ec))
            return true;
    if (maze[sr][sc + 1] == '.')    // check east
        if(pathExists(maze, sr, sc + 1, er, ec))
            return true;
    
    return false;
}

// -------- vvv DELETE vvv ---------

/*#include <iostream>
#include <cassert>
using namespace std;
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
    
    // *** test these one at a time (changes maze) ***
    
    //assert(pathExists(maze, 6,5, 6,5));
    assert(pathExists(maze, 6,5, 1,8));
    //assert(pathExists(maze, 6,5, 7,1));
    //assert(pathExists(maze, 6,5, 1,1));
    //assert(!pathExists(maze, 6,5, 8,8));
    //assert(!pathExists(maze, 6,5, 8,6));
    //assert(!pathExists(maze, 6,5, 1,0));
    
    cerr << "All tests passed!" << endl;
}*/
