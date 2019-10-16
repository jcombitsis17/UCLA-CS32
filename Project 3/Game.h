#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>

#include "Piece.h"

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();

    bool gameOver(Piece p);         // determine if the game will end when the next Piece starts falling
  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;

    int m_score;
    int m_rowsLeft;
};

void buildString(string& s);    // constructs appropriate strings for Score, Level, and Rows Left

#endif // GAME_INCLUDED
