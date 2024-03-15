#include <iostream>
#include <array>
#include "TicTacToe.h"

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