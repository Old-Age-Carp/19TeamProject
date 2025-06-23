#pragma once

#include <memory>
#include "CGameObject.h"
#include "CMonster.h"
#include "CLogManager.h"
#include "CMonsterManager.h"
#include "CGameItem.h"

class CBattleManager
{
public:
	CBattleManager(CGameObject* gameObject, CLogManager* loger, CMonsterManager* monsterManager);


	void SetBattle();
	void PlayerTurn();
	void MonsterTurn();

private:
	CGameObject* m_pGameObject;
	CMonster m_Monster;
	CLogManager* m_pLogger;
	CMonsterManager* m_pMonsterManager;

	std::wstring MonsterCurrentName; 
	int m_MonsterCurrentHp = 0;
	int m_MonsterCurrentAtk = 0;

	bool m_bIsBossBattle;

	CMonster GenerateMonster();
};
