#include "..\Public\CBattleManager.h"
#include "..\Public\CMonster.h"
#include "..\Public\CGameObject.h"
#include "..\Public\CBattleAI.h"
#include "CIsBattleAble.h"
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cwchar>

void CBattleManager::SetBattle(std::unique_ptr<IBattleTurnSelector> turnSelector,
	std::shared_ptr<CIsBattleAble> team1,
	std::shared_ptr<CIsBattleAble> team2)
{
	m_turnSelector = std::move(turnSelector);
	vector<shared_ptr<CIsBattleAble>> teams;
	teams.push_back(std::shared_ptr<CIsBattleAble>(team1));
	teams.push_back(std::shared_ptr<CIsBattleAble>(team2));
	m_turnSelector->SetTeams(teams);
	m_pPlayer = team1;
	m_pMonster = team2;

	if (m_pPlayer == nullptr || m_pMonster == nullptr)
	{
		return;
	}

	m_BattleLog.clear();

	//std::srand(static_cast<unsigned int>(std::time(nullptr)));

 //   
	//if (*(static_cast<CGameObject*>(m_pPlayer)->Get_pLevel()) >= 10)
 //   {	
	//	int BossIds[] = { 107, 108 };
 //   	int numBosses = static_cast<int>(std::size(BossIds));
 //       *m_pMonsterId = BossIds[rand() % numBosses];
 //       m_bIsBossBattle = true;
 //   }
 //   else
 //   {
 //       int normalMonsterMinId = 101;
 //       int normalMonsterMaxId = 106;

 //       int normalRange = normalMonsterMaxId - normalMonsterMinId + 1;
 //       *m_pMonsterId = normalMonsterMinId + rand() % normalRange;
 //       m_bIsBossBattle = false;
 //   }
	//GenerateMonster(m_bIsBossBattle, *m_pMonsterId);
}

//void CBattleManager::PlayerTurn()
//{
//	if (!m_pMonster || !m_pPlayer) 
//	{
//		return;
//	}
//	
//	m_pMonster->TakeDamage( m_pPlayer->GetAttackValue());
//
//	if (!m_pMonster->IsAlive())
//	{
//		*m_pPlayer->Get_pExp() += static_cast<CMonster*>(m_pMonster)->GetExpReward();
//
//		if (*m_pPlayer->Get_pExp() >= 100)
//		{
//			while (*m_pPlayer->Get_pExp() >= 100)
//			{
//				*m_pPlayer->Get_pLevel() += 1;
//				*m_pPlayer->Get_pExp() -= 100;
//			}
//			*m_pPlayer->Get_pHealth() = *m_pPlayer->Get_pHealthMax();
//		}
//	}
//}

bool CBattleManager::NextTurn()
{	
	if (!m_turnSelector)
	{
        return true;
	}

 	CBattleAbleObject* nextActor = m_turnSelector->GetNextTurn();
	if (!nextActor)
	{
		return false;
	}
	// 선택된 actor 의 팀
	CIsBattleAble* turnOtherTeam = nullptr;
	const vector<CBattleAbleObject*>& playerMember = m_pPlayer->GetTeamBattlerList();
	if (std::find(playerMember.begin(), playerMember.end(), nextActor) != playerMember.end())
	{
		turnOtherTeam = m_pMonster.get();
	}
	else
	{
		turnOtherTeam = m_pPlayer.get();
	}

	EActionKind action = nextActor->GetAI().Think();
	CBattleAbleObject* target = nextActor->GetAI().ThinkTarget(action, vector<CIsBattleAble*>{turnOtherTeam});


	wchar_t buffer[256];

	switch (action)
	{
	case EActionKind::Attack:
	{
		int damage = nextActor->GetAttackValue();
		target->TakeDamage(damage);
		swprintf_s(buffer, 256, L"%ws 이가 %ws 에게 공격 %d 대미지!",
			nextActor->getName().c_str(), target->getName().c_str(), damage);
		m_BattleLog.push_back(LogWString(buffer));

		if (target->IsAlive() == false)
		{
			swprintf_s(buffer, 256, L"%ws 사망했다!",target->getName().c_str());
			m_BattleLog.push_back(LogWString(buffer));
		}
	}
		break;
	case EActionKind::UseItem:
	{
		// 사용 가능한 아이템만 들어있음
		vector<CItem*> items = nextActor->GetHaveItems();
		if (items.size() > 0)
		{
			// 사용할 수 있는 아이템들 중에서 랜덤하게 하나 사용.
			int randomIndex = rand() % items.size();
			CItem* useItem = items[randomIndex];
			swprintf_s(buffer, 256, L"아이템 %ws 사용!", useItem->GetName().c_str());
			m_BattleLog.push_back(LogWString(buffer));
			nextActor->UseItem(useItem);
		}
	}
		break;
	default:
		break;
	}

	if ((m_pPlayer->IsAvailable() and m_pMonster->IsAvailable()) == false)
		return false;
	
    return true;
}

//void CBattleManager::MonsterTurn(const std::vector<CIsBattleAble*>& otherTeams)
//{
//    if (!m_pMonster || !m_pPlayer)
//	{
//		return;
//	}
//		
//    CBattleAI ai(m_pMonster);
//    EActionKind action = ai.Think();
//    CBattleAbleObject* target = ai.ThinkTarget(action, otherTeams);
//
//    if (!target) return;
//
//    if (action == EActionKind::Attack)
//	{
//		target->TakeDamage(m_pMonster->GetAttackValue());
//	}
//	
//	if (*m_pPlayer->Get_pHealth() < 0)
//	{
//		*m_pPlayer->Get_pHealth() = 0;
//	}
//}

CBattleAbleObject* CBattleManager::GetCurrentTurn()
{
    return m_turnSelector ? m_turnSelector->GetNextTurn() : nullptr;
}

const std::vector<ILogable*> CBattleManager::GetBattleLog()
{
	std::vector<ILogable*> retVector = {};

	for (LogWString& log : m_BattleLog)
	{
		retVector.push_back(static_cast<ILogable*>(&log));
	}

	return retVector;
}
