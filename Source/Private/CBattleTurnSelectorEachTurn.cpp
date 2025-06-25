#include "CBattleTurnSelectorEachTurn.h"
#include <algorithm>

unique_ptr<CGameObject> CBattleTurnSelectorEachTurn::GetNextTurn()
{
	return unique_ptr<CGameObject>();
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
