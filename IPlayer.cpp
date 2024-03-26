#include "IPlayer.h"

IPlayer::IPlayer(Board* board, Symbols symb)
{
    //std::cout << "IPlayer constructor..." << std::endl;

    this->board = board;
    this->symb = symb;
}

IPlayer::~IPlayer()
{
    //std::cout << "IPlayer destructor..." << std::endl;
}

Symbols IPlayer::GetSymbol()
{
    return symb;
}
