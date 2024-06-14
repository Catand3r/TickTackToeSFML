#include <iostream>
#include <array>
#include "TicTacToe.h"
#include "OnlineTicTacToe.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "utils.h"
#include <optional>
#include <cstdlib>
#include <ctime>
#include <limits>

// ITicTacToe

ITicTacToe::ITicTacToe() : window_(sf::VideoMode(500, 500), ""),
                           boardWidth_(0.66 * window_.getSize().x),
                           boardHeight_(0.66 * window_.getSize().y),
                           cellWidth_(0.33 * boardWidth_),
                           cellHeight_(0.33 * boardHeight_),
                           lines_({utils::CreateLine(0.22 * window_.getSize().x, 0, 90, boardWidth_),
                                   utils::CreateLine(0.44 * window_.getSize().x, 0, 90, boardWidth_),
                                   utils::CreateLine(0, 0.22 * window_.getSize().y, 0, boardHeight_),
                                   utils::CreateLine(0, 0.44 * window_.getSize().x, 0, boardHeight_),
                                   utils::CreateLine(0, 0.66 * window_.getSize().y, 0, boardHeight_),
                                   utils::CreateLine(0.66 * window_.getSize().x, 0, 90, boardWidth_)})

{
    std::srand(std::time(nullptr));
    SetEmptyCells();
    SetFont();
    SetTurnText();
    SetClockText();
}

void ITicTacToe::SetWindowTitle()
{
    window_.setTitle("ITicTacToe");
}

void ITicTacToe::SetFont()
{
    font_.loadFromFile("../Fonts/Arial.ttf");
}

void ITicTacToe::SetTurnText()
{
    turnText_.setPosition(0.33 * window_.getSize().x, 0.83 * window_.getSize().y);
    turnText_.setFont(font_);
    turnText_.setCharacterSize(0.08 * window_.getSize().x);
    turnText_.setFillColor(sf::Color::White);
}

void ITicTacToe::SetClockText()
{
    clockText_.setPosition(0.66 * window_.getSize().x, 0.83 * window_.getSize().y);
    clockText_.setFont(font_);
    clockText_.setCharacterSize(0.08 * window_.getSize().x);
    clockText_.setFillColor(sf::Color::White);
}

void ITicTacToe::UpdateClockText()
{
    int currentElapsedTime = clock_.getElapsedTime().asSeconds();
    std::string currentElapsedTimeString = std::to_string(currentElapsedTime);
    clockText_.setString(currentElapsedTimeString);
}

void ITicTacToe::UpdateTurnText(std::string string)
{
    turnText_.setString(string);
}

void ITicTacToe::Run()
{
    SetWindowTitle();
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
        UpdateTurnText("Circle");
        UpdateClockText();
        FirstPlayer(event);
        break;
    }
    case GameState::secondPlayer:
    {
        UpdateTurnText("Cross");
        UpdateClockText();
        SecondPlayer(event);
        break;
    }

    case GameState::gameDraw:
    case GameState::win:
    {

        EndGame();
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
    const int cellH = 0.66 * window_.getSize().y / 3;
    const int cellW = 0.66 * window_.getSize().x / 3;

    const int row = sf::Mouse::getPosition(window_).y / cellH;
    const int column = sf::Mouse::getPosition(window_).x / cellW;

    return {row, column};
}

void ITicTacToe::EndGame()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        winLine_ = std::nullopt;
        clock_.restart();
        window_.clear();
        SetEmptyCells();
        gstate_ = GameState::firstPlayer;
    }
}

bool ITicTacToe::IsGameWon() const
{
    return CrossWon() || CircleWon();
}

bool ITicTacToe::CrossWon() const
{
    return CheckDiagonalWinCondition(CellState::cross) || CheckRowOrColumnWinCondition(CellState::cross);
}

bool ITicTacToe::CircleWon() const
{
    return CheckDiagonalWinCondition(CellState::circle) || CheckRowOrColumnWinCondition(CellState::circle);
}

std::optional<sf::RectangleShape> ITicTacToe::CheckDiagonalWinCondition(CellState state) const
{
    if (cells_[0][0] == state && cells_[1][1] == state && cells_[2][2] == state)
    {
        return utils::CreateLine(0, 0, 45, boardWidth_ * 1.41, 5.0, sf::Color::Red);
    }
    else if (cells_[2][0] == state && cells_[1][1] == state && cells_[0][2] == state)
    {
        return utils::CreateLine(boardWidth_, 0, 135, boardHeight_ * 1.41, 5.0, sf::Color::Red);
    }

    return std::nullopt;
}

