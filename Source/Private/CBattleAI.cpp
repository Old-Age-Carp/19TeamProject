#include "CBattleAI.h"
#include "CIsBattleAble.h"

#include <random>

using std::vector;

EActionKind CBattleAI::Think() const 
{
	// TODO: 아이템 사용 처리

	return EActionKind::Attack;
}

CBattleAbleObject* CBattleAI::ThinkTarget(EActionKind actionKind, std::vector<CIsBattleAble*> otherTeams) const
{
	CBattleAbleObject* target = nullptr;
	switch (actionKind)
	{
	case EActionKind::Attack:
	{
		int teamIndex = rand() % otherTeams.size();
		vector<CBattleAbleObject*> teamMemberList = otherTeams[teamIndex]->GetTeamBattlerList();
		int targetIndex = rand() % teamMemberList.size();
		target = teamMemberList[targetIndex];
		break;
	}
	case EActionKind::UseItem:
		target = battler;
		break;
	default:
		break;
	}
	return target;
}
