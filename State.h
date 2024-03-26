#ifndef State_hpp
#define State_hpp

#include <iostream>

#include "Board.h"

class State
{

public:
    Board* board;
    State** children;
    int childrenNum;
    int weight;
    int depth;

    State(Board* board);
    ~State();

private:

};
#endif
