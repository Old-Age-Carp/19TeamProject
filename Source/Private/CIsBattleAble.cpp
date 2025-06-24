#include "..\Public\CIsBattleAble.h"
#include "..\Public\IHitAble.h"

CIsBattleAble::CIsBattleAble(std::vector<IHitAble*>& battlers)
	: m_battlers(battlers)
{
}

bool CIsBattleAble::IsAvailable() const
{
	int aliveCount = 0;
	for(const auto& battler : m_battlers)
	{
		if(battler && battler->IsAlive())
		{
			aliveCount++;
		}
	}
	return aliveCount >= 2;
}

bool CIsBattleAble::IsTeamBattleAvailable(int teamCount) const
{
    std::vector<int> teamAliveCount(teamCount, 0);
    for(const auto& battler : m_battlers)
    {
        if(battler && battler->IsAlive())
        {
            continue;
        }
        
        int teamIndex = battler->GetTeamIndex();
        
        if(teamIndex >= 0 && teamIndex < teamCount)
        {
                teamAliveCount[teamIndex]++;
        }
    }

    int aliveCount = 0;
    for(int count : teamAliveCount)
    {
        if(count > 2)
        {
            aliveCount++;
        }
    }
    return aliveCount >= 2;
}
