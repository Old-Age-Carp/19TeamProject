#include "CBattleTurnSelectorEachTurn.h"
#include <algorithm>

CBattleAbleObject* CBattleTurnSelectorEachTurn::GetNextTurn()
{
	if (mTeamLastTurnIndexList.size() == 0)
		return nullptr;

	++mCurrentTeamIndex;
	int teamMemberIndex = ++mTeamLastTurnIndexList[mCurrentTeamIndex];
	
	shared_ptr<CIsBattleAble> team = mTeamList[mCurrentTeamIndex];

	auto& battlerList = team->GetTeamBattlerList();
	return battlerList[teamMemberIndex];
}

/// <summary>
/// 리스트에 나열된 순서로 턴을 가집니다.
/// </summary>
void CBattleTurnSelectorEachTurn::SetTeams(vector<shared_ptr<CIsBattleAble>>& teamList)
{
	mTeamList = teamList;
	mTeamLastTurnIndexList.resize(teamList.size());
	std::fill(mTeamLastTurnIndexList.begin(), mTeamLastTurnIndexList.end(), -1);
	mCurrentTeamIndex = -1;
}
