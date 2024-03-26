#ifndef Board_hpp
#define Board_hpp

#include <iostream>
#include <string>

#include "Symbols.h"

class Board
{

public:
    Board();
    Board(Board& b);
    Symbols GetValueAt(int position);
    const char* GetPrintableValueAt(int position);
    void PrintValueAt(int position);
    bool SetValueAt(Symbols symb, int position);
    void PrintBoard();

private:
    Symbols table[9];

};

#endif
