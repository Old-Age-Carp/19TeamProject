#include "CBattleTurnSelectorEachTurn.h"
#include <algorithm>

weak_ptr<CGameObject> CBattleTurnSelectorEachTurn::GetNextTurn()
{
	++currentTeamIndex;
	int currentTeamIndex = ++mTeamLastTurnIndexList[currentTeamIndex];
	
	shared_ptr<CIsBattleAble> team = mTeamList[currentTeamIndex];

	auto& battlerList = team->GetTeamBattlerList();
	IBattleAble& battler = 
	//return weak_ptr(team[currentTeamIndex]);
}

/// <summary>
/// 리스트에 나열된 순서로 턴을 가집니다.
/// </summary>
void CBattleTurnSelectorEachTurn::SetTeams(vector<const shared_ptr<CIsBattleAble>>& teamList)
{
	mTeamList = teamList;
	mTeamLastTurnIndexList.resize(teamList.size());
	std::fill(mTeamLastTurnIndexList.begin(), mTeamLastTurnIndexList.end(), -1);
	currentTeamIndex = -1;
}
