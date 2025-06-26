#include "CBattleAI.h"
#include "CIsBattleAble.h"

#include <random>

using std::vector;

/// <summary>
/// 플레이어 아이템 쓰거나 공격을 합니다.
/// </summary>
EActionKind CBattleAI::Think() const 
{
	// 입력에 따른 출력 (없음)
	// 게임은 데이터와 그데이터의 변동이다.
	// 전투중에, 랜덤하게 사용하기 확률 미정

	// 아이템 있는가
	if (battler->GetHaveItems().size() > 0)
	{
		// 확률계산해서 아이템을 사용할건가?
		// 0~1;
		float random01 = static_cast<float>(rand()) / RAND_MAX;
		if (UseItemRatio >= rand()) // 0~1 0.1 보다 작거나 같으면 
		{
			// 아이템사용
			return EActionKind::UseItem;
		}
	}

	// 어택
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
