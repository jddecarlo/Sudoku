// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#include <algorithm>
#include "BoardState.h"
#pragma warning( push )
#pragma warning( disable : 26495 26451 4458 4996 4267 4244 )
#include "csv.h"
#pragma warning ( pop )

using namespace std;

extern "C" BoardState* CreateEmptyBoardState()
{
    return new BoardState();
}

extern "C" BoardState* CreateBoardStateFromArray(const array<int, 81>& cellValues)
{
    return new BoardState(cellValues);
}

extern "C" EXPORTED BoardState * CreateBoardStateFromFile(const string filePath)
{
    return new BoardState(filePath);
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

BoardState::BoardState(const string filePath)
{
    io::CSVReader<9> in(filePath);
    //in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
    //std::string vendor; int size; double speed;
    //while (in.read_row(vendor, size, speed)) {
        // do stuff with the data
    //}

    array<int, 9> buffer;
    auto iterator = m_board.begin();
    for (int i = 0; i < 9; i++)
    {
        if (in.read_row(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8]))
            std::for_each(buffer.begin(), buffer.end(), [&iterator](const int& value) { iterator++->SetValue(value); });
    }
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

CellState& BoardState::operator[](const int i)
{
    return m_board[i];
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