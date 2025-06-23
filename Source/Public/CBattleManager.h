#pragma once

#include <random>
#include "CGameObject.h"
#include "CMonster.h"
#include "CLogManager.h"
#include "CStaticDataManager.h"

class CBattleManager
{
public:
	CBattleManager(CGameObject* gameObject, CLogManager* logger, CStaticDataManager* staticDataManager):
		m_pGameObject(gameObject),
		m_pLogger(logger),
		m_pStaticDataManager(staticDataManager),
		m_bIsBossBattle(false)
	{
	};

	void SetBattle();
	void PlayerTurn();
	void MonsterTurn();
	bool GameObjectIsAlive();
	bool MonsterIsAlive();

private:
	void GenerateMonster(bool isBoss, int monsterId);
	CGameObject* m_pGameObject;
	CMonster m_Monster;
	CLogManager* m_pLogger;
	CStaticDataManager* m_pStaticDataManager;
	bool m_bIsBossBattle;
};
