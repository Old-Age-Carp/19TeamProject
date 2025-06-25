#pragma once
#include "CGameObject.h"
#include "CBattleManager.h"

#include <memory>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

class IBattleTurnSelector
{
public:
	virtual unique_ptr<CGameObject> GetNextTurn() = 0;
	virtual void SetTeams(vector<const shared_ptr<CIsBattleAble>> teamList) = 0;
};
