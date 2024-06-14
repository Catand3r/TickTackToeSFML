#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

namespace utils
{
    static sf::RectangleShape CreateLine(int x, int y, int rot, double length = 200.0, double width = 5.0, sf::Color color = sf::Color::White)
    {
        sf::RectangleShape line(sf::Vector2f(length, width));
        line.rotate(rot);
        line.setPosition(x, y);
        line.setFillColor(color);
        return line;
    }

    static sf::CircleShape CreateCircle(int x, int y, float c = 30.f)
    {
        sf::CircleShape circle(c);
        circle.setPosition(x, y);
        return circle;
    }
}