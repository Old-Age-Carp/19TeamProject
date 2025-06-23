#include "..\Public/CBattleManager.h"

void CBattleManager::SetBattle()
{
	int monsterId;
	if(*(m_pGameObject->Get_pLevel()) >= 10)
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
		m_pLogger->AddLog(L"Error: Monster data not found for ID: " + std::to_wstring(monsterId));
		return;
	}

	m_Monster = CMonster(pData);
	GenerateMonster(m_bIsBossBattle, monsterId);

	m_pLogger->AddLog(L"Battle started with monster: " + m_Monster.GetName() + L" (HP: " + std::to_wstring(m_Monster.GetCurrentHP()) + L", ATK: " + std::to_wstring(m_Monster.GetAttack()) + L")");
}

void CBattleManager::GenerateMonster(bool isBoss, int monsterId)
{
	if(isBoss)
	{
		m_pLogger->AddLog(L"Generating boss monster...");
	}
	else
	{
		m_pLogger->AddLog(L"Generating regular monster...");
	}
}

void CBattleManager::PlayerTurn()
{
	m_Monster.TakeDamage(m_pGameObject->getAttack());
	if(!m_Monster.IsAlive())
	{
		m_pLogger->AddLog(L"You defeated the monster: " + m_Monster.GetName());
		return;
	}
	m_pLogger->AddLog(L"You attacked the monster: " + m_Monster.GetName() + L" (Remaining HP: " + std::to_wstring(m_Monster.GetCurrentHP()) + L")");
}

void CBattleManager::MonsterTurn()
{
	int damage = m_Monster.GetAttack();
	*m_pGameObject->Get_pHealth() -= damage;
	if(*m_pGameObject->Get_pHealth() < 0)
	{
		*m_pGameObject->Get_pHealth() = 0;	}
	if(!GameObjectIsAlive())
	{
		m_pLogger->AddLog(L"The monster " + m_Monster.GetName() + L" has defeated you!");
		return;
	}
	m_pLogger->AddLog(L"The monster " + m_Monster.GetName() + L" attacked you! (Your remaining health: " + std::to_wstring(*m_pGameObject->Get_pHealth()) + L")");
}

bool CBattleManager::GameObjectIsAlive()
{
	return m_pGameObject->getHealth() > 0;
}

bool CBattleManager::MonsterIsAlive()
{
	return m_Monster.IsAlive();
}
