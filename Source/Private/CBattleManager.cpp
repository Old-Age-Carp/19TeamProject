#include "CBattleManager.h"

void CBattleManager::SetBattle()
{
	int monsterId;
	if(m_pGameObject->getLevel() >= 10)
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

	const FMonsterData* pData = m_pStaticDataManager->GetMonsterData(monsterId);
	if(!pData)
	{
		m_pLogger->Log(L"Error: Monster data not found for ID: " + std::to_wstring(monsterId));
		return;
	}

	m_monster = CMonster(*pData);
	GenerateMonster(m_bIsBossBattle, monsterId);

	m_pLogger->Log(L"Battle started with monster: " + m_Monster.GetName() + L" (HP: " + std::to_wstring(m_Monster.GetHp()) + L", ATK: " + std::to_wstring(m_Monster.GetAtk()) + L")");
}

void CBattleManager::GenerateMonster(bool isBoss, int monsterId)
{
	if(isBoss)
	{
		m_pLogger->Log(L"Generating boss monster...");
	}
	else
	{
		m_pLogger->Log(L"Generating regular monster...");
	}
}

void CBattleManager::PlayerTurn()
{
	m_Monster.TakeDamage(m_pGameObject->getAttack());
	if(!MonsterIsAlive())
	{
		m_pLogger->Log(L"You defeated the monster: " + m_Monster.GetName());
		return;
	}
	m_pLogger->Log(L"You attacked the monster: " + m_Monster.GetName() + L" (Remaining HP: " + std::to_wstring(m_Monster.GetCurrentHp()) + L")");
}

void CBattleManager::MonsterTurn()
{
	m_pGameObject->TakeDamage(m_Monster.GetAttack()); // CGameObject don't have a TakeDamage method

	if(!GameObjectIsAlive())
	{
		m_pLogger->Log(L"The monster " + m_Monster.GetName() + L" has defeated you!");
		return;
	}
	m_pLogger->Log(L"The monster " + m_Monster.GetName() + L" attacked you! (Your remaining health: " + std::to_wstring(m_pGameObject->getHealth()) + L")");
}

bool CBattleManager::GameObjectIsAlive()
{
	return m_pGameObject->getHealth() > 0;
}

bool CBattleManager::MonsterIsAlive()
{
	return m_Monster.IsAlive();
}
