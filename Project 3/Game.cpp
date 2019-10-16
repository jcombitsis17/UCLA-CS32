#include "Game.h"
#include <string>
#include <algorithm>
using namespace std;
#include <cmath>    // pow()

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_rowsLeft(5), m_score(0), m_well(m_screen)
{
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    string score = to_string(m_score);  // prints the current score in the appropriate location
    buildString(score);
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score:     ");
    m_screen.printString(score);
    
    string rowsLeft = to_string(m_rowsLeft);    // prints the current number of rows left in the appropriate location
    buildString(rowsLeft);
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left: ");
    m_screen.printString(rowsLeft);
    
    string level = to_string(m_level);  // prints the current level in the appropriate location
    buildString(level);
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:     ");
    m_screen.printString(level);
}

bool Game::playOneLevel()
{
    m_rowsLeft = 5 * m_level;   // initializes number of rows left
    m_well.clearWell();
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();    // displays initial score, rows left, and level
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next Piece:");
    
    Piece currPiece(m_well, m_screen, chooseRandomPieceType()); // first Piece of level
    
    Timer fall;
    PieceType nextPiece;
    int rowFull, howMany;
    bool samePiece = false; // determines if a new Piece has just started falling or not
    
    while (true)
    {
        fall.start();
        
        if (!samePiece) // if new Piece, generate a random nextPiece and display it
        {
            nextPiece = chooseRandomPieceType();            // determine type of next Piece
            Piece displayNext(m_well, m_screen, nextPiece); // create Piece just for display
            for (int i = 0; i < 4; i++)                     // display next Piece
            {
                for (int j = 0; j < 4; j++)
                {
                    m_screen.gotoXY(NEXT_PIECE_X + j, NEXT_PIECE_Y + i);
                    m_screen.printChar(displayNext.getChar(i, j));
                }
            }
            samePiece = true;
            m_screen.refresh();
        }
        
        currPiece.displayPiece();
        howMany = 0;
        
        TIMER:
        while (fall.elapsed() < max(1000 - (100 * (m_level - 1)), 100))
        {
            char key;
            if (getCharIfAny(key))  // check if keystroke
            {
                switch (key)
                {
                    case ARROW_LEFT:
                        if (currPiece.type() == PIECE_CRAZY)    // if CrazyPiece, move in opposite direction
                        {
                            if (!currPiece.legalMoveRight())
                                break;
                            currPiece.moveRight();
                        } else
                        {
                            if (!currPiece.legalMoveLeft())     // check legal move left
                                break;
                            currPiece.moveLeft();               // move Piece left
                        }
                        m_well.display(m_screen, WELL_X, WELL_Y);
                        break;
                    case ARROW_RIGHT:
                        if (currPiece.type() == PIECE_CRAZY)    // if CrazyPiece, move in opposite direction
                        {
                            if (!currPiece.legalMoveLeft())
                                break;
                            currPiece.moveLeft();
                        } else
                        {
                            if (!currPiece.legalMoveRight())    // check legal move right
                                break;
                            currPiece.moveRight();              // move Piece right
                        }
                        m_well.display(m_screen, WELL_X, WELL_Y);
                        break;
                    case ARROW_DOWN:
                        if (!currPiece.legalMoveDown())         // if Piece cannot move down, end the current "turn"
                            goto ENDTURN;                       // (i.e. set current Piece to rest and drop a new one)
                        
                        currPiece.moveDown();
                        m_well.display(m_screen, WELL_X, WELL_Y);
                        fall.start();
                        goto TIMER;                             // if the Piece is manually moved down, restart Timer
                        break;
                    case ARROW_UP:
                        if (currPiece.canRotate())  // check if the Piece can rotate based on its...
                        {                           // ...position in the Well
                            currPiece.rotate();     // rotate the Piece clockwise
                            m_well.display(m_screen, WELL_X, WELL_Y);
                        }
                        break;
                    case ' ':   // spacebar
                    {
                        while (currPiece.legalMoveDown())       // move Piece down until it cannot legally fall anymore
                            currPiece.moveDown();
                        m_well.display(m_screen, WELL_X, WELL_Y);   // only display the Well after, so that...
                                                                    // ...no sliding animation is seen
                        goto ENDTURN;   // end the current "turn"
                        break;
                    }
                    case 'Q': case 'q': // to quit, send a "Game Over" signal
                        return false;
                    default:    // do nothing for any other keys
                        break;
                }   // end switch
            }       // end if
        }           // end while (fall.elapsed) piece reached bottom
        
        if (currPiece.legalMoveDown())  // if the Timer ends, move the Piece down
        {
            currPiece.moveDown();
            m_well.display(m_screen, WELL_X, WELL_Y);
        }
        else
        {
        ENDTURN:    // end the current "turn"
            if (currPiece.type() == PIECE_FOAM) // activate any special actions (foamBomb/vaporBomb)
            {
                currPiece.foamBomb(currPiece.x() + 1, currPiece.y() + 1);
                m_well.display(m_screen, WELL_X, WELL_Y);
            }
            
            if (currPiece.type() == PIECE_VAPOR)
            {
                currPiece.vaporBomb();
                m_well.display(m_screen, WELL_X, WELL_Y);
            } else
            {
                if (currPiece.type() != PIECE_FOAM)
                    currPiece.stopPiece();  // turn '#' of Piece into '$'
                
                for (int i = 0; i < 18; i++)    // check for rows to vaporize
                {
                    rowFull = m_well.checkRow(i);
                    if (rowFull != -1)
                    {
                        m_well.vaporizeRow(rowFull);
                        howMany++;
                    }
                }
                m_rowsLeft -= howMany;  // update Rows Left value
                if (m_rowsLeft < 0)
                    m_rowsLeft = 0;
                if (howMany > 0)
                    m_score += ( pow(2, howMany - 1) * 100 );   // update Score value
                
                displayStatus();    // display updated Game status
                if (m_rowsLeft == 0)
                    return true;    // if rowsLeft = 0, level has been completed
                
                m_well.display(m_screen, WELL_X, WELL_Y);
            }
            
            currPiece = Piece(m_well, m_screen, nextPiece); // construct next Piece to fall
            samePiece = false;
        }

        if (gameOver(currPiece))
            break;
        
    } // this means Game Over
    
    return false;
}

bool Game::gameOver(Piece p)    // returns true for Game Over if, when the a new Piece is initially dropped at the...
{                               // ...top of the Well, its '#' chars overlap with an existing '$' or '*' in the Well
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (p.getChar(i, j) == '#')
            {
                if (m_well.getValue(p.x() + j, p.y() + i) == '$' ||
                    m_well.getValue(p.x() + j, p.y() + i) == '*')
                {
                    p.displayPiece();
                    return true;
                }
            }
        }
    }
    return false;
}

void buildString(string& s)   // build the right-justified, 7 character wide strings for...
{                             // ...the score, level, and rows left
    while (s.size() != 7)
        s.insert(0, " ");
}
