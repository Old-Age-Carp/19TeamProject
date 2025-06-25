#pragma once

#include <vector>
#include "CIsBattleAble.h"
#include "IBattleAble.h"

class CIsBattleAble
{
public:
    CIsBattleAble(std::vector<IBattleAble*>& battlers);
    bool IsAvailable() const;
    bool IsTeamBattleAvailable(int teamCount = 2) const;
    const std::vector<IBattleAble*>& GetTeamBattlerList();
private:
    std::vector<IBattleAble*>& m_battlers;
};
