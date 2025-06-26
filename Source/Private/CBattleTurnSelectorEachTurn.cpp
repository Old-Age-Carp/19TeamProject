#include "CBattleTurnSelectorEachTurn.h"
#include "CIsBattleAble.h"
#include <algorithm>

CBattleAbleObject* CBattleTurnSelectorEachTurn::GetNextTurn()
{
	if (mTeamLastTurnIndexList.size() == 0)
		return nullptr;

	++mCurrentTeamIndex;
	if (mCurrentTeamIndex >= mTeamList.size())
		mCurrentTeamIndex = 0;
	int teamMemberIndex = ++mTeamLastTurnIndexList[mCurrentTeamIndex];

	if (teamMemberIndex >= mTeamList[mCurrentTeamIndex]->GetTeamBattlerList().size())
		teamMemberIndex = 0;
	
	shared_ptr<CIsBattleAble> team = mTeamList[mCurrentTeamIndex];

	auto& battlerList = team->GetTeamBattlerList();
	return battlerList[teamMemberIndex];
}

/// <summary>
/// 리스트에 나열된 순서로 턴을 가집니다.
/// </summary>
void CBattleTurnSelectorEachTurn::SetTeams(vector<shared_ptr<CIsBattleAble>> teamList)
{
	mTeamList = teamList;
	mTeamLastTurnIndexList.resize(teamList.size());
	std::fill(mTeamLastTurnIndexList.begin(), mTeamLastTurnIndexList.end(), -1);
	mCurrentTeamIndex = -1;
}
