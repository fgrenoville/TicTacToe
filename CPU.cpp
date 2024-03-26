#include "CPU.h"

int CPU::numOfSolutions = 0;

CPU::CPU(Board* board, Symbols symb) : IPlayer(board, symb)
{
    std::cout << "CPU joins the game playing with symbol: " << symb << std::endl;

    opponentSymb = symb == X ? O : X;
}

CPU::~CPU()
{
    //std::cout << "CPU destructor..." << std::endl;

    delete state;
}

Symbols CPU::GetOpponentSymbol()
{
    return opponentSymb;
}

int CPU::NewMove(Board* board)
{
    std::cout << "CPU move..." << std::endl;

    if (state == nullptr)
    {
        HourGlass hourglass;
        stop_thread_1.store(false);

        std::thread t1(&HourGlass::Show, &hourglass, std::ref(stop_thread_1));

        state = new State(board);
        BuildTree(state, true, 0);
        MiniMax(state);
        currentGameState = state;

        stop_thread_1.store(true);
        t1.join();

        std::cout << "Calculated " << CPU::numOfSolutions << " solutions." << std::endl;
    }
    else
    {
        bool isTheSameBoard = true;
        int childIndex = INFINITY;
        if (currentGameState != nullptr && currentGameState->childrenNum > 0)
        {

            for (int i = 0; i < currentGameState->childrenNum; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (board->GetValueAt(j) != currentGameState->children[i]->board->GetValueAt(j))
                    {
                        isTheSameBoard = false;
                        break;
                    }
                }

                if (isTheSameBoard)
                {
                    childIndex = i;
                    break;
                }
                isTheSameBoard = true;
            }

            currentGameState = currentGameState->children[childIndex];
        }
    }

    //PrintAllNodes(currentGameState);

    return AskForMove(currentGameState);
}

void CPU::MiniMax(State* state)
{
    if (state != nullptr)
    {
        int val = 0;

        if (state->childrenNum > 0 && state->childrenNum < 2)
        {
            state->weight = state->children[0]->weight;

        }
        else
        {
            for (int i = 0; i < state->childrenNum; i++)
            {
                if (state->children[i]->weight == 999)
                {
                    MiniMax(state->children[i]);
                }

                bool isMin = state->depth % 2 == 1 ? true : false;

                if (i == 0)
                {
                    val = state->children[i]->weight;
                }

                if (isMin)
                {
                    if (state->children[i]->weight < val)
                    {
                        val = state->children[i]->weight;
                    }
                }
                else
                {
                    if (state->children[i]->weight > val)
                    {
                        val = state->children[i]->weight;
                    }
                }

            }

            state->weight = val;
        }
    }
}

int CPU::AskForMove(State* state)
{
    if (state != nullptr && state->childrenNum > 0)
    {
        int maxWeight = -999;
        int childIndex = -999;
        for (int i = 0; i < state->childrenNum; i++)
        {
            if (maxWeight < state->children[i]->weight)
            {
                maxWeight = state->children[i]->weight;
                childIndex = i;
            }
        }

        currentGameState = state->children[childIndex];

        for (int i = 0; i < 9; i++)
        {
            if (state->board->GetValueAt(i) != currentGameState->board->GetValueAt(i))
            {
                return i;
            }
        }

    }

    return -1;
}

void CPU::BuildTree(State* state, bool isMyTurn, int depth)
{

    std::vector<int> emptyCell;

    bool haveIWon = HaveIWon(state->board);
    bool hasOpponentWon = HasOpponentWon(state->board);
    if (haveIWon || hasOpponentWon)
    {
        state->weight = haveIWon ? 10 : -10;
        state->depth = depth;
        return;
    }
    else if (IsItTie(state->board))
    {
        state->weight = 0;
        state->depth = depth;
    }
    else
    {
        for (int i = 0; i < 9; i++)
        {
            if (state->board->GetValueAt(i) == Empty)
            {
                emptyCell.push_back(i);
            }
        }
    }

    if (emptyCell.size() > 0)
    {
        depth++;

        state->children = new State * [emptyCell.size()];
        state->childrenNum = (int)emptyCell.size();

        for (int i = 0; i < emptyCell.size(); i++)
        {
            State* newState = new State(state->board);

            newState->board->SetValueAt((isMyTurn ? symb : opponentSymb), emptyCell[i]);

            state->children[i] = newState;
            state->children[i]->depth = depth;

        }

        for (int i = 0; i < state->childrenNum; i++)
        {
            CPU::numOfSolutions++;
            BuildTree(state->children[i], !isMyTurn, depth);
        }
    }
}

