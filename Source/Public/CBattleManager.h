#pragma once

#include <random>
#include <vector>
#include <memory>
#include "TSingleton.h"
#include "CGameObject.h"
#include "CMonster.h"
#include "CLogManager.h"
#include "CStaticDataManager.h"
#include "CIsBattleAble.h"
#include "IBattleTurnSelector.h"

class CBattleManager : public TSingleton<CBattleManager>
{
public:
	CBattleManager() = default;

	void SetBattle(std::unique_ptr<IBattleTurnSelector> turnSelector);
	void PlayerTurn();
	void MonsterTurn();
	bool IsAlive(int health) const { return health > 0; };
	bool NextTurn();				// 턴 넘기기 + 전투 종료 여부 반환
    CGameObject* GetCurrentTurn();	// 현재 턴 주체 반환
	
private:
	bool m_bIsPlayerTurn = true; 	// 플레이어 턴 여부 true면 플레이어 턴, false면 몬스터 턴
	void GenerateMonster(bool isBoss, int monsterId);
	CGameObject* m_pGameObject;
	CMonster* m_pMonster;
	CLogManager* m_pLogger;
	CStaticDataManager* m_pStaticDataManager;
	std::unique_ptr<IBattleTurnSelector> m_turnSelector;
	bool m_bIsBossBattle = false;
	int* m_pMonsterId;
};
