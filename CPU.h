#ifndef CPU_hpp
#define CPU_hpp

#include <iostream>
#include <vector>
#include <thread>

#include "IPlayer.h"
#include "State.h"
#include "HourGlass.h"

class CPU : public IPlayer
{

public:
    CPU(Board* board, Symbols symb);
    virtual ~CPU() override;
    virtual int NewMove(Board* board) override;
    Symbols GetOpponentSymbol();

private:
    Symbols opponentSymb;
    State* state;
    State* currentGameState;
    std::atomic_bool stop_thread_1;
    static int numOfSolutions;

    void BuildTree(State* state, bool isMyTurn, int depth);
    void MiniMax(State* state);
    int AskForMove(State* state);
    void PrintAllNodes(State* state);
    bool IsItTie(Board* board);
    bool HaveIWon(Board* board);
    bool HasOpponentWon(Board* board);

};

#endif