void CPU::PrintAllNodes(State* state)
{
    if (state != nullptr)
    {
        std::cout << "___________" << " weight: " << state->weight << " depth: " << state->depth << std::endl;
        std::cout << state->board->GetValueAt(0) << " | " << state->board->GetValueAt(1) << " | " << state->board->GetValueAt(2) << std::endl;
        std::cout << state->board->GetValueAt(3) << " | " << state->board->GetValueAt(4) << " | " << state->board->GetValueAt(5) << std::endl;
        std::cout << state->board->GetValueAt(6) << " | " << state->board->GetValueAt(7) << " | " << state->board->GetValueAt(8) << std::endl;
        std::cout << "__________" << std::endl;

        int i = 0;

        while (i < state->childrenNum)
        {
            if (state->children[i] != nullptr)
            {
                PrintAllNodes(state->children[i]);
            }

            i++;
        }
    }
}

bool CPU::IsItTie(Board* board)
{
    for (int i = 0; i < 9; i++)
    {
        if (board->GetValueAt(i) == Empty)
            return false;
    }

    return true;

}

bool CPU::HaveIWon(Board* board)
{
    if (board->GetValueAt(0) == symb &&
        board->GetValueAt(1) == symb &&
        board->GetValueAt(2) == symb)
    {
        return true;
    }

    if (board->GetValueAt(3) == symb &&
        board->GetValueAt(4) == symb &&
        board->GetValueAt(5) == symb)
    {
        return true;
    }

    if (board->GetValueAt(6) == symb &&
        board->GetValueAt(7) == symb &&
        board->GetValueAt(8) == symb)
    {
        return true;
    }

    if (board->GetValueAt(0) == symb &&
        board->GetValueAt(3) == symb &&
        board->GetValueAt(6) == symb)
    {
        return true;
    }

    if (board->GetValueAt(1) == symb &&
        board->GetValueAt(4) == symb &&
        board->GetValueAt(7) == symb)
    {
        return true;
    }

    if (board->GetValueAt(2) == symb &&
        board->GetValueAt(5) == symb &&
        board->GetValueAt(8) == symb)
    {
        return true;
    }

    if (board->GetValueAt(0) == symb &&
        board->GetValueAt(4) == symb &&
        board->GetValueAt(8) == symb)
    {
        return true;
    }

    if (board->GetValueAt(2) == symb &&
        board->GetValueAt(4) == symb &&
        board->GetValueAt(6) == symb)
    {
        return true;
    }

    return false;
}

bool CPU::HasOpponentWon(Board* board)
{
    if (board->GetValueAt(0) == opponentSymb &&
        board->GetValueAt(1) == opponentSymb &&
        board->GetValueAt(2) == opponentSymb)
    {
        return true;
    }

    if (board->GetValueAt(3) == opponentSymb &&
        board->GetValueAt(4) == opponentSymb &&
        board->GetValueAt(5) == opponentSymb)
    {
        return true;
    }

    if (board->GetValueAt(6) == opponentSymb &&
        board->GetValueAt(7) == opponentSymb &&
        board->GetValueAt(8) == opponentSymb)
    {
        return true;
    }

    if (board->GetValueAt(0) == opponentSymb &&
        board->GetValueAt(3) == opponentSymb &&
        board->GetValueAt(6) == opponentSymb)
    {
        return true;
    }

    if (board->GetValueAt(1) == opponentSymb &&
        board->GetValueAt(4) == opponentSymb &&
        board->GetValueAt(7) == opponentSymb)
    {
        return true;
    }

    if (board->GetValueAt(2) == opponentSymb &&
        board->GetValueAt(5) == opponentSymb &&
        board->GetValueAt(8) == opponentSymb)
    {
        return true;
    }

    if (board->GetValueAt(0) == opponentSymb &&
        board->GetValueAt(4) == opponentSymb &&
        board->GetValueAt(8) == opponentSymb)
    {
        return true;
    }

    if (board->GetValueAt(2) == opponentSymb &&
        board->GetValueAt(4) == opponentSymb &&
        board->GetValueAt(6) == opponentSymb)
    {
        return true;
    }

    return false;
}



