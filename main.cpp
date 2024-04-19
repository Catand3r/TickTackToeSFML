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

    ttt->Run();
    delete ttt;
    std::cout << "\nexit\n";
    return 0;
}