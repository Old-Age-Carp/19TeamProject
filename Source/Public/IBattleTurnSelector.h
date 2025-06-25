#pragma once
#include "CGameObject.h"
#include "CBattleAbleObject.h"

#include <memory>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

class IBattleTurnSelector
{
public:
	virtual ~IBattleTurnSelector() = default;
	virtual CBattleAbleObject* GetNextTurn() = 0;
	virtual weak_ptr<CIsBattleAble> GetCurrentTeam() = 0;
	virtual void SetTeams(vector<shared_ptr<CIsBattleAble>>& teamList) = 0;
};
