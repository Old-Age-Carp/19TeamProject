#pragma once

#include <vector>

#include "CBattleAbleObject.h"

class CBattleTeam
{
public:
    CBattleTeam(std::vector<CBattleAbleObject*> battlers);
    bool IsAvailable() const;
    bool IsTeamBattleAvailable(int teamCount = 2) const;
    const std::vector<CBattleAbleObject*>& GetTeamBattlerList() { return m_battlers; }
private:
    std::vector<CBattleAbleObject*> m_battlers;
};
