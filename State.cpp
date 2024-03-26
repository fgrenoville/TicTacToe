#include "State.h"

State::State(Board* board)
{
    Board* b = new Board(*board);
    this->board = b;
    weight = 999;
}

State::~State()
{
    /*
    std::cout << "Deleting state:\n";
    this->board->PrintBoard();
    */

    if (this->childrenNum > 1)
    {
        for (int i = 0; i < childrenNum; i++)
        {
            if (this->children[i] != nullptr)
            {
                this->childrenNum--;
                delete this->children[i];
                this->children[i] = nullptr;
            }
        }
    }
    delete board;
}
