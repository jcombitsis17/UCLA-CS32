#include "Well.h"

Well::Well(Screen& screen)
: m_screen(screen)
{
    for (int i = 0; i < 12; i++)        // initialize everything blank
        for (int j = 0; j < 19; j++)
            m_wellDisplay[i][j] = ' ';
    
    for (int i = 0; i < 18; i++)        // initialize left/right borders
    {
        m_wellDisplay[0][i] = '@';
        m_wellDisplay[11][i] = '@';
    }
    
    for (int i = 0; i < 12; i++)        // initialize bottom of Well
    {
        m_wellDisplay[i][18] = '@';
    }
}

Well& Well::operator=(const Well& other)
{
    m_screen = other.m_screen;
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 19; j++)
            m_wellDisplay[i][j] = other.m_wellDisplay[i][j];
    return *this;
}

void Well::display(Screen& screen, int x, int y)    // display the entire Well
{
    screen.gotoXY(x, y);    // called in Game.cpp with (x = WELL_X = 0), (y = WELL_Y = 0)
    
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            screen.gotoXY(x + i, y + j);
            screen.printChar(m_wellDisplay[i][j]);  // print contents of Well
        }
    }
    screen.refresh();
}

void Well::addChar(int x, int y, char c)    // add/display a specific char at a specific position in the Well
{
    m_wellDisplay[x][y] = c;
    m_screen.gotoXY(x, y);
    m_screen.printChar(c);
}

char Well::getValue(int x, int y) const     // returns the char at position (x,y) in the Well
{
    return m_wellDisplay[x][y];
}

int Well::checkRow(int row) const   // determine if a row is completely filled
{
    for (int i = 1; i <= 10; i++)
    {
        if (m_wellDisplay[i][row] == '$' || m_wellDisplay[i][row] == '*')
        {
            if (i == 10)
                return row; // if row consists entirely of '$' and/or '*', return which row was checked
            continue;
        } else
            break;
    }
    return -1;  // if row not filled, return -1
}

void Well::vaporizeRow(int row) // vaporize a certain row in the Well
{
    for (int i = 1; i <= 10; i++)       // vaporize selected row
        m_wellDisplay[i][row] = ' ';
    for (int y = row - 1; y >= 0; y--)  // shift all above rows down by 1
        for (int x = 1; x <= 10; x++)
            m_wellDisplay[x][y + 1] = m_wellDisplay[x][y];
}

void Well::clearWell()  // set all char values within the Well to ' '
{
    for (int i = 1; i <= 10; i++)
        for (int j = 0; j < 18; j++)
            m_wellDisplay[i][j] = ' ';
}
