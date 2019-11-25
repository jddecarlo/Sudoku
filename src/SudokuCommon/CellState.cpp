// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#include <algorithm>
#include "CellState.h"
#include "Defines.h"

using namespace std;

CellState::CellState() : m_value(BLANK_CELL)
{
}

CellState::CellState(int value) : m_value(value)
{
}

CellState::CellState(int value, const std::set<int>& possibleValues)
    : m_value(value), m_possibleValues(possibleValues)
{
}

CellState::CellState(const CellState& cellState)
{
    *this = cellState;
}

CellState::CellState(CellState&& cellState) noexcept
{
    *this = cellState;
}

CellState& CellState::operator=(const CellState& cellState)
{
    m_value = cellState.m_value;
    m_possibleValues = cellState.m_possibleValues;

    return *this;
}

CellState& CellState::operator=(CellState&& cellState) noexcept
{
    m_value = cellState.m_value;
    m_possibleValues = cellState.m_possibleValues;

    cellState.m_value = BLANK_CELL;
    cellState.m_possibleValues.clear();
    
    return *this;
}

bool CellState::IsBlankCell() const
{
    return m_value == BLANK_CELL;
}

int CellState::GetValue() const
{
    return m_value;
}

void CellState::SetValue(int value)
{
    m_value = value;
    m_possibleValues.clear();
}

const set<int>& CellState::GetPossibleValues() const
{
    return m_possibleValues;
}

void CellState::AddPossibleValue(int value)
{
    m_possibleValues.insert(value);
}

void CellState::RemovePossibleValue(int value)
{
    m_possibleValues.erase(value);
}
