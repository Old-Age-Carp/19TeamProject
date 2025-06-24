#pragma once

#include <vector>
#include "CIsBattleAble.h"

class CIsBattleAble
{
public:
    CIsBattleAble(std::vector<class IHitAble*>& battlers);
    bool IsAvailable() const;
    bool IsTeamBattleAvailable(int teamCount = 2) const;
private:
    std::vector<IHitAble*>& m_battlers;
};