std::optional<sf::RectangleShape> ITicTacToe::CheckRowOrColumnWinCondition(CellState state) const
{
    for (int i = 0; i < cells_.size(); i++)
    {
        if (cells_[i][0] == state && cells_[i][1] == state && cells_[i][2] == state)
        {
            return utils::CreateLine(0, i * cellWidth_ + 0.5 * cellWidth_, 0, boardWidth_, 5.0, sf::Color::Red);
        }
        for (int j = 0; j < cells_[i].size(); j++)
        {

            if (cells_[0][j] == state && cells_[1][j] == state && cells_[2][j] == state)
            {
                return utils::CreateLine(j * cellHeight_ + 0.5 * cellHeight_, 0, 90, boardHeight_, 5.0, sf::Color::Red);
            }
        }
    }

    return std::nullopt;
}

std::optional<sf::RectangleShape> ITicTacToe::CreateWinLine()
{
    std::optional<sf::RectangleShape> winLine = CheckDiagonalWinCondition(CellState::circle);
    if (!winLine.has_value())
    {
        winLine = CheckDiagonalWinCondition(CellState::cross);
        if (!winLine.has_value())
        {
            winLine = CheckRowOrColumnWinCondition(CellState::circle);
            if (!winLine.has_value())
            {
                winLine = CheckRowOrColumnWinCondition(CellState::cross);
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
                const int xPos = j * 0.33 * boardWidth_;
                const int yPos = i * 0.33 * boardHeight_;
                const int radius = 0.5 * cellWidth_;
                sf::CircleShape circle = utils::CreateCircle(xPos, yPos, radius);
                window_.draw(circle);
            }
            else if (cells_[i][j] == CellState::cross)
            {
                const int xPos = j * 0.33 * boardWidth_;
                const int yPos = i * 0.33 * boardHeight_;
                const int length = cellHeight_ * 1.41;
                const int width = 0.045 * cellWidth_;
                X x{utils::CreateLine(xPos, yPos, 45, length, width),
                    utils::CreateLine(xPos + cellWidth_, yPos, 135, length, width)};
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

    window_.draw(turnText_);
    window_.draw(clockText_);

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

// SingleModeTicTacToe

SingleModeTicTacToe::SingleModeTicTacToe(std::string diffstr) : diffstr_(diffstr)
{
}

void SingleModeTicTacToe::FirstPlayer(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto [row, column] = HumanPlayerMove();

        std::cout << "Enter MouseButtonReleased\n";

        std::cout << "Player row: " << row << "column: " << column << "\n";
        ProcessTurn(row, column);
    }
}

void SingleModeTicTacToe::SecondPlayer(sf::Event)
{
    auto [row, column] = ComputerMove();
    std::cout << "Computer row: " << row << "column: " << column << "\n";
    ProcessTurn(row, column);
}

std::pair<int, int> SingleModeTicTacToe::ComputerMove()
{
    if (diffstr_ == "normal")
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
    else if (diffstr_ == "hard")
    {
        return BestComputerMove();
        std::cout << "Exiting BestComputerMove()\n";
    }
    return {-1, -1};
}

std::pair<int, int> SingleModeTicTacToe::BestComputerMove()
{
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (cells_[i][j] == CellState::empty)
            {
                cells_[i][j] = CellState::cross;
                int score = MiniMax(Turn::circle);
                // sf::sleep(sf::seconds(1));
                std::cout << "Result for computer move << " << i << " " << j << " = " << score << '\n';
                cells_[i][j] = CellState::empty;
                if (score > bestScore)
                {
                    std::cout << "Update bestScore for move " << i << " " << j << " = " << score << '\n';
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    std::cout << "Exiting BestComputerMove() with result = " << bestMove.first << " " << bestMove.second << '\n';
    return bestMove;
}

int SingleModeTicTacToe::MiniMax(Turn currentTurn)
{
    if (CrossWon())
        return 1;
    else if (CircleWon())
        return -1;
    else if (!IsAnyCellEmpty())
        return 0;

    if (currentTurn == Turn::cross) // maximizing
    {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (cells_[i][j] == CellState::empty)
                {
                    cells_[i][j] = CellState::cross;
                    int score = MiniMax(Turn::circle);
                    cells_[i][j] = CellState::empty;
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else // min
    {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (cells_[i][j] == CellState::empty)
                {
                    cells_[i][j] = CellState::circle;
                    int score = MiniMax(Turn::cross);
                    cells_[i][j] = CellState::empty;
                    bestScore = std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }

    // std::cout << "Minimax return " << bestScore << " for turn " << static_cast<int>(currentTurn) << '\n';
    // sf::sleep(sf::seconds(1));
}

void SingleModeTicTacToe::SetWindowTitle()
{
    window_.setTitle("Singleplayer TicTacToe");
}

// MultiModeTicTacToe

void MultiModeTicTacToe::FirstPlayer(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto [row, column] = HumanPlayerMove();

        std::cout << "Enter MouseButtonReleased\n";

        std::cout << "Player row: " << row << "column: " << column << "\n";
        ProcessTurn(row, column);
    }
}

void MultiModeTicTacToe::SecondPlayer(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto [row, column] = HumanPlayerMove();

        std::cout << "Enter MouseButtonReleased\n";

        std::cout << "Player row: " << row << "column: " << column << "\n";
        ProcessTurn(row, column);
    }
}

void MultiModeTicTacToe::SetWindowTitle()
{
    window_.setTitle("Multiplayer TicTacToe");
}

// OnlineModeTicTacToe

OnlineModeTicTacToe::OnlineModeTicTacToe(std::string networkchoice, std::string ip, int port) : networkMode_(networkchoice),
                                                                                                seqNum_(0)
{
    if (networkchoice == "c")
    {
        Connect(ip, port);
        sf::sleep(sf::seconds(1));
    }
    else if (networkchoice == "s")
    {
        Listen(port);
    }
}

void OnlineModeTicTacToe::Connect(std::string ip, int port)
{
    sf::Socket::Status status = socket_.connect(ip, port);
    if (status != sf::Socket::Done)
    {
        sf::Clock clock;
        while (status != sf::Socket::Done)
        {
            if (clock.getElapsedTime().asSeconds() >= 2)
            {
                status = socket_.connect(ip, port);
                std::cout << "Socket nie podłączony\n";
                clock.restart();
            }
        }
    }
    std::cout << "Socket podłączony\n";
    sf::SocketSelector selector;
    selector.add(socket_);
}

void OnlineModeTicTacToe::Listen(int port)
{
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(port) != sf::Socket::Done)
    {
        // error...
    }

    // accept a new connection
    if (listener.accept(socket_) != sf::Socket::Done)
    {
        // error...
    }
}

void OnlineModeTicTacToe::clientTurn(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        auto [row, column] = HumanPlayerMove();
        std::cout << "Enter MouseButtonReleased\n";

        std::cout << "Player row: " << row << "column: " << column << "\n";
        ProcessTurn(row, column);
        Send(row, column);
    }
}

void OnlineModeTicTacToe::serverTurn()
{
    std::optional<sf::Packet> recievePacket = Recieve();
    if (recievePacket.has_value())
    {
        int row, column, seqNum;
        *recievePacket >> seqNum >> row >> column;
        std::cout << "Odebrane numer: " << seqNum << ", row: " << row << ", odebrane column: " << column << "\n";
        if (seqNum == seqNum_)
        {
            ProcessTurn(row, column);
            seqNum_++;
        }
    }
}

void OnlineModeTicTacToe::Send(int row, int column)
{
    sf::Packet sendPacket;
    std::cout << "Wysłany numer: " << seqNum_ << ", row: " << row << ", wysłany column: " << column << "\n";
    sendPacket << seqNum_ << row << column;
    if (socket_.send(sendPacket) != sf::Socket::Done)
    {
        // error ...
    }
    seqNum_++;
}

std::optional<sf::Packet> OnlineModeTicTacToe::Recieve()
{
    sf::SocketSelector selector;
    selector.add(socket_);
    if (selector.wait(sf::milliseconds(100)))
    {
        if (selector.isReady(socket_))
        {
            sf::Packet recievedPacket;
            if (socket_.receive(recievedPacket) != sf::Socket::Done)
            {
                // error ...
            }
            else
            {
                return recievedPacket;
            }
            return std::nullopt;
        }
    }
    return std::nullopt;
}

void OnlineModeTicTacToe::FirstPlayer(sf::Event event)
{
    if (networkMode_ == "c")
    {
        clientTurn(event);
    }
    else if (networkMode_ == "s")
    {
        serverTurn();
    }
}

void OnlineModeTicTacToe::SecondPlayer(sf::Event event)
{
    if (networkMode_ == "c")
    {
        serverTurn();
    }
    else if (networkMode_ == "s")
    {
        clientTurn(event);
    }
}

void OnlineModeTicTacToe::SetWindowTitle()
{
    if (networkMode_ == "c")
    {
        window_.setTitle("Online TicTacToe (client)");
    }
    else if (networkMode_ == "s")
    {
        window_.setTitle("Online TicTacToe (server)");
    }
    else
    {
        window_.setTitle("Online TicTacToe");
    }
}