#ifndef Human_hpp
#define Human_hpp

#include <iostream>

#include "IPlayer.h"
#include "Board.h"

class Human : public IPlayer
{

public:
    Human(Board* board, Symbols symb);
    virtual ~Human() override;

    virtual int NewMove(Board* board) override;

private:
    int AskForMove();
};

#endif
