#pragma once
#include "IBattleTurnSelector.h"

class DefaultBattleTurnSelector : public IBattleTurnSelector
{
	unique_ptr<CGameObject> GetNextTurn() override;
	void SetTeams(vector<const shared_ptr<CIsBattleAble>> teamList) override;
};
