#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <array>
#include <string>
#include <optional>
#include "TicTacToe.h"
#include "utils.h"

using Lines = std::array<sf::RectangleShape, 4>;

void Run(sf::RenderWindow &window, Lines &lines, Mode mode)
{
    TicTacToe ttt(mode);
    std::optional<sf::RectangleShape> winLine;
    ttt.SetEmptyCells();
    while (window.isOpen())
    {
        sf::Event event;
        int row = 0;
        int column = 0;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && ttt.IsPlayerTurn()) || (ttt.IsComputerTurn()) && !winLine.has_value())
            // ([[IsPlayerMove() and IsButtonClicked()] or [IsComputerMove] and !winLine.has_value()])
            {
                std::cout << "Enter MouseButtonReleased\n";
                ttt.NextTurn();

                const int cellWidth = window.getSize().x / 3;
                const int cellHeight = window.getSize().y / 3;

                row = sf::Mouse::getPosition(window).y / cellHeight;

                column = sf::Mouse::getPosition(window).x / cellWidth;

                if (column < 0 || column > 2 || row < 0 || row > 2)
                    break;

                ttt.ProcessTurn(row, column);
                winLine = ttt.CreateWinLine();
            }
        }

        window.clear();
        ttt.Draw(window);

        for (const auto &line : lines)
        {
            window.draw(line);
        }

        if (winLine.has_value())
        {
            window.draw(winLine.value());
        }
        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && (!ttt.AreAllCellsNotEmpty() || winLine.has_value()))
        {
            winLine = std::nullopt;
            window.clear();
            ttt.SetEmptyCells();
        }
    }
}

int main()
{
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
    Run(window, lines, mode);
    std::cout << "\nexit\n";
    return 0;
}