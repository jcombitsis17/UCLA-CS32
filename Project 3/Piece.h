#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "UserInterface.h"
#include "Well.h"
#include <vector>
using namespace std;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

class Piece
{
public:
    Piece(Well& well, Screen& screen, PieceType type);
    ~Piece();
    Piece& operator=(const Piece& other);
    
    // used for moving/rotating a Piece
    void moveLeft();
    void moveRight();
    void moveDown();
    void deleteForMove() const;
    void displayPiece() const;
    void stopPiece();
    void rotate();
    
    // determine if a Piece can legally move within the Well
    bool legalMoveLeft() const;
    bool legalMoveRight() const;
    bool legalMoveDown() const;
    bool canRotate() const;
    
    void vaporBomb();
    void foamBomb(int x, int y);
    
    // accessor functions
    PieceType type() const
        { return m_type; }
    int x() const
        { return m_x; }
    int y() const
        { return m_y; }
    char getChar(int i, int j) const
        { return m_shape[i][j]; }
private:
    PieceType m_type;
    int m_x;    // current location of boundind box's (0,0) coordinate
    int m_y;    // current location of boundind box's (0,0) coordinate
    vector<vector<char>> m_shape;   // 2-D vector of the Piece's shape within its bounding box
    Well& m_well;
    Screen& m_screen;
    int m_orientation;  // either 0,1,2,3 based on current orientation
};

PieceType chooseRandomPieceType();

#endif // PIECE_INCLUDED
