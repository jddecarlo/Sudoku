// Copyright (c) Jonathan DeCarlo.
// Licensed under the MIT license.

#pragma once

#include <stack>
#include "BoardState.h"

class Game
{
public:
    Game(BoardStatePtr initialBoardState);
    virtual ~Game() = default;

    BoardStatePtr Solve();

protected:
    void FillInPossibleValues(BoardStatePtr state) const;
    int SetObviousValues(BoardStatePtr state) const;
    bool IsBoardStateInvalid(BoardStatePtr state) const;
    void PushBranches(BoardStatePtr nextState, std::stack<BoardStatePtr> branches) const;

private:
    BoardStatePtr m_startState;
};
