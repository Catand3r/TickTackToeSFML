#include <iostream>
#include <array>

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
    Turn turn_;
    void NextTurn();
    Cells cells_;
    void SetEmptyCells();
    bool AreAllCellsNotEmpty();
};