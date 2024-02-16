#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <array>

using Lines = std::array<sf::RectangleShape, 4>;

using X = std::array<sf::RectangleShape, 2>;

sf::RectangleShape CreateLine(int x, int y, int rot, int length, int width);

sf::CircleShape CreateCircle(int x, int y);

void Run(sf::RenderWindow &window, Lines &lines)
{
    while (window.isOpen())
    {
        sf::Event event;
        bool turn = false;
        int setPositionY;
        int setPositionX;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                bool drawX;
                bool drawCircle;
                if (turn)
                {
                    turn = false;
                }
                else
                {
                    turn = true;
                }

                if (sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < 66)
                {
                    setPositionY = 66;
                }
                else if (sf::Mouse::getPosition(window).y > 66 && sf::Mouse::getPosition(window).y < 132)
                {
                    setPositionY = 132;
                }
                else if (sf::Mouse::getPosition(window).y > 132 && sf::Mouse::getPosition(window).y < 200)
                {
                    setPositionY = 200;
                }

                if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < 66)
                {
                    setPositionX = 0;
                }
                else if (sf::Mouse::getPosition(window).x > 66 && sf::Mouse::getPosition(window).x < 132)
                {
                    setPositionX = 66;
                }
                else if (sf::Mouse::getPosition(window).x > 132 && sf::Mouse::getPosition(window).x < 200)
                {
                    setPositionX = 132;
                }
            }
        }

        // window.clear();

        // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        // {
        //     if (sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < 66)
        //     {
        //         setPositionY = 66;
        //     }
        //     else if (sf::Mouse::getPosition(window).y > 66 && sf::Mouse::getPosition(window).y < 132)
        //     {
        //         setPositionY = 132;
        //     }
        //     else if (sf::Mouse::getPosition(window).y > 132 && sf::Mouse::getPosition(window).y < 200)
        //     {
        //         setPositionY = 200;
        //     }

        //     if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < 66)
        //     {
        //         setPositionX = 0;
        //     }
        //     else if (sf::Mouse::getPosition(window).x > 66 && sf::Mouse::getPosition(window).x < 132)
        //     {
        //         setPositionX = 66;
        //     }
        //     else if (sf::Mouse::getPosition(window).x > 132 && sf::Mouse::getPosition(window).x < 200)
        //     {
        //         setPositionX = 132;
        //     }

        //     /*if (!turn)
        //     {
        //         std::cout << "Nacisnales podczas gdy wskaznik myszy mial pos x: " << sf::Mouse::getPosition(window).x << "i pos y: " << sf::Mouse::getPosition(window).y << "\n";
        //         drawCircle = false;
        //         drawX = true;
        //         // turn = true;
        //     }
        //     else if (turn)
        //     {
        //         drawX = false;
        //         drawCircle = true;
        //         // turn = false;
        //     }*/
        //     if (turn)
        //     {
        //         turn = false;
        //     }
        //     else
        //     {
        //         turn = true;
        //     }
        // }

        if (!turn)
        {
            X x{CreateLine(setPositionX, setPositionY - 60, 45, 84, 3), CreateLine(setPositionX, setPositionY, -45, 84, 3)};
            for (const auto &line : x)
            {
                window.draw(line);
            }
        }

        if (turn)
        {
            sf::CircleShape circle(CreateCircle(setPositionX, setPositionY - 60));
            window.draw(circle);
        }

        for (const auto &line : lines)
        {
            window.draw(line);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            window.clear();
        }
        window.display();
    }
}

sf::CircleShape CreateCircle(int x, int y)
{
    sf::CircleShape circle(30.f);
    circle.setPosition(x, y);
    return circle;
}

sf::RectangleShape CreateLine(int x, int y, int rot, int length = 200, int width = 5)
{
    sf::RectangleShape line(sf::Vector2f(length, width));
    line.rotate(rot);
    line.setPosition(x, y);
    return line;
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