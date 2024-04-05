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
    TicTacToe ttt;
    sf::RenderWindow window(sf::VideoMode(200, 200), "Kolko i krzyzyk");
    Lines lines{utils::CreateLine(66, 0, 90), utils::CreateLine(132, 0, 90), utils::CreateLine(0, 66, 0), utils::CreateLine(0, 132, 0)};
    std::cout << "isOpen" << window.isOpen() << '\n';
    std::cout << "Choose mode(singleplayer(computer), multiplayer): \n";
    std::string modestr;
    Mode mode;
    std::cin >> modestr;
    if (modestr == "singleplayer")
    {
        mode = Mode::single;
    }
    else if (modestr == "multiplayer")
    {
        mode = Mode::multi;
    }
    ttt.Run(window, lines);
    std::cout << "\nexit\n";
    return 0;
}