#pragma once
#include "CGameObject.h"
#include "CBattleManager.h"

#include <memory>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

class IBattleTurnSelector
{
public:
	virtual weak_ptr<CGameObject> GetNextTurn() = 0;
	virtual void SetTeams(vector<const shared_ptr<CIsBattleAble>>& teamList) = 0;
};
