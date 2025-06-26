#pragma once

#include <memory>
#include "TSingleton.h"
#include "CBattleAbleObject.h"
#include "CStaticDataManager.h"
#include "IBattleTurnSelector.h"

class CBattleManager : public TSingleton<CBattleManager>
{
public:
	CBattleManager() = default;

	void SetBattle(std::unique_ptr<IBattleTurnSelector> turnSelector, CIsBattleAble* team1, CIsBattleAble* team2);
	void PlayerTurn();
	void MonsterTurn(const std::vector<CIsBattleAble*>& otherTeams);
	bool IsAlive(int health) const { return health > 0; };
	bool NextTurn();				// 턴 넘기기 + 전투 종료 여부 반환
    CBattleAbleObject* GetCurrentTurn();	// 현재 턴 주체 반환
	
private:
	void GenerateMonster(bool isBoss, int monsterId);
	
	CIsBattleAble* m_pPlayer = nullptr;
	CIsBattleAble* m_pMonster = nullptr;
	CStaticDataManager* m_pStaticDataManager = nullptr;
	std::unique_ptr<IBattleTurnSelector> m_turnSelector;
	bool m_bIsBossBattle = false;
	int* m_pMonsterId = nullptr;
};
