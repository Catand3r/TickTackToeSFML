#include "gtest/gtest.h"
#define protected public // to do: delete it
#include "TicTacToe.h"

using Cells = std::array<std::array<CellState, 3>, 3>;

Cells createEmptyCells()
{
    SingleModeTicTacToe ttt;
    Cells emptyCells;
    for (int i = 0; i < emptyCells.size(); i++)
    {
        for (int j = 0; j < emptyCells[i].size(); j++)
        {
            emptyCells[i][j] = CellState::empty;
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
    SingleModeTicTacToe ttt;
    ttt.SetEmptyCells();
    EXPECT_EQ(ttt.cells_, createEmptyCells());
}

TEST(SFMLExampleTests, GivenTicTacToeAndcells_WhenIsAnyCellEmptyIsCalledThencells_IsNotEqualToemptyCells)
{
    SingleModeTicTacToe ttt;
    ttt.SetEmptyCells();
    EXPECT_EQ(ttt.IsAnyCellEmpty(), true);
}