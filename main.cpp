#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <array>

using Lines = std::array<sf::RectangleShape, 4>;

using X = std::array<sf::RectangleShape, 2>;

using Cells = std::array<std::array<int, 3>, 3>;

sf::RectangleShape CreateLine(int x, int y, int rot, double length, double width, sf::Color color);

sf::CircleShape CreateCircle(int x, int y);

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
    Cells cells;
    bool turn = false;
    sf::RectangleShape winLine;
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[i].size(); j++)
        {
            std::cout << "cells " << i << " " << j << " = " << cells[i][j] << '\n';
            cells[i][j] = 0;
        }
    }
    while (window.isOpen())
    {
        sf::Event event;
        int row = 0;
        int column = 0;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Enter MouseButtonReleased\n";
                bool drawX;
                bool drawCircle;
                turn = !turn;

                if (sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < 66)
                {
                    // Jesteśmy w pierwszym wierszu
                    row = 0;
                }
                else if (sf::Mouse::getPosition(window).y > 66 && sf::Mouse::getPosition(window).y < 132)
                {
                    row = 1;
                }
                else if (sf::Mouse::getPosition(window).y > 132 && sf::Mouse::getPosition(window).y < 200)
                {
                    row = 2;
                }

                if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < 66)
                {
                    column = 0;
                }
                else if (sf::Mouse::getPosition(window).x > 66 && sf::Mouse::getPosition(window).x < 132)
                {
                    column = 1;
                }
                else if (sf::Mouse::getPosition(window).x > 132 && sf::Mouse::getPosition(window).x < 200)
                {
                    column = 2;
                }

                std::cout << "Kliknieto row = " << row << " column = " << column << " runda =" << turn << '\n';

                if (turn && cells[row][column] == 0)
                {
                    cells[row][column] = 1; // kolko
                }
                else if (!turn && cells[row][column] == 0)
                {
                    cells[row][column] = 2; // krzyzyk
                }
                else if (turn && cells[row][column] != 0)
                {
                    std::cout << "Niepoprawny ruch\n";
                    turn = false;
                }
                else if (!turn && cells[row][column] != 0)
                {
                    std::cout << "Niepoprawny ruch\n";
                    turn = true;
                }

                if (cells[0][0] == 1 && cells[1][1] == 1 && cells[2][2] == 1)
                {
                    // zwyciestwo kolek
                    winLine = CreateLine(0, 0, 45, 282.8, 5.0, sf::Color::Red);
                }
                else if (cells[2][0] == 1 && cells[1][1] == 1 && cells[0][2] == 1)
                {
                    // zwyciestwo kolek
                    winLine = CreateLine(0, 0, 135, 282.8, 5.0, sf::Color::Red);
                }
                else if (cells[0][0] == 2 && cells[1][1] == 2 && cells[2][2] == 2)
                {
                    // zwyciestwo krzyzykow
                    winLine = CreateLine(0, 0, 45, 282.8, 5.0, sf::Color::Red);
                }
                else if (cells[2][0] == 2 && cells[1][1] == 2 && cells[0][2] == 2)
                {
                    // zwyciestwo krzyzykow
                    winLine = CreateLine(0, 0, 135, 282.8, 5.0, sf::Color::Red);
                }

                for (int i = 0; i < cells.size(); i++)
                {
                    if (cells[i][0] == 1 && cells[i][1] == 1 && cells[i][2] == 1)
                    {
                        // zwyciestwo kolek
                        winLine = CreateLine(0, i * 66 + 33, 0, 200.0, 5.0, sf::Color::Red);
                        std::cout << "Narysowano linie zwyciestwo kolek\n";
                    }
                    else if (cells[i][0] == 2 && cells[i][1] == 2 && cells[i][2] == 2)
                    {
                        // zwyciestwo krzyzykow
                        winLine = CreateLine(0, i * 66 + 33, 0, 200.0, 5.0, sf::Color::Red);
                        std::cout << "Narysowano linie zwyciestwo krzyzkow\n";
                    }
                    for (int j = 0; j < cells[i].size(); j++)
                    {

                        if (cells[0][j] == 1 && cells[1][j] == 1 && cells[2][j] == 1)
                        {
                            // zwyciestwo kolek
                            winLine = CreateLine(j * 66 + 33, 0, 90, 200.0, 5.0, sf::Color::Red);
                            std::cout << "Narysowano linie zwyciestwo kolek\n";
                        }
                        else if (cells[0][j] == 2 && cells[1][j] == 2 && cells[2][j] == 2)
                        {
                            // zwyciestwo krzyzykow
                            winLine = CreateLine(j * 66 + 33, 0, 90, 200.0, 5.0, sf::Color::Red);
                            std::cout << "Narysowano linie zwyciestwo krzyzkow\n";
                        }
                    }
                }
            }
        }

        window.clear();
        for (int i = 0; i < cells.size(); i++)
        {
            for (int j = 0; j < cells[i].size(); j++)
            {
                if (cells[i][j] == 1)
                {
                    sf::CircleShape circle = CreateCircle(j * 66, i * 66);
                    window.draw(circle);
                }
                else if (cells[i][j] == 2)
                {
                    X x{CreateLine(j * 66, i * 66, 45, 84.0, 3.0), CreateLine(j * 66, i * 66 + 60, -45, 84.0, 3.0)};
                    for (const auto &line : x)
                    {
                        window.draw(line);
                    }
                }
            }
        }

        if (cells[0][0] != 0 && cells[0][1] != 0 && cells[0][2] != 0 && cells[1][0] != 0 && cells[1][1] != 0 && cells[1][2] != 0 && cells[2][0] != 0 && cells[2][1] != 0 && cells[2][2] != 0)
        {
            window.clear();
            for (int i = 0; i < cells.size(); i++)
            {
                for (int j = 0; j < cells.size(); j++)
                {
                    cells[i][j] = 0;
                }
            }
        }

        for (const auto &line : lines)
        {
            window.draw(line);
        }

        window.draw(winLine);

        window.display();
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