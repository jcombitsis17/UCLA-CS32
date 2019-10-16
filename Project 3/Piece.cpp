#include "Piece.h"

const vector<vector<vector<char>>> pieces0 =    // vectors for orientation 0

{
    
    {   // I
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', '#'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // L
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {'#', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // J
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', '#'},
        {' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' '}
    },
    
    {   // T
        {' ', '#', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // O
        {'#', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // S
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // Z
        {' ', ' ', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // VAPOR
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // FOAM
        {' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // CRAZY
        {'#', ' ', ' ', '#'},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }
    
};

Piece::Piece(Well& well, Screen& screen, PieceType type)
: m_well(well), m_screen(screen), m_type(type), m_shape(pieces0[type]), m_orientation(0), m_x(4), m_y(0)
{
    // construct Piece in orientation 0, and location (4,0) (includes left wall of Well)
}

Piece::~Piece()
{}

Piece& Piece::operator=(const Piece& other) // acts like constructor, becuase only called to make brand-new Piece
{
    if (this == &other)
        return *this;
    m_well = other.m_well;
    m_screen = other.m_screen;
    m_type = other.m_type;
    m_x = 4;
    m_y = 0;
    m_shape = pieces0[m_type];
    m_orientation = other.m_orientation;
    
    return *this;
}

void Piece::moveLeft()
{
    deleteForMove();    // erases Piece from the Well
    m_x--;
    displayPiece();     // displays Piece at its new location in the Well
}

void Piece::moveRight()
{
    deleteForMove();    // erases Piece from the Well
    m_x++;
    displayPiece();     // displays Piece at its new location in the Well
}

void Piece::moveDown()
{
    deleteForMove();    // erases Piece from the Well
    m_y++;
    displayPiece();     // displays Piece at its new location in the Well
}

void Piece::deleteForMove() const   // sets each '#' in a Piece to ' ' so that it is no longer displayed in the Well
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_shape[i][j] == '#')
                m_well.addChar(m_x + j, m_y + i, ' ');
        }
    }
}

void Piece::displayPiece() const    // add each '#' in Piece's bounding box to the Well
{
    m_screen.gotoXY(m_x, m_y);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_shape[i][j] == '#')
            {
                m_screen.gotoXY(m_x + j, m_y + i);
                m_well.addChar(m_x + j, m_y + i, '#');
            }
        }
    }
    m_screen.refresh();
}

void Piece::stopPiece() // replace each '#' in the Piece with a '$'
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_shape[i][j] == '#')
            {
                m_shape[i][j] = '$';
                m_screen.gotoXY(m_x + j, m_y + i);
                m_well.addChar(m_x + j, m_y + i, '$');
            }
        }
    }
}

bool Piece::legalMoveLeft() const   // for each '#' in Piece, returns true as long as the character in the Well to its...
{                                   // ...left is not '@', '$', or '*'
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_shape[i][j] == '#')
                if (m_well.getValue((m_x + j) - 1, m_y + i) == '@' ||
                    m_well.getValue((m_x + j) - 1, m_y + i) == '$' ||
                    m_well.getValue((m_x + j) - 1, m_y + i) == '*')
                    return false;
        }
    }
    return true;
}

bool Piece::legalMoveRight() const  // for each '#' in Piece, returns true as long as the character in the Well to its...
{                                   // ...right is not '@', '$', or '*'
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_shape[i][j] == '#')
                if (m_well.getValue((m_x + j) + 1, m_y + i) == '@' ||
                    m_well.getValue((m_x + j) + 1, m_y + i) == '$' ||
                    m_well.getValue((m_x + j) + 1, m_y + i) == '*')
                    return false;
        }
    }
    return true;
}

bool Piece::legalMoveDown() const   // for each '#' in Piece, returns true as long as the character in the Well...
{                                   // ...below it is not '@', '$', or '*'
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_shape[i][j] == '#')
                if (m_well.getValue(m_x + j, (m_y + i) + 1) == '@' ||
                    m_well.getValue(m_x + j, (m_y + i) + 1) == '$' ||
                    m_well.getValue(m_x + j, (m_y + i) + 1) == '*')
                    return false;
        }
    }
    return true;
}

void Piece::vaporBomb() // for each '#' in VaporBomb, set each char in the Well to ' ' for up to 2 positions...
{                       // ...above/below it
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (m_shape[i][j] == '#')
                for (int k = i - 2; k <= i + 2; k++)
                    if (m_well.getValue(m_x + j, m_y + k) == '$' ||
                        m_well.getValue(m_x + j, m_y + k) == '*')
                    {
                        m_well.addChar(m_x + j, m_y + k, ' ');
                    }
    deleteForMove();    // also delete the VaporBomb from the Well, since upon detonation it vaporizes itself
}

void Piece::foamBomb(int x, int y)  // recursive foamBomb algorithm
{
    if (abs((m_x + 1) - x) > 2 || abs((m_y + 1) - y) > 2 ||     // outside 5x5 bounding block
        m_well.getValue(x, y) == '@' ||                         // hit wall of Well
        m_well.getValue(x, y) == '$' ||                         // slot already occupied
        m_well.getValue(x, y) == '*')                           // slot already visited (or already occupied)
        return;
    
    if (m_well.getValue(x, y) == ' ' || m_well.getValue(x, y) == '#')   // change all valid locations in Well to '*'
        m_well.addChar(x, y, '*');
    
    foamBomb(x + 1, y); // check adjacent right
    foamBomb(x - 1, y); // check adjacent left
    foamBomb(x, y + 1); // check adjacent down
    foamBomb(x, y - 1); // check adjacent up
}

const vector<vector<vector<char>>> pieces1 =    // vectors for orientation 1

{
    
    {   // I
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '}
    },
    
    {   // L
        {' ', '#', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // J
        {' ', ' ', ' ', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', '#', '#', ' '}
    },
    
    {   // T
        {' ', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // O
        {'#', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // S
        {' ', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // Z
        {' ', ' ', '#', ' '},
        {' ', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // VAPOR
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // FOAM
        {' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // CRAZY
        {' ', ' ', ' ', '#'},
        {' ', ' ', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', ' ', '#'}
    }
    
};

const vector<vector<vector<char>>> pieces2 =    // vectors for orientation 2

{
    
    {   // I
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', '#'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // L
        {' ', ' ', ' ', ' '},
        {' ', ' ', '#', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // J
        {' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', '#', '#'},
        {' ', ' ', ' ', ' '}
    },
    
    {   // T
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // O
        {'#', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // S
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // Z
        {' ', ' ', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // VAPOR
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // FOAM
        {' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // CRAZY
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {'#', ' ', ' ', '#'}
    }
    
};

const vector<vector<vector<char>>> pieces3 =    // vectors for orientation 3

{
    
    {   // I
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '}
    },
    
    {   // L
        {' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', '#', ' '}
    },
    
    {   // J
        {' ', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // T
        {' ', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // O
        {'#', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // S
        {' ', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // Z
        {' ', ' ', '#', ' '},
        {' ', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // VAPOR
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // FOAM
        {' ', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    
    {   // CRAZY
        {'#', ' ', ' ', ' '},
        {' ', '#', ' ', ' '},
        {' ', '#', ' ', ' '},
        {'#', ' ', ' ', ' '}
    }
    
};

void Piece::rotate()    // roate the Piece clockwise
{
    deleteForMove();    // erase Piece from the Well
    
    if (m_orientation == 3) // increment orientation integer
        m_orientation = 0;
    else
        m_orientation++;
    
    if (m_orientation == 0) // assign new 2-D vector to Piece
        m_shape = pieces0[m_type];
    else if (m_orientation == 1)
        m_shape = pieces1[m_type];
    else if (m_orientation == 2)
        m_shape = pieces2[m_type];
    else
        m_shape = pieces3[m_type];
    
    displayPiece(); // display new Piece orientation in the Well
}

bool Piece::canRotate() const
{
    vector<vector<char>> test;  // create a temporary 2-D vector to simulate the Piece being rotated
    if (m_orientation == 0)
        test = pieces1[m_type];
    else if (m_orientation == 1)
        test = pieces2[m_type];
    else if (m_orientation == 2)
        test = pieces3[m_type];
    else
        test = pieces0[m_type];
    
    for (int i = 0; i < 4; i++) // return false if the simulated rotated Piece overlaps with the Well or another Piece
        for (int j = 0; j < 4; j++)
            if (test[i][j] == '#')
                if (m_well.getValue(m_x + j, m_y + i) == '$' ||
                    m_well.getValue(m_x + j, m_y + i) == '*' ||
                    m_well.getValue(m_x + j, m_y + i) == '@')
                    return false;
    
    return true;
}
