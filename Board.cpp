#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 9; i++)
    {
        table[i] = Empty;
    }
}

Board::Board(Board& b)
{
    //std::cout << "Copy constructor called..." << std::endl;
    table[0] = b.table[0];
    table[1] = b.table[1];
    table[2] = b.table[2];
    table[3] = b.table[3];
    table[4] = b.table[4];
    table[5] = b.table[5];
    table[6] = b.table[6];
    table[7] = b.table[7];
    table[8] = b.table[8];
}

Symbols Board::GetValueAt(int position)
{
    if (position >= 0 && position <= 8)
    {
        return table[position];
    }

    return Error;
}

bool Board::SetValueAt(Symbols symb, int position)
{
    if (position >= 0 && position <= 8)
    {
        if (table[position] == Empty)
        {
            table[position] = symb;
            return true;
        }
    }

    return false;
}

const char* Board::GetPrintableValueAt(int position)
{
    if (position >= 0 && position <= 8)
    {
        switch (table[position])
        {
        case Empty:
            return " ";
            break;
        case X:
            return "X";
            break;
        case O:
            return "O";
            break;
        case Error:
        default:
            return "Err";
            break;
        }
    }
}

void Board::PrintValueAt(int position)
{
    if (position >= 0 && position <= 8)
    {
        switch (table[position])
        {
        case Empty:
            std::cout << " ";
            break;
        case X:
            std::cout << "X";
            break;
        case O:
            std::cout << "O";
            break;
        case Error:
        default:
            std::cout << "Err";
            break;
        }
    }
}


void Board::PrintBoard()
{

    std::cout << "+---+" << "+---+" << "+---+" << std::endl;

    for (int i = 0; i < 9; i++)
    {
        std::cout << " ";

        PrintValueAt(i);

        std::cout << "  |  ";

        PrintValueAt(++i);

        std::cout << "  |  ";

        PrintValueAt(++i);

        std::cout << std::endl;

        //std::cout << " " << GetPrintableValueAt(i) << "  |  " << GetPrintableValueAt(++i) << "  |  " << GetPrintableValueAt(++i) << std::endl;
    }

    std::cout << "+---+" << "+---+" << "+---+" << std::endl;

}
