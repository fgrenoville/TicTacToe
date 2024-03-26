#ifndef Match_hpp
#define Match_hpp

#include <iostream>

#include "Board.h"
#include "IPlayer.h"
#include "Symbols.h"

class Match
{

public:
    Match(Board* board, IPlayer* p1, IPlayer* p2);
    void Play();


private:
    Board* board;
    IPlayer* p1;
    IPlayer* p2;

    IPlayer* turnToMove;

    Symbols HasSomebodyWon();

};
#endif