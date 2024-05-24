#pragma once
#include <iostream>
#include <array>
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <optional>
#include <string>

using X = std::array<sf::RectangleShape, 2>;

using Lines = std::array<sf::RectangleShape, 4>;

enum class GameState
{
    firstPlayer = 0,
    secondPlayer,
    win,
    gameDraw
};

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

enum class CellState
{
    empty = 0,
    circle, // 1
    cross   // 2
};

using Cells = std::array<std::array<CellState, 3>, 3>;

class ITicTacToe
{
public:
    void Run();
    ITicTacToe(); // only for tests - todo: delete it
    virtual ~ITicTacToe() = default;

protected:
    void ProcessTurn(const int, const int);
    std::optional<sf::RectangleShape> CreateWinLine();
    std::pair<int, int> ComputerMove();
    std::pair<int, int> HumanPlayerMove();
    std::optional<sf::RectangleShape> CheckDiagonalWinCondition(CellState) const;
    std::optional<sf::RectangleShape> CheckRowOrColumnWinCondition(CellState) const;
    bool IsCellEmpty(int, int);
    bool IsAnyCellEmpty() const;
    bool IsGameWon() const;
    void Draw();
    void SetEmptyCells();
    void RunGameState(sf::Event);
    void EndGame();
    virtual void SetWindowTitle();
    virtual void FirstPlayer(sf::Event) = 0;
    virtual void SecondPlayer(sf::Event) = 0;
    sf::RenderWindow window_;
    std::optional<sf::RectangleShape> winLine_;
    Cells cells_;
    GameState gstate_ = GameState::firstPlayer;
    Turn turn_ = Turn::circle;
    Lines lines_;
};

class SingleModeTicTacToe : public ITicTacToe
{
private:
    void SetWindowTitle() override;
    void FirstPlayer(sf::Event) override;
    void SecondPlayer(sf::Event) override;
};

class MultiModeTicTacToe : public ITicTacToe
{
private:
    void SetWindowTitle() override;
    void FirstPlayer(sf::Event) override;
    void SecondPlayer(sf::Event) override;
};