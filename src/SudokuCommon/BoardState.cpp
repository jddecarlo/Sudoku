// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#include "BoardState.h"

using namespace std;

extern "C" BoardState* CreateEmptyBoardState()
{
    return new BoardState();
}

extern "C" void ReleaseBoardState(BoardState* pBoardState)
{
    delete pBoardState;
}

BoardState::InnerSquareState::InnerSquareState()
{
    m_cells.fill(BLANK_CELL);
}

int& BoardState::InnerSquareState::operator[](int i)
{
    return m_cells[i];
}

const int& BoardState::InnerSquareState::operator[](int i) const
{
    return m_cells[i];
}

BoardState::InnerSquareState& BoardState::operator[](int i)
{
    return m_board[i];
}

const BoardState::InnerSquareState& BoardState::operator[](int i) const
{
    return m_board[i];
}
