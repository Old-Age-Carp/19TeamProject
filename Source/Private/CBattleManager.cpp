#include "CBattleManager.h"
#include "CLogManager.h"
#include <random>

CBattleManager::CBattleManager(CPlayer* player, CLogManager* logger, m_pMonsterManager* monsterManager)
	:m_pGame(player), m_pLogger(logger), m_pMonsterManager(monsterManager), m_bIsBossBattle(false), m_MonsterCurrnetHp(0), m_MonsterCurrentAtk(0)
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
	m_pLogger->Log(L"Battle started with monster: " + m_MonsterCurrentName + L" (HP: " + std::to_wstring(m_MonsterCurrentHp) + L", ATK: " + std::to_wstring(m_MonsterCurrentAtk) + L")");
}

CMonster CBattleManager::GenerateMonster()
{
	m_pLoger->Log(L"Generating monster...");
	return CMonster(*m_pMonsterManager->GetMonsterData(monsterId));
}

void CBattleManager::PlayerTurn()
{
	m_MonsterCurrentHp -= m_pGameObject->getAttack();
	if(m_MonsterCurrentHp <= 0)
	{
		m_pLogger->Log(L"You defeated the monster: " + m_MonsterCurrentName);
		return;
	}
	m_pLogger->Log(L"You attacked the monster: " + m_MonsterCurrentName + L" (Remaining HP: " + std::to_wstring(m_MonsterCurrentHp) + L")");
}

void CBattleManager::MonsterTurn()
{
	if(m_MonsterCurrentHp <= 0)
	{
		return;
	}

	m_pGameObject->getHealth() -= m_MonsterCurrentAtk;

	if(m_pGameObject->getHealth() <= 0)
	{
		m_pLogger->Log(L"The monster " + m_MonsterCurrentName + L" has defeated you!");
		return;
	}
	m_pLogger->Log(L"The monster " + m_MonsterCurrentName + L" attacked you! (Your remaining health: " + std::to_wstring(m_pGameObject->getHealth()) + L")");
}

void CBattleManager::EndBattle()
{
	if(m_pGameObject->getHealth() <= 0)
	{
		m_pLogger->Log(L"You have been defeated by the monster: " + m_MonsterCurrentName);
		return;
	}

	m_pLogger->Log(L"Battle ended with monster: " + m_MonsterCurrentName);
	if (m_MonsterCurrentHp <= 0)
	{
		m_pLogger->Log(L"You have defeated the monster: " + m_MonsterCurrentName);
	}
	else
	{
		m_pLogger->Log(L"The monster " + m_MonsterCurrentName + L" has escaped!");
	}
}