#include "CBattleTeam.h"
#include "IHitAble.h"

CBattleTeam::CBattleTeam(std::vector<CBattleAbleObject*> battlers)
	: m_battlers(battlers)
{
}

bool CBattleTeam::IsAvailable() const
{
	int aliveCount = 0;
	for(const auto& battler : m_battlers)
	{
		if(battler && battler->IsAlive())
		{
			aliveCount++;
		}
	}
	return aliveCount >= 1;
}

bool CBattleTeam::IsTeamBattleAvailable(int teamCount) const
{
    std::vector<int> teamAliveCount(teamCount, 0);
    for(const auto& battler : m_battlers)
    {
        if(battler && battler->IsAlive())
        {
            int teamId = 0;// battler->GetTeamId();

            if(teamId >= 0 && teamId < teamCount)
            {
                teamAliveCount[teamId]++;
            }
        }
    }

    int aliveCount = 0;
    for(int count : teamAliveCount)
    {
        if(count >= 2)
        {
            aliveCount++;
        }
    }
    return aliveCount >= 2;
}
