#include "Human.h"

Human::Human(Board* board, Symbols symb) : IPlayer(board, symb)
{
    std::cout << "Human joins the game playing with symbol: " << symb << std::endl;
}

Human::~Human()
{
    //std::cout << "Human destructor..." << std::endl;
}

int Human::NewMove(Board* board)
{
    //std::cout << "Human move..." << std::endl;

    return AskForMove();
}

int Human::AskForMove()
{
    int move;

    do
    {
        std::cout << "What's your move? (1-9) " << std::endl;
        std::cin >> move;

        if (move > 0 && move < 10)
        {
            move--;

            Symbols symb = board->GetValueAt(move);
            if (symb == Empty)
            {
                break;
            }
        }

        std::cout << "Move not allowed..." << std::endl;

    } while (true);

    return move;
}
