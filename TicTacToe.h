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
    std::optional<sf::RectangleShape> checkDiagonalWinCondition(CellState) const;
    std::optional<sf::RectangleShape> checkRowOrColumnWinCondition(CellState) const;
    void Draw();
    bool IsCellEmpty(int, int);
    void SetEmptyCells();
    bool IsAnyCellEmpty() const;
    bool IsGameWon() const;
    void RunGameState(sf::Event);
    virtual std::string GetWindowTitle();
    virtual void firstPlayer(sf::Event) = 0;
    virtual void secondPlayer(sf::Event) = 0;
    void endGame();
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
    std::string GetWindowTitle() override;
    void firstPlayer(sf::Event) override;
    void secondPlayer(sf::Event) override;
};

class MultiModeTicTacToe : public ITicTacToe
{
private:
    std::string GetWindowTitle() override;
    void firstPlayer(sf::Event) override;
    void secondPlayer(sf::Event) override;
};

class OnlineModeTicTacToe : public ITicTacToe
{
public:
    OnlineModeTicTacToe(std::string, std::string, int);

private:
    std::string GetWindowTitle() override;
    void Send(int, int);
    std::optional<sf::Packet> Recieve();
    void firstPlayer(sf::Event) override;
    void secondPlayer(sf::Event) override;
    void clientTurn(sf::Event);
    void serverTurn();
    void Network();
    void Connect(std::string, int);
    void Listen(int);
    sf::TcpSocket socket_;
    std::string port;
    int ip;
    std::string networkMode_;
};