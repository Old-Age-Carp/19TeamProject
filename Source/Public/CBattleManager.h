#pragma once

#include <random>
#include <vector>
#include "CGameObject.h"
#include "CMonster.h"
#include "CLogManager.h"
#include "CStaticDataManager.h"

class CIsBattleAble
{
public:
	CIsBattleAble(const std::vector<CIsBattleAble*>& battlers);
	bool IsAvailable() const;
	bool IsTeamBattleAvailable(int teamCount = 2) const;

private:
	const std::vector<CIsBattleAble*>& m_battlers;
};

class CBattleManager
{
public:
	CBattleManager(CGameObject* gameObject, CLogManager* logger, CStaticDataManager* staticDataManager):
		m_pGameObject(gameObject),
		m_pLogger(logger),
		m_pStaticDataManager(staticDataManager),
		m_bIsBossBattle(false)
	{};

	void SetBattle();
	void PlayerTurn();
	void MonsterTurn();
	bool IsAlive(int health) const { return health > 0; };

private:
	void GenerateMonster(bool isBoss, int monsterId);
	CGameObject* m_pGameObject;
	CMonster* m_pMonster;
	CLogManager* m_pLogger;
	CStaticDataManager* m_pStaticDataManager;
	bool m_bIsBossBattle;
	int* m_pMonsterId;
};
