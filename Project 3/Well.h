#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include "UserInterface.h"

class Well
{
  public:
    Well(Screen& screen);
    Well& operator=(const Well& other);
    
    // used to edit specific contents of the Well and display them to the Screen
    void display(Screen& screen, int x, int y);
    void addChar(int x, int y, char c);
    
    // accessor function(s)
    char getValue(int x, int y) const;
    
    // used at the end of a "turn" to vaporize rows that are filled up (if any)
    int checkRow(int row) const;
    void vaporizeRow(int row);
    
    // used at the beginning of each level
    void clearWell();
private:
    char m_wellDisplay[12][19];
    Screen& m_screen;
};

#endif // WELL_INCLUDED
