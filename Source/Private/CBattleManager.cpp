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

	m_pMonster = new CMonster(pData);
	GenerateMonster(m_bIsBossBattle, *m_pMonsterId);

	m_pLogger->AddLog(L"Battle started with monster: " + m_pMonster->getName() + L" (HP: " + std::to_wstring(m_pMonster->GetCurrentHP()) + L", ATK: " + std::to_wstring(m_pMonster->GetAttackValue()) + L")");
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
		m_pLogger->AddLog(L"You defeated the monster: " + m_pMonster->getName());

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
		m_pLogger->AddLog(L"You attacked the monster: " + m_pMonster->getName() + L" (Remaining HP: " + std::to_wstring(m_pMonster->GetCurrentHP()) + L")");
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
		m_pLogger->AddLog(L"The monster " + m_pMonster->getName() + L" has defeated you!");
		return;
	}
	m_pLogger->AddLog(L"The monster " + m_pMonster->getName() + L" attacked you! (Your remaining health: " + std::to_wstring(*m_pGameObject->Get_pHealth()) + L")");
}

bool CBattleManager::NextTurn()
{
    if (!m_pGameObject || !m_pMonster)
        return true;										// 전투 대상이 없으면 종료로 간주

    m_bIsPlayerTurn = !m_bIsPlayerTurn; 					// 턴 전환

    if (m_bIsPlayerTurn)
    {
        PlayerTurn();
        return !IsAlive(m_pMonster->GetCurrentHP());		// 몬스터 사망 여부
    }
    else
    {
        MonsterTurn();
        return !IsAlive(*m_pGameObject->Get_pHealth()); 	// 플레이어 사망 여부
    }
}

CGameObject* CBattleManager::GetCurrentTurn()
{
	return  m_bIsPlayerTurn ? m_pGameObject : static_cast<CGameObject*>(m_pMonster);
}
