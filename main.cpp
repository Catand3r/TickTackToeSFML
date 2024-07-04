#include <iostream>
#include <string>
#include "TicTacToe.h"
#include "OnlineTicTacToe.h"

int main()
{
    ITicTacToe *ttt = nullptr;
    std::cout << "Choose mode(singleplayer(computer), multiplayer, online): \n";
    std::string modestr;
    std::cin >> modestr;
    if (modestr == "single")
    {
        std::cout << "Choose difficulty(normal (random), hard (minimax))";
        std::string diffstr;
        std::cin >> diffstr;
        if (diffstr == "normal")
        {
            ttt = new SingleModeTicTacToe(diffstr);
        }
        else if (diffstr == "hard")
        {
            ttt = new SingleModeTicTacToe(diffstr);
        }
    }
    else if (modestr == "multi")
    {
        ttt = new MultiModeTicTacToe();
    }
    else if (modestr == "online")
    {
        std::string networkchoice;
        std::cout << "Client or server? (c, s)\n";
        std::cin >> networkchoice;
        std::string ip;
        int port;
        if (networkchoice == "c")
        {
            std::cout << "Type in an IP address: ";
            std::cin >> ip;
            std::cout << "Type in a port: ";
            std::cin >> port;
        }
        else if (networkchoice == "s")
        {
            std::cout << "Type in a port: ";
            std::cin >> port;
        }
        ttt = new OnlineModeTicTacToe(networkchoice, ip, port);
    }

    ttt->Run();
    delete ttt;
    std::cout << "\nexit\n";
    return 0;
}