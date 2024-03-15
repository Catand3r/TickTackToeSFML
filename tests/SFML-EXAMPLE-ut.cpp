#include "gtest/gtest.h"
#include "TicTacToe.h"

using Cells = std::array<std::array<State, 3>, 3>;

Cells createEmptyCells()
{
    TicTacToe ttt;
    Cells emptyCells;
    for (int i = 0; i < emptyCells.size(); i++)
    {
        for (int j = 0; j < emptyCells[i].size(); j++)
        {
            emptyCells[i][j] = State::empty;
        }
    }
    return emptyCells;
}

TEST(SFMLExampleTests, AlwaysTrue)
{
    EXPECT_EQ(true, true);
}

TEST(SFMLExampleTests, GivenTicTacToeAndcells_WhenSetEmptyCellsIsCalledThencells_IsEqualToemptyCells)
{
    TicTacToe ttt;
    ttt.SetEmptyCells();
    EXPECT_EQ(ttt.cells_, createEmptyCells());
}

TEST(SFMLExampleTests, GivenTicTacToeAndturn_WhenNextTurnIsCalledThenturn_IsEqualToTurncircle)
{
    TicTacToe ttt;
    EXPECT_EQ(ttt.turn_, Turn::cross);
    ttt.NextTurn();
    EXPECT_EQ(ttt.turn_, Turn::circle);
    ttt.NextTurn();
    EXPECT_EQ(ttt.turn_, Turn::cross);
}

TEST(SFMLExampleTests, GivenTicTacToeAndcells_WhenIsAnyCellEmptyIsCalledThencells_IsNotEqualToemptyCells)
{
    TicTacToe ttt;
    ttt.SetEmptyCells();
    EXPECT_EQ(ttt.AreAllCellsNotEmpty(), false);
}