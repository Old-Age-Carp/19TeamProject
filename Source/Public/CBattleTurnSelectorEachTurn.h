#pragma once
#include "IBattleTurnSelector.h"

/// <summary>
/// 각 팀마다 한 명씩 턴을 분배하는 클래스.
/// </summary>
class CBattleTurnSelectorEachTurn : public IBattleTurnSelector
{
private:
	vector<const shared_ptr<CIsBattleAble>> mTeamList;
	//size = mTeamList.size 각 팀 별로 마지막으로 턴을 가진 인덱스가 저장되어 있다.
	vector<int> mTeamLastTurnIndexList;
	// 현재 턴인 팀의 인덱스 값.
	int currentTeamIndex;

public:
	weak_ptr<CGameObject> GetNextTurn() override;
	inline weak_ptr<CIsBattleAble> GetCurrentTeam() override
	{
		return currentTeamIndex < 0 ? weak_ptr<CIsBattleAble>()
			: weak_ptr(mTeamList[currentTeamIndex]);
	}
	void SetTeams(vector<const shared_ptr<CIsBattleAble>>& teamList) override;
};
