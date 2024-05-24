#pragma once
#include "TicTacToe.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

class OnlineModeTicTacToe : public ITicTacToe
{
public:
    OnlineModeTicTacToe(std::string, std::string, int);
    ~OnlineModeTicTacToe() override = default;

private:
    void SetWindowTitle() override;
    void FirstPlayer(sf::Event) override;
    void SecondPlayer(sf::Event) override;

    std::optional<sf::Packet> Recieve();
    void Send(int, int);
    void Network();
    void Connect(std::string, int);
    void Listen(int);

    void clientTurn(sf::Event);
    void serverTurn();
    int ip;
    int seqNum_;
    sf::TcpSocket socket_;
    std::string port;
    std::string networkMode_;
};