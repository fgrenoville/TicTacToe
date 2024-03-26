#include "Match.h"

Match::Match(Board* board, IPlayer* p1, IPlayer* p2)
{
    this->board = board;
    this->p1 = p1;
    this->p2 = p2;
}

void Match::Play()
{
    srand(time(NULL));
    turnToMove = (rand() % 10) < 5 ? p2 : p1;

    for (int i = 0; i < 9; i++)
    {
        board->PrintBoard();

        board->SetValueAt(turnToMove->GetSymbol(), turnToMove->NewMove(board));

        Symbols symb = HasSomebodyWon();
        if (symb == X || symb == O)
        {
            board->PrintBoard();

            std::cout << symb << " Wins the match." << std::endl;

            return;
        }

        turnToMove = turnToMove == p1 ? p2 : p1;
    }

    std::cout << "It's a draw!" << std::endl;
}

Symbols Match::HasSomebodyWon()
{
    if (board->GetValueAt(0) == X &&
        board->GetValueAt(1) == X &&
        board->GetValueAt(2) == X)
    {
        return X;
    }

    if (board->GetValueAt(3) == X &&
        board->GetValueAt(4) == X &&
        board->GetValueAt(5) == X)
    {
        return X;
    }

    if (board->GetValueAt(6) == X &&
        board->GetValueAt(7) == X &&
        board->GetValueAt(8) == X)
    {
        return X;
    }

    if (board->GetValueAt(0) == X &&
        board->GetValueAt(3) == X &&
        board->GetValueAt(6) == X)
    {
        return X;
    }

    if (board->GetValueAt(1) == X &&
        board->GetValueAt(4) == X &&
        board->GetValueAt(7) == X)
    {
        return X;
    }

    if (board->GetValueAt(2) == X &&
        board->GetValueAt(5) == X &&
        board->GetValueAt(8) == X)
    {
        return X;
    }

    if (board->GetValueAt(0) == X &&
        board->GetValueAt(4) == X &&
        board->GetValueAt(8) == X)
    {
        return X;
    }

    if (board->GetValueAt(2) == X &&
        board->GetValueAt(4) == X &&
        board->GetValueAt(6) == X)
    {
        return X;
    }

    if (board->GetValueAt(0) == O &&
        board->GetValueAt(1) == O &&
        board->GetValueAt(2) == O)
    {
        return O;
    }

    if (board->GetValueAt(3) == O &&
        board->GetValueAt(4) == O &&
        board->GetValueAt(5) == O)
    {
        return O;
    }

    if (board->GetValueAt(6) == O &&
        board->GetValueAt(7) == O &&
        board->GetValueAt(8) == O)
    {
        return O;
    }

    if (board->GetValueAt(0) == O &&
        board->GetValueAt(3) == O &&
        board->GetValueAt(6) == O)
    {
        return O;
    }

    if (board->GetValueAt(1) == O &&
        board->GetValueAt(4) == O &&
        board->GetValueAt(7) == O)
    {
        return O;
    }

    if (board->GetValueAt(2) == O &&
        board->GetValueAt(5) == O &&
        board->GetValueAt(8) == O)
    {
        return O;
    }

    if (board->GetValueAt(0) == O &&
        board->GetValueAt(4) == O &&
        board->GetValueAt(8) == O)
    {
        return O;
    }

    if (board->GetValueAt(2) == O &&
        board->GetValueAt(4) == O &&
        board->GetValueAt(6) == O)
    {
        return O;
    }

    return Empty;

}
