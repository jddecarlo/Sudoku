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

BoardState::BoardState()
{
}

BoardState::~BoardState()
{
}

BoardState::InnerSquareState::InnerSquareState()
{
    m_cells.fill(BLANK_CELL);
}

BoardState::InnerSquareState::~InnerSquareState()
{
}