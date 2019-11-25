// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#pragma once

#include <set>

class CellState
{
public:
    CellState();
    CellState(int value);
    CellState(int value, const std::set<int>& possibleValues);
    CellState(const CellState& cellState);
    CellState(CellState&& cellState) noexcept;
    virtual ~CellState() = default;

    CellState& operator=(const CellState& cellState);
    CellState& operator=(CellState&& cellState) noexcept;

    bool IsBlankCell() const;
    int GetValue() const;
    void SetValue(int value);
    const std::set<int>& GetPossibleValues() const;
    void AddPossibleValue(int value);
    void RemovePossibleValue(int value);

private:
    int m_value;
    std::set<int> m_possibleValues;
};