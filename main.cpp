//
//  TicTacToe
//
//

#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Match.h"
#include "IPlayer.h"
#include "Human.h"
#include "CPU.h"


char* ParseArguments(int argc, const char* argv[])
{
    char* params = new char[3]();

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);

        if (arg == "-h")
        {
            if (params[0] != 'H')
            {
                params[0] = 'H';
            }
        }
        else if (arg == "-p1:human") {
            if ((params[1] != 'H') && (params[1] != 'C'))
            {
                params[1] = 'H';
            }
        }
        else if (arg == "-p1:cpu")
        {
            if ((params[1] != 'H') && (params[1] != 'C'))
            {
                params[1] = 'C';
            }
        }
        else if (arg == "-p2:human")
        {
            if ((params[2] != 'H') && (params[2] != 'C'))
            {
                params[2] = 'H';
            }
        }
        else if (arg == "-p2:cpu")
        {
            if ((params[2] != 'H') && (params[2] != 'C'))
            {
                params[2] = 'C';
            }
        }
    }

    return params;
}

int main(int argc, const char* argv[]) {

    char* params = ParseArguments(argc, argv);

    if (params[0] == 'H')
    {
        std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h\t\tShow this help message" << std::endl;
        std::cout << "  -p1:human\tSet player1 as human" << std::endl;
        std::cout << "  -p1:cpu\tSet player1 as AI" << std::endl;
        std::cout << "  -p2:human\tSet player2 as human" << std::endl;
        std::cout << "  -p2:cpu\tSet player2 as AI" << std::endl;

        return 0;
    }
    
    Board* board = new Board();
    IPlayer* player1;
    IPlayer* player2;

    if (params[1] == 'H')
    {
        player1 = new Human(board, X);
    }
    else if (params[1] == 'C')
    {
        player1 = new CPU(board, X);
    }
    else
    {
        std::cout << "Error: player1 must be set." << std::endl;
        return -1;
    }

    if (params[2] == 'H')
    {
        player2 = new Human(board, O);
    }
    else if (params[2] == 'C')
    {
        player2 = new CPU(board, O);
    }
    else
    {
        std::cout << "Error: player2 must be set." << std::endl;
        return -1;
    }

    delete[] params;

    Match* match = new Match(board, player1, player2);

    match->Play();

    std::cout << "Thank you for playing TicTacToe." << std::endl;

    delete player2;
    delete player1;
    delete board;

    return 0;
}
