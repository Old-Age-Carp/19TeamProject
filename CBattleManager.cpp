#include "CBattleManager.h"
#include "CLogManager.h"
#include <random>

CBattleManager::CBattleManager(CPlayer* player, CLogManager* logger, m_pMonsterManager* monsterManager)
	:m_pPlayer(player), m_pLogger(logger), m_pMonsterManager(monsterManager), m_bIsBossBattle(false), m_MonsterCurrnetHp(0), m_MonsterCurrentAtk(0)
{
}

void CBattleManager::SetBattle()
{
	const int monsterId
	if(m_pPlayer*->GetLevel() >= 10)
	{
		int BossIds[] =  { 107, 108 };
		monsterId = bossIds[rand() % 2];
		m_bIsBossBattle = true;
	}
	else
	{
		monsterId = 101 + rnad() % 6;
		m_bIsBossBattle = false; 
	}

	FMonsterData* pData = m_pMonsterManager->GetMonsterData(monsterId);
	if(!pData)
	{
		retern;
	}

	m_bIsBossBattle = (pData->type == EMonsterType::Boss);
	m_Monster = CMonster(*pData);
	m_MonsterCurrentName = pData->Name;
	m_MonsterCurrentHp = pData->hp;
	m_MonsterCurrentAtk = pData->atk;
}

CMonster CBattleManager::GenerateMonster()
{
	return CMonster(*m_pMonsterManager->GetMonsterData(monsterId));
}

void CBattleManager::PlayerTurn()
{
	m_MonsterCurrentHp -= m_pPlayer.GetAttack();
}

void CBattleManager::MonsterTurn()
{
	if(m_MonsterCurrentHp <= 0)
	{
		return;
	}

	m_pPlayer->Damage(m_MonsterCurrentAtk);
}

