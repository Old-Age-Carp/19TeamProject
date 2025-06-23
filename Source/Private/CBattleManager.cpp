#include "CBattleManager.h"
#include "CLogManager.h"
#include <random>

CBattleManager::CBattleManager(CPlayer* player, CLogManager* logger, m_pMonsterManager* monsterManager)
	:m_pGameObject(gameObject), m_pLogger(logger), m_pMonsterManager(monsterManager), m_bIsBossBattle(false), m_MonsterCurrnetHp(0), m_MonsterCurrentAtk(0)
{
}

void CBattleManager::SetBattle()
{
	const int monsterId;
	if(m_pGameObject->iLevel() >= 10)
	{
		int BossIds[] =  { 107, 108 };
		monsterId = BossIds[rand() % 2];
		m_bIsBossBattle = true;
	}
	else
	{
		monsterId = 101 + rand() % 6;
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

	GenerateMonster();

	m_pLogger->Log(L"Battle started with monster: " + m_MonsterCurrentName + L" (HP: " + std::to_wstring(m_MonsterCurrentHp) + L", ATK: " + std::to_wstring(m_MonsterCurrentAtk) + L")");
}

CMonster CBattleManager::GenerateMonster()
{
	if(m_bIsBossBattle)
	{
		m_pLogger->Log(L"Generating boss monster...");
	}
	else
	{
		m_pLogger->Log(L"Generating regular monster...");
	}
	return CMonster(*m_pMonsterManager->GetMonsterData(monsterId));
}

void CBattleManager::PlayerTurn()
{
	m_MonsterCurrentHp -= m_pGameObject->getAttack();
	if(!MonsterIsAlive())
	{
		m_pLogger->Log(L"You defeated the monster: " + m_MonsterCurrentName);
		return;
	}
	m_pLogger->Log(L"You attacked the monster: " + m_MonsterCurrentName + L" (Remaining HP: " + std::to_wstring(m_MonsterCurrentHp) + L")");
}

void CBattleManager::MonsterTurn()
{
	m_pGameObject->getHealth() -= m_MonsterCurrentAtk;

	if(!GameObjectIsAlive())
	{
		m_pLogger->Log(L"The monster " + m_MonsterCurrentName + L" has defeated you!");
		return;
	}
	m_pLogger->Log(L"The monster " + m_MonsterCurrentName + L" attacked you! (Your remaining health: " + std::to_wstring(m_pGameObject->getHealth()) + L")");
}

bool CBattleManager::GameObjectIsAlive()
{
	return m_pGameObject->getHealth() > 0;
}

bool CBattleManager::MonsterIsAlive()
{
	return m_MonsterCurrentHp > 0;
}
