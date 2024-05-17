#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <array>
#include <string>
#include <optional>
#include "TicTacToe.h"
#include "utils.h"
#include <cstdlib>
#include <ctime>

/*
enum class State
{
    Init = 0,
    CrossTurn,
    CircleTurn,
    GameWon,
    GameDraw
};

void Initialize()
{
    ....

    state = CrossTurn();
}

void ProcessTurn(player)
{
    if()
    {

    state = NextPlayer();
    }
}

void Run()
{
    switch (state)
    case Init:
    Initialize();
    break;
    case CrossTurn():
    ProcessTurn(Player::Cross);
    break;
    case CircleTurn():
    ProcessTurn(Plater::Circle);
    case Game....
}

*/

int main()
{
    ITicTacToe *ttt = nullptr;
    std::cout << "Choose mode(singleplayer(computer), multiplayer): \n";
    std::string modestr;
    std::cin >> modestr;
    if (modestr == "single")
    {
        ttt = new SingleModeTicTacToe();
    }
    else if (modestr == "multi")
    {
        ttt = new MultiModeTicTacToe();
    }
    else if (modestr == "online")
    {
        std::string networkchoice;
        std::cout << "Client or server? (c, s)\n";
        std::cin >> networkchoice;
        std::string ip;
        int port;
        if (networkchoice == "c")
        {
            std::cout << "Type in an IP address: ";
            std::cin >> ip;
            std::cout << "Type in a port: ";
            std::cin >> port;
        }
        else if (networkchoice == "s")
        {
            std::cout << "Type in a port: ";
            std::cin >> port;
        }
        ttt = new OnlineModeTicTacToe(networkchoice, ip, port);
    }

    ttt->Run();
    delete ttt;
    std::cout << "\nexit\n";
    return 0;
}