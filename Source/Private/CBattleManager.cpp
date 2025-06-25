#include "..\Public\CBattleManager.h"
#include "..\Public\CMonster.h"
#include "..\Public\CGameObject.h"
#include <cstdlib>
#include <ctime>

void CBattleManager::SetBattle(std::unique_ptr<IBattleTurnSelector> turnSelector, CBattleAbleObject* team1, CBattleAbleObject* team2)
{
	m_turnSelector = std::move(turnSelector);

	m_pPlayer = team1;
	m_pMonster = team2;

	if (m_pPlayer == nullptr || m_pMonster == nullptr)
	{
		return;
	}

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

    
	if (*(static_cast<CGameObject*>(m_pPlayer)->Get_pLevel()) >= 10)
    {	
		int BossIds[] = { 107, 108 };
    	int numBosses = static_cast<int>(std::size(BossIds));
        *m_pMonsterId = BossIds[rand() % numBosses];
        m_bIsBossBattle = true;
    }
    else
    {
        int normalMonsterMinId = 101;
        int normalMonsterMaxId = 106;

        int normalRange = normalMonsterMaxId - normalMonsterMinId + 1;
        *m_pMonsterId = normalMonsterMinId + rand() % normalRange;
        m_bIsBossBattle = false;
    }
	GenerateMonster(m_bIsBossBattle, *m_pMonsterId);
}

void CBattleManager::GenerateMonster(bool isBoss, int monsterId)
{
    const FMonsterData* pData = m_pStaticDataManager->GetMonsterData(monsterId);
    if (!pData)
	{
		return;
	}

    delete m_pMonster;
    m_pMonster = new CMonster(pData);
}

void CBattleManager::PlayerTurn()
{
	if (!m_pMonster || !m_pPlayer) 
	{
		return;
	}
	
	m_pMonster->TakeDamage( m_pPlayer->GetAttackValue());

	if (!m_pMonster->IsAlive())
	{
		*m_pPlayer->Get_pExp() += static_cast<CMonster*>(m_pMonster)->GetExpReward();

		if (*m_pPlayer->Get_pExp() >= 100)
		{
			while (*m_pPlayer->Get_pExp() >= 100)
			{
				*m_pPlayer->Get_pLevel() += 1;
				*m_pPlayer->Get_pExp() -= 100;
			}
			*m_pPlayer->Get_pHealth() = *m_pPlayer->Get_pHealthMax();
		}
	}
}

void CBattleManager::MonsterTurn()
{
	if (!m_pMonster || !m_pPlayer) 
	{
		return;
	}

	m_pPlayer->TakeDamage(m_pMonster->GetAttackValue());

	if (*m_pPlayer->Get_pHealth() < 0)
	{
		*m_pPlayer->Get_pHealth() = 0;
	}
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

	if (nextActor == m_pPlayer)
	{
		PlayerTurn();
		return !IsAlive(*m_pMonster->Get_pHealth());
	}
	else if (nextActor == m_pMonster)
	{
		MonsterTurn();
		return !IsAlive(*m_pPlayer->Get_pHealth());
	}
    return true;
}

CBattleAbleObject* CBattleManager::GetCurrentTurn()
{
    return m_turnSelector ? m_turnSelector->GetNextTurn() : nullptr;
}