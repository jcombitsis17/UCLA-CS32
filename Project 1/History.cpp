#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
: m_nRows(nRows), m_nCols(nCols)
{
    for (int r = 0; r < MAXROWS; r++)
        for (int c = 0; c < MAXCOLS; c++)
            m_grid[r][c] = 0;
}

bool History::record(int r, int c)
{
    if ( ! isInBounds(r, c))
        return false;
    m_grid[r][c] += 1;
    return true;
}

void History::display() const
{
    clearScreen();
    char historyGrid[MAXROWS][MAXCOLS];
    
    for (int r = 1; r <= m_nRows; r++)
    {
        for (int c = 1; c <= m_nCols; c++)
        {
            if (m_grid[r][c] == 0)
                historyGrid[r][c] = '.';
            else if (m_grid[r][c] >= 26)
                historyGrid[r][c] = 'Z';
            else
                historyGrid[r][c] = 'A' + m_grid[r][c] - 1;
        }
    }
    
    for (int r = 1; r <= m_nRows; r++)
    {
        for (int c = 1; c <= m_nCols; c++)
            cout << historyGrid[r][c];
        cout << endl;
    }
    
    cout << endl;
}

bool History::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_nRows  &&  c >= 1  &&  c <= m_nCols);
}
