#pragma once

#include <vector>

#include "CBattleAbleObject.h"

class CIsBattleAble
{
public:
    CIsBattleAble(std::vector<CBattleAbleObject*>& battlers);
    CIsBattleAble(std::vector<CBattleAbleObject*>& battlers);
    bool IsAvailable() const;
    bool IsTeamBattleAvailable(int teamCount = 2) const;
    const std::vector<CBattleAbleObject*>& GetTeamBattlerList() { return m_battlers; }
private:
    std::vector<CBattleAbleObject*>& m_battlers;
};
