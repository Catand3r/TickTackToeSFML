#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <array>
#include <optional>
#include "TicTacToe.h"

using Lines = std::array<sf::RectangleShape, 4>;

using X = std::array<sf::RectangleShape, 2>;

sf::RectangleShape CreateLine(int x, int y, int rot, double length, double width, sf::Color color);

sf::CircleShape CreateCircle(int x, int y);

std::optional<sf::RectangleShape> checkDiagonalWinCondition(const Cells &cells, State state)
{
    if (cells[0][0] == state && cells[1][1] == state && cells[2][2] == state)
    {
        return CreateLine(0, 0, 45, 282.8, 5.0, sf::Color::Red); // todo hardcoded
    }
    else if (cells[2][0] == state && cells[1][1] == state && cells[0][2] == state)
    {
        return CreateLine(200, 0, 135, 282.8, 5.0, sf::Color::Red); // todo hardcoded
    }

    return std::nullopt;
}

std::optional<sf::RectangleShape> checkRowOrColumnWinCondition(const Cells &cells, State state)
{
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i][0] == state && cells[i][1] == state && cells[i][2] == state)
        {
            return CreateLine(0, i * 66 + 33, 0, 200.0, 5.0, sf::Color::Red);
        }
        for (int j = 0; j < cells[i].size(); j++)
        {

            if (cells[0][j] == state && cells[1][j] == state && cells[2][j] == state)
            {
                return CreateLine(j * 66 + 33, 0, 90, 200.0, 5.0, sf::Color::Red);
            }
        }
    }

    return std::nullopt;
}

sf::RectangleShape CreateLine(int x, int y, int rot, double length = 200.0, double width = 5.0, sf::Color color = sf::Color::White)
{
    sf::RectangleShape line(sf::Vector2f(length, width));
    line.rotate(rot);
    line.setPosition(x, y);
    line.setFillColor(color);
    return line;
}

void Run(sf::RenderWindow &window, Lines &lines)
{
    TicTacToe ttt;
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
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !winLine.has_value())
            {
                std::cout << "Enter MouseButtonReleased\n";
                bool drawX;
                bool drawCircle;
                ttt.NextTurn();

                const int cellWidth = window.getSize().x / 3;
                const int cellHeight = window.getSize().y / 3;

                row = sf::Mouse::getPosition(window).y / cellHeight;

                column = sf::Mouse::getPosition(window).x / cellWidth;

                std::cout << "Kliknieto row = " << row << " column = " << column << " runda =" << static_cast<bool>(ttt.turn_) << '\n';

                if (column < 0 || column > 2 || row < 0 || row > 2)
                    break;

                if (ttt.cells_[row][column] == State::empty)
                {
                    ttt.cells_[row][column] = ttt.turn_ == Turn::circle ? State::circle : State::cross;
                }
                else
                {
                    ttt.NextTurn();
                }

                winLine = checkDiagonalWinCondition(ttt.cells_, State::circle);
                if (!winLine.has_value())
                {
                    winLine = checkDiagonalWinCondition(ttt.cells_, State::cross);
                    if (!winLine.has_value())
                    {
                        winLine = checkRowOrColumnWinCondition(ttt.cells_, State::circle);
                        if (!winLine.has_value())
                        {
                            winLine = checkRowOrColumnWinCondition(ttt.cells_, State::cross);
                        }
                    }
                }
            }
        }

        window.clear();
        for (int i = 0; i < ttt.cells_.size(); i++)
        {
            for (int j = 0; j < ttt.cells_[i].size(); j++)
            {
                if (ttt.cells_[i][j] == State::circle)
                {
                    sf::CircleShape circle = CreateCircle(j * 66, i * 66);
                    window.draw(circle);
                }
                else if (ttt.cells_[i][j] == State::cross)
                {
                    X x{CreateLine(j * 66, i * 66, 45, 84.0, 3.0), CreateLine(j * 66, i * 66 + 60, -45, 84.0, 3.0)};
                    for (const auto &line : x)
                    {
                        window.draw(line);
                    }
                }
            }
        }

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
            for (int i = 0; i < ttt.cells_.size(); i++)
            {
                for (int j = 0; j < ttt.cells_.size(); j++)
                {
                    ttt.cells_[i][j] = State::empty;
                }
            }
        }
    }
}

sf::CircleShape CreateCircle(int x, int y)
{
    sf::CircleShape circle(30.f);
    circle.setPosition(x, y);
    return circle;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Kolko i krzyzyk");
    Lines lines{CreateLine(66, 0, 90), CreateLine(132, 0, 90), CreateLine(0, 66, 0), CreateLine(0, 132, 0)};
    std::cout << "isOpen" << window.isOpen() << '\n';
    Run(window, lines);
    std::cout << "\nexit\n";
    return 0;
}