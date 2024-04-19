#include <iostream>
#include <array>
#include "TicTacToe.h"
#include "SFML/Graphics.hpp"
#include "utils.h"
#include <optional>
#include <cstdlib>
#include <ctime>

ITicTacToe::ITicTacToe() : lines_({utils::CreateLine(66, 0, 90), utils::CreateLine(132, 0, 90), utils::CreateLine(0, 66, 0), utils::CreateLine(0, 132, 0)}),
                           window_(sf::VideoMode(200, 200), "Kolko i krzyzyk")

{
    std::srand(std::time(nullptr));
    SetEmptyCells();
}

void ITicTacToe::Run()
{
    while (window_.isOpen())
    {
        sf::Event event;
        window_.pollEvent(event);

        if (event.type == sf::Event::Closed)
            window_.close();

        RunGameState(event);
        Draw();
    }
}

void ITicTacToe::RunGameState(sf::Event event)
{
    switch (gstate_)
    {
    case GameState::firstPlayer:
    {
        firstPlayer(event);
        break;
    }
    case GameState::secondPlayer:
    {
        secondPlayer(event);
        break;
    }

    case GameState::gameDraw:
    case GameState::win:
    {
        endGame();
        break;
    }
    }
}

void ITicTacToe::ProcessTurn(const int row, const int column)
{
    if (cells_[row][column] == CellState::empty)
    {
        cells_[row][column] = gstate_ == GameState::firstPlayer ? CellState::circle : CellState::cross;

        if (IsGameWon())
        {
            winLine_ = CreateWinLine();
            gstate_ = GameState::win;
        }
        else if (!IsAnyCellEmpty())
        {
            gstate_ = GameState::gameDraw;
        }
        else
        {
            if (gstate_ == GameState::firstPlayer)
            {
                gstate_ = GameState::secondPlayer;
            }
            else
            {
                gstate_ = GameState::firstPlayer;
            }
        }
    }
}

std::pair<int, int> ITicTacToe::HumanPlayerMove()
{
    const int cellWidth = window_.getSize().x / 3;
    const int cellHeight = window_.getSize().y / 3;

    const int row = sf::Mouse::getPosition(window_).y / cellHeight;
    const int column = sf::Mouse::getPosition(window_).x / cellWidth;

    return {row, column};
}

std::pair<int, int> ITicTacToe::ComputerMove()
{
    if (cells_[0][0] == CellState::cross && cells_[1][1] == CellState::cross && cells_[2][2] == CellState::empty)
    {
        return {2, 2};
    }
    else if (cells_[0][0] == CellState::cross && cells_[1][1] == CellState::empty && cells_[2][2] == CellState::cross)
    {
        return {1, 1};
    }
    else if (cells_[0][0] == CellState::empty && cells_[1][1] == CellState::cross && cells_[2][2] == CellState::cross)
    {
        return {0, 0};
    }
    else if (cells_[0][2] == CellState::cross && cells_[1][1] == CellState::cross && cells_[2][0] == CellState::empty)
    {
        return {2, 0};
    }
    else if (cells_[0][2] == CellState::cross && cells_[1][1] == CellState::empty && cells_[2][0] == CellState::cross)
    {
        return {1, 1};
    }
    else if (cells_[0][2] == CellState::empty && cells_[1][1] == CellState::cross && cells_[2][0] == CellState::cross)
    {
        return {0, 2};
    }

    for (int i = 0; i < cells_.size(); i++)
    {
        if (cells_[i][0] == CellState::cross && cells_[i][1] == CellState::cross && cells_[i][2] == CellState::empty)
        {
            return {i, 2};
        }
        else if (cells_[i][0] == CellState::cross && cells_[i][1] == CellState::empty && cells_[i][2] == CellState::cross)
        {
            return {i, 1};
        }
        else if (cells_[i][0] == CellState::empty && cells_[i][1] == CellState::cross && cells_[i][2] == CellState::cross)
        {
            return {i, 2};
        }
        // for (int j = 0; j < cells_[i].size(); j++)
        //{

        if (cells_[0][i] == CellState::cross && cells_[1][i] == CellState::cross && cells_[2][i] == CellState::empty)
        {
            return {2, i};
        }
        else if (cells_[0][i] == CellState::cross && cells_[1][i] == CellState::empty && cells_[2][i] == CellState::cross)
        {
            return {1, i};
        }
        else if (cells_[0][i] == CellState::empty && cells_[1][i] == CellState::cross && cells_[2][i] == CellState::cross)
        {
            return {0, i};
        }
        //}
    }

    int randomRow = std::rand() % 3;
    int randomColumn = std::rand() % 3;
    while (!IsCellEmpty(randomRow, randomColumn))
    {
        std::cout << "In while()\n";
        randomRow = std::rand() % 3;
        randomColumn = std::rand() % 3;
    }
    return {randomRow, randomColumn};
}

