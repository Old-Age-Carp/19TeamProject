#pragma once

#include <memory>
#include "CPlayer.h"
#include "CMonster.h"
#include "CLogManager.h"
#include "CMonsterManager.h"
#include "CGameItem.h"

class CBattleManager
{
public:
	CBattleManager(CPlayer* player, CLogManager* loger, CMonsterManager* monsterManager);


	void SetBattle();
	void PlayerTurn();
	void MonsterTurn();

private:
	CPlayer* m_pPlayer;
	CMonster m_Monster;
	CLogManager* m_pLogger;
	CMonsterManager* m_pMonsterManager;

	std::wstring MonsterCurrentName; 
	int m_MonsterCurrentHp = 0;
	int m_MonsterCurrentAtk = 0;

	bool m_bIsBossBattle;

	CMonster GenerateMonster();
};
