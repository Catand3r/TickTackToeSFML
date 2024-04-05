#pragma once
#include <iostream>
#include <array>
#include "SFML/Graphics.hpp"
#include <optional>

using X = std::array<sf::RectangleShape, 2>;

enum class Mode
{
    single = 0,
    multi
};

enum class Turn : bool
{
    cross = 0,
    circle = 1
};

enum class State
{
    empty = 0,
    circle, // 1
    cross   // 2
};

using Cells = std::array<std::array<State, 3>, 3>;

class TicTacToe
{
public:
    TicTacToe() = default; // only for tests - todo: delete it
    TicTacToe(Mode);
    void NextTurn();
    void SetEmptyCells();
    bool AreAllCellsNotEmpty();
    void ProcessTurn(const int, const int);
    std::optional<sf::RectangleShape> CreateWinLine();
    void Draw(sf::RenderWindow &);
    bool IsPlayerTurn() const;
    bool IsComputerTurn() const;
    bool IsCellEmpty(int, int);
    std::pair<int, int> ComputerMove();

private:
    std::optional<sf::RectangleShape> checkDiagonalWinCondition(State);
    std::optional<sf::RectangleShape> checkRowOrColumnWinCondition(State);
    Cells cells_;
    Turn turn_ = Turn::circle;
    Mode mode_ = Mode::multi;
};