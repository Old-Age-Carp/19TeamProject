#pragma once

#include <memory>
#include "CGameObject.h"
#include "CMonster.h"
#include "CLogManager.h"
#include "CStaticDataManager.h"
#include "CGameItem.h"

class CBattleManager
{
public:
	CBattleManager(CGameObject* gameObject, CLogManager* logger, CStaticDataManager* staticDataManager);

	void SetBattle();
	void PlayerTurn();
	void MonsterTurn();
	bool GameObjectIsAlive();
	bool MonsterIsAlive();

private:
	CGameObject* m_pGameObject;
	CMonster m_Monster;
	CLogManager* m_pLogger;
	CStaticDataManager* m_pStaticDataManager;

	std::wstring m_MonsterCurrentName;
	int m_MonsterCurrentHp = 0;
	int m_MonsterCurrentAtk = 0;

	bool m_bIsBossBattle;

	CMonster GenerateMonster();
};
