// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#pragma once

#include <array>
#include <string>
#include "Defines.h"
#include "CellState.h"

class BoardState
{
public:
    BoardState();
    BoardState(const std::array<int, 81>& cellValues);
    BoardState(const std::string filePath);
    BoardState(const BoardState& boardState);
    BoardState(BoardState&& boardState) noexcept;
    virtual ~BoardState() = default;

    BoardState& operator=(const BoardState& boardState);
    BoardState& operator=(BoardState&& boardState) noexcept;
    CellState& operator[](const int i);

    bool IsBlankCell(int i) const;
    std::set<int>&& CalculatePossibleValues(int i) const;

    bool IsBoardComplete() const;

protected:
    std::set<int>&& GetRelatedCellIndices(int i) const;

private:
    std::array<CellState, 81> m_board;
};

extern "C" EXPORTED BoardState* CreateEmptyBoardState();
extern "C" EXPORTED BoardState* CreateBoardStateFromArray(const std::array<int, 81>& cellValues);
extern "C" EXPORTED BoardState* CreateBoardStateFromFile(const std::string filePath);
extern "C" EXPORTED void ReleaseBoardState(BoardState* pBoardState);

DECLARE_SMART_PTR(BoardState)
#define CONVERT_TO_BOARDSTATEPTR(VAR_NAME, PTR) CONVERT_TO_SMART_PTR(BoardStatePtr, VAR_NAME, PTR, ReleaseBoardState)
