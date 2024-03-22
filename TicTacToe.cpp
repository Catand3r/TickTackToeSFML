#include <iostream>
#include <array>
#include "TicTacToe.h"
#include "SFML/Graphics.hpp"
#include "utils.h"
#include <optional>

TicTacToe::TicTacToe(Mode mode)
{
    mode_ = mode;
}

void TicTacToe::NextTurn()
{
    bool turnB = static_cast<bool>(turn_);
    turnB = !turnB;
    turn_ = static_cast<Turn>(turnB);
}

void TicTacToe::SetEmptyCells()
{
    for (int i = 0; i < cells_.size(); i++)
    {
        for (int j = 0; j < cells_[i].size(); j++)
        {
            std::cout << "cells " << i << " " << j << " = " << static_cast<int>(cells_[i][j]) << '\n';
            cells_[i][j] = State::empty;
        }
    }
}

bool TicTacToe::AreAllCellsNotEmpty()
{
    return cells_[0][0] != State::empty && cells_[0][1] != State::empty && cells_[0][2] != State::empty &&
           cells_[1][0] != State::empty && cells_[1][1] != State::empty && cells_[1][2] != State::empty &&
           cells_[2][0] != State::empty && cells_[2][1] != State::empty && cells_[2][2] != State::empty;
}

void TicTacToe::ProcessTurn(const int row, const int column)
{
    if (cells_[row][column] == State::empty)
    {
        cells_[row][column] = turn_ == Turn::circle ? State::circle : State::cross;
    }
    else
    {
        NextTurn();
    }
}

std::optional<sf::RectangleShape> TicTacToe::checkDiagonalWinCondition(State state)
{
    if (cells_[0][0] == state && cells_[1][1] == state && cells_[2][2] == state)
    {
        return utils::CreateLine(0, 0, 45, 282.8, 5.0, sf::Color::Red); // todo hardcoded
    }
    else if (cells_[2][0] == state && cells_[1][1] == state && cells_[0][2] == state)
    {
        return utils::CreateLine(200, 0, 135, 282.8, 5.0, sf::Color::Red); // todo hardcoded
    }

    return std::nullopt;
}

std::optional<sf::RectangleShape> TicTacToe::checkRowOrColumnWinCondition(State state)
{
    for (int i = 0; i < cells_.size(); i++)
    {
        if (cells_[i][0] == state && cells_[i][1] == state && cells_[i][2] == state)
        {
            return utils::CreateLine(0, i * 66 + 33, 0, 200.0, 5.0, sf::Color::Red);
        }
        for (int j = 0; j < cells_[i].size(); j++)
        {

            if (cells_[0][j] == state && cells_[1][j] == state && cells_[2][j] == state)
            {
                return utils::CreateLine(j * 66 + 33, 0, 90, 200.0, 5.0, sf::Color::Red);
            }
        }
    }

    return std::nullopt;
}

std::optional<sf::RectangleShape> TicTacToe::CreateWinLine()
{
    std::optional<sf::RectangleShape> winLine = checkDiagonalWinCondition(State::circle);
    if (!winLine.has_value())
    {
        winLine = checkDiagonalWinCondition(State::cross);
        if (!winLine.has_value())
        {
            winLine = checkRowOrColumnWinCondition(State::circle);
            if (!winLine.has_value())
            {
                winLine = checkRowOrColumnWinCondition(State::cross);
            }
        }
    }
    return winLine;
}

void TicTacToe::Draw(sf::RenderWindow &window)
{
    for (int i = 0; i < cells_.size(); i++)
    {
        for (int j = 0; j < cells_[i].size(); j++)
        {
            if (cells_[i][j] == State::circle)
            {
                sf::CircleShape circle = utils::CreateCircle(j * 66, i * 66);
                window.draw(circle);
            }
            else if (cells_[i][j] == State::cross)
            {
                X x{utils::CreateLine(j * 66, i * 66, 45, 84.0, 3.0), utils::CreateLine(j * 66, i * 66 + 60, -45, 84.0, 3.0)};
                for (const auto &line : x)
                {
                    window.draw(line);
                }
            }
        }
    }
}

bool TicTacToe::IsPlayerTurn() const
{
    return mode_ == Mode::single && turn_ == Turn::circle || mode_ == Mode::multi;
}

bool TicTacToe::IsComputerTurn() const
{
    return mode_ == Mode::single && turn_ == Turn::cross;
}
