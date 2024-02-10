#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Kolko i krzyzyk");
    sf::RectangleShape lineVer1(sf::Vector2f(200, 5));
    lineVer1.rotate(90);
    lineVer1.setFillColor(sf::Color::White);
    lineVer1.setPosition(66, 0);
    sf::RectangleShape lineVer2(sf::Vector2f(200, 5));
    lineVer2.rotate(90);
    lineVer2.setFillColor(sf::Color::White);
    lineVer2.setPosition(134, 0);
    sf::RectangleShape lineVer3(sf::Vector2f(200, 5));
    lineVer3.rotate(90);
    lineVer3.setFillColor(sf::Color::White);
    lineVer3.setPosition(150, 0);
    sf::RectangleShape lineHor1(sf::Vector2f(200, 5));
    lineHor1.setPosition(0, 66);
    lineHor1.setFillColor(sf::Color::White);
    sf::RectangleShape lineHor2(sf::Vector2f(200, 5));
    lineHor2.setPosition(0, 134);
    lineHor2.setFillColor(sf::Color::White);
    sf::RectangleShape lineHor3(sf::Vector2f(200, 5));
    lineHor3.setPosition(0, 150);
    lineHor3.setFillColor(sf::Color::Cyan);
    std::cout << "isOpen" << window.isOpen() << '\n';
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(lineVer1);
        window.draw(lineVer2);
        // window.draw(lineVer3);
        window.draw(lineHor1);
        window.draw(lineHor2);
        // window.draw(lineHor3);
        window.display();
    }
    std::cout << "\nexit\n";
    return 0;
}