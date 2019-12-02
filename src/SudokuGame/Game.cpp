// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#include <set>
#include "Game.h"

using namespace std;

Game::Game(BoardStatePtr initialBoardState)
{
    m_startState = initialBoardState;
}

BoardStatePtr Game::Solve()
{
    stack<BoardStatePtr> branches;
    BoardStatePtr currentState = m_startState;
    while (!currentState->IsBoardComplete())
    {
        BoardStatePtr nextState;
        {
            BoardState* pClone = new BoardState(*currentState);
            CONVERT_TO_BOARDSTATEPTR(nextState, pClone);
        }
        FillInPossibleValues(nextState);
        if (SetObviousValues(nextState) > 0)
            currentState = nextState;
        else if (IsBoardStateInvalid(nextState))
        {
            if (branches.empty())
                return nullptr;

            currentState = branches.top();
            branches.pop();
        }
        else
        {
            PushBranches(nextState, branches);
            if (branches.empty())
                return nullptr;
            
            currentState = branches.top();
            branches.pop();
        }
    }

    return currentState;
}

void Game::FillInPossibleValues(BoardStatePtr state) const
{
    for (int i = 0; i < 81; i++)
    {
        auto possibleValues = state->CalculatePossibleValues(i);
        for (auto value : possibleValues)
            (*state)[i].AddPossibleValue(value);
    }
}

int Game::SetObviousValues(BoardStatePtr state) const
{
    int count = 0;
    for (int i = 0; i < 81; i++)
    {
        const auto& possibleValues = (*state)[i].GetPossibleValues();
        if (possibleValues.size() == 1)
        {
            (*state)[i].SetValue(*possibleValues.begin());
            ++count;
        }
    }

    return count;
}

bool Game::IsBoardStateInvalid(BoardStatePtr state) const
{

}

void Game::PushBranches(BoardStatePtr nextState, std::stack<BoardStatePtr> branches) const
{

}
