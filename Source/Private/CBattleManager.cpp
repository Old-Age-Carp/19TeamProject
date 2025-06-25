#include "..\Public\CBattleManager.h"

void CBattleManager::SetBattle(std::unique_ptr<IBattleTurnSelector> turnSelector)
{	
	m_turnSelector = std::move(turnSelector);

	if(*(m_pGameObject->Get_pLevel()) >= 10)
	{
		int BossIds[] =  { 107, 108 };
		*m_pMonsterId = BossIds[rand() % 2];
		m_bIsBossBattle = true;
	}
	else
	{
		*m_pMonsterId = 101 + rand() % 6;
		m_bIsBossBattle = false;
	}

	const FMonsterData* pData = m_pStaticDataManager->GetMonsterData(*m_pMonsterId);
	if(!pData)
	{
		m_pLogger->AddLog(L"Error: Monster data not found for ID: " + std::to_wstring(*m_pMonsterId));
		return;
	}

	if(m_pMonster)
	{
		delete m_pMonster;
		m_pMonster = nullptr;
	}

	m_pMonster = new CMonster(pData);

	m_pLogger->AddLog(L"Battle started with monster: " + m_pMonster->GetName() + L" (HP: " + std::to_wstring(m_pMonster->GetCurrentHP()) + L", ATK: " + std::to_wstring(m_pMonster->GetAttackValue()) + L")");
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
	m_pMonster->TakeDamage(m_pGameObject->getAttack());

	if(!IsAlive(m_pMonster->GetCurrentHP()))
	{
		m_pLogger->AddLog(L"You defeated the monster: " + m_pMonster->GetName());

		*m_pGameObject->Get_pExp() += m_pMonster->GetExpReward();
		m_pLogger->AddLog(L"You gained " + std::to_wstring(m_pMonster->GetExpReward()) + L" experience points!");

		if(*m_pGameObject->Get_pExp() >= 100)
		{
			while(*m_pGameObject->Get_pExp() >= 100)
			{
				*m_pGameObject->Get_pLevel() += 1;
				*m_pGameObject->Get_pExp() -= 100;
			}
			*m_pGameObject->Get_pHealth() = *m_pGameObject->Get_pHealthMax();
			m_pLogger->AddLog(L"You leveled up! New level: " + std::to_wstring(*m_pGameObject->Get_pLevel()));
		}
		return;
	}
	else
	{
		m_pLogger->AddLog(L"You attacked the monster: " + m_pMonster->GetName() + L" (Remaining HP: " + std::to_wstring(m_pMonster->GetCurrentHP()) + L")");
	}
}

void CBattleManager::MonsterTurn()
{
	int damage = m_pMonster->GetAttackValue();
	*m_pGameObject->Get_pHealth() -= damage;
	
	if(*m_pGameObject->Get_pHealth() < 0)
	{
		*m_pGameObject->Get_pHealth() = 0;	
	}

	if(!IsAlive(*m_pGameObject->Get_pHealth()))
	{
		m_pLogger->AddLog(L"The monster " + m_pMonster->GetName() + L" has defeated you!");
		return;
	}
	m_pLogger->AddLog(L"The monster " + m_pMonster->GetName() + L" attacked you! (Your remaining health: " + std::to_wstring(*m_pGameObject->Get_pHealth()) + L")");
}

bool CBattleManager::IsAlive(int m_health) const
{
	return m_health > 0;
}

bool CBattleManager::NextTurn()
{
    if (!m_turnSelector)
	{
        return true;
	}

    CBattleAbleObject* nextActor = m_turnSelector->GetNextTurn();

	if (!nextActor)
	{
		return true;
	}

	if (nextActor == dynamic_cast<CBattleAbleObject*>(m_pGameObject))
	{
		PlayerTurn();
		return !IsAlive(m_pMonster->GetCurrentHP());
	}
    else if (nextActor == dynamic_cast<CBattleAbleObject*>(m_pMonster))
    {
        MonsterTurn();
        return !IsAlive(*m_pGameObject->Get_pHealth());
    }

    return true;
}

CGameObject* CBattleManager::GetCurrentTurn()
{
	return m_bIsPlayerTurn ? m_pGameObject : m_pMonster;
}