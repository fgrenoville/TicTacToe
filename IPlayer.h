#ifndef Player_hpp
#define Player_hpp

#include <iostream>

#include "Board.h"

class IPlayer
{

public:
    IPlayer(Board* board, Symbols symb);
    virtual ~IPlayer();
    virtual int NewMove(Board* board) = 0;
    Symbols GetSymbol();

protected:
    Board* board;
    Symbols symb;

};

#endif
