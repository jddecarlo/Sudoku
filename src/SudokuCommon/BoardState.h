// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#pragma once

#include <array>
#include "Defines.h"

class BoardState
{
private:
    class InnerSquareState
    {
    public:
        InnerSquareState();
        virtual ~InnerSquareState();

    private:
        std::array<int, 9> m_cells;
    };

public:
    BoardState();
    virtual ~BoardState();

private:
    std::array<InnerSquareState, 9> m_board;
};

extern "C" EXPORTED BoardState* CreateEmptyBoardState();
extern "C" EXPORTED void ReleaseBoardState(BoardState* pBoardState);

DECLARE_SMART_PTR(BoardState)
#define CONVERT_TO_BOARDSTATEPTR(VAR_NAME, PTR) CONVERT_TO_SMART_PTR(BoardStatePtr, VAR_NAME, PTR, ReleaseBoardState)
