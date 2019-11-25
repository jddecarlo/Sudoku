// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#include <algorithm>
#include "BoardState.h"

using namespace std;

extern "C" BoardState* CreateEmptyBoardState()
{
    return new BoardState();
}

extern "C" BoardState* CreateBoardStateFromArray(const array<int, 81>& cellValues)
{
    return new BoardState(cellValues);
}

extern "C" void ReleaseBoardState(BoardState* pBoardState)
{
    delete pBoardState;
}

BoardState::BoardState() : m_board()
{
}

BoardState::BoardState(const array<int, 81>& cellValues) : m_board()
{
    for (int i = 0; i < 81; i++)
        m_board[i].SetValue(cellValues[i]);
}

BoardState::BoardState(const BoardState& boardState)
{
    *this = boardState;
}

BoardState::BoardState(BoardState&& boardState) noexcept
{
    *this = boardState;
}

BoardState& BoardState::operator=(const BoardState& boardState)
{
    m_board = boardState.m_board;

    return *this;
}

BoardState& BoardState::operator=(BoardState&& boardState) noexcept
{
    m_board = boardState.m_board;
    
    CellState blankCell;
    boardState.m_board.fill(blankCell);

    return *this;
}

bool BoardState::IsBlankCell(int i) const
{
    return m_board[i].IsBlankCell();
}

set<int>&& BoardState::CalculatePossibleValues(int i) const
{
    if (!m_board[i].IsBlankCell())
        return move(set<int>{m_board[i].GetValue()});

    set<int> relatedCellIndices = GetRelatedCellIndices(i);
    set<int> existingValues;
    for (int index : relatedCellIndices)
    {
        const CellState& cellState = m_board[index];
        if (!cellState.IsBlankCell())
            existingValues.insert(cellState.GetValue());
    }

    set<int> allPossibleValues{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    set<int> possibleValues;
    set_difference(allPossibleValues.begin(), allPossibleValues.end(), 
        existingValues.begin(), existingValues.end(), inserter(possibleValues, possibleValues.begin()));

    return move(possibleValues);
}

set<int>&& BoardState::GetRelatedCellIndices(int i) const
{
    int row_start = GET_ROW_START_INDEX(i);
    int column_start = GET_COLUMN_START_INDEX(i);
    int square_start = GET_SQUARE_START_INDEX(i);
    set<int> indices;
    for (int index = 0; i < 9; i++)
    {
        indices.insert(row_start * 9 + index);
        indices.insert(index * 9 + column_start);
        indices.insert(square_start + (index % 3) + ((index / 3) * 9));
    }

    return move(indices);
}

bool BoardState::IsBoardComplete() const
{
    return find_if(m_board.begin(), m_board.end(), [](const CellState& cellState) { return cellState.IsBlankCell(); }) ==
        m_board.end();
}