void ITicTacToe::endGame()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        winLine_ = std::nullopt;
        window_.clear();
        SetEmptyCells();
        gstate_ = GameState::firstPlayer;
    }
}

bool ITicTacToe::IsGameWon() const
{
    return checkDiagonalWinCondition(CellState::cross) ||
           checkRowOrColumnWinCondition(CellState::cross) ||
           checkDiagonalWinCondition(CellState::circle) ||
           checkRowOrColumnWinCondition(CellState::circle);
}

std::optional<sf::RectangleShape> ITicTacToe::checkDiagonalWinCondition(CellState state) const
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

std::optional<sf::RectangleShape> ITicTacToe::checkRowOrColumnWinCondition(CellState state) const
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

std::optional<sf::RectangleShape> ITicTacToe::CreateWinLine()
{
    std::optional<sf::RectangleShape> winLine = checkDiagonalWinCondition(CellState::circle);
    if (!winLine.has_value())
    {
        winLine = checkDiagonalWinCondition(CellState::cross);
        if (!winLine.has_value())
        {
            winLine = checkRowOrColumnWinCondition(CellState::circle);
            if (!winLine.has_value())
            {
                winLine = checkRowOrColumnWinCondition(CellState::cross);
            }
        }
    }
    if (!winLine.has_value() && IsAnyCellEmpty())
    {
        winLine = utils::CreateLine(0, 0, 0, 0.0, 0.0);
    }

    return winLine;
}

void ITicTacToe::Draw()
{
    window_.clear();
    for (int i = 0; i < cells_.size(); i++)
    {
        for (int j = 0; j < cells_[i].size(); j++)
        {
            if (cells_[i][j] == CellState::circle)
            {
                sf::CircleShape circle = utils::CreateCircle(j * 66, i * 66);
                window_.draw(circle);
            }
            else if (cells_[i][j] == CellState::cross)
            {
                X x{utils::CreateLine(j * 66, i * 66, 45, 84.0, 3.0), utils::CreateLine(j * 66, i * 66 + 60, -45, 84.0, 3.0)};
                for (const auto &line : x)
                {
                    window_.draw(line);
                }
            }
        }
    }

    for (const auto &line : lines_)
    {
        window_.draw(line);
    }

    if (winLine_.has_value())
    {
        window_.draw(winLine_.value());
    }
    window_.display();
}

void ITicTacToe::SetEmptyCells()
{
    for (int i = 0; i < cells_.size(); i++)
    {
        for (int j = 0; j < cells_[i].size(); j++)
        {
            std::cout << "cells " << i << " " << j << " = " << static_cast<int>(cells_[i][j]) << '\n';
            cells_[i][j] = CellState::empty;
        }
    }
}

bool ITicTacToe::IsAnyCellEmpty() const
{
    // to do: try to use std::anyof()
    return cells_[0][0] == CellState::empty || cells_[0][1] == CellState::empty || cells_[0][2] == CellState::empty ||
           cells_[1][0] == CellState::empty || cells_[1][1] == CellState::empty || cells_[1][2] == CellState::empty ||
           cells_[2][0] == CellState::empty || cells_[2][1] == CellState::empty || cells_[2][2] == CellState::empty;
}

bool ITicTacToe::IsCellEmpty(int row, int column)
{
    return cells_[row][column] == CellState::empty;
}

void SingleModeTicTacToe::firstPlayer(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto [row, column] = HumanPlayerMove();

        std::cout << "Enter MouseButtonReleased\n";

        std::cout << "Player row: " << row << "column: " << column << "\n";
        ProcessTurn(row, column);
    }
}

void SingleModeTicTacToe::secondPlayer(sf::Event)
{
    auto [row, column] = ComputerMove();
    std::cout << "Computer row: " << row << "column: " << column << "\n";
    ProcessTurn(row, column);
}

void MultiModeTicTacToe::firstPlayer(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto [row, column] = HumanPlayerMove();

        std::cout << "Enter MouseButtonReleased\n";

        std::cout << "Player row: " << row << "column: " << column << "\n";
        ProcessTurn(row, column);
    }
}

void MultiModeTicTacToe::secondPlayer(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto [row, column] = HumanPlayerMove();

        std::cout << "Enter MouseButtonReleased\n";

        std::cout << "Player row: " << row << "column: " << column << "\n";
        ProcessTurn(row, column);
    }
}