#pragma once

#include <memory>
#include <vector>
#include "TSingleton.h"
#include "CBattleAbleObject.h"
#include "CStaticDataManager.h"
#include "IBattleTurnSelector.h"
#include "CLogManager.h"

class CBattleManager : public TSingleton<CBattleManager>
{
public:
	CBattleManager() = default;

	void SetBattle(std::unique_ptr<IBattleTurnSelector> turnSelector,
		std::shared_ptr<CBattleTeam> team1, std::shared_ptr<CBattleTeam> team2);
	bool IsAlive(int health) const { return health > 0; };
	bool NextTurn();				// 턴 넘기기 + 전투 종료 여부 반환
    CBattleAbleObject* GetCurrentTurn();	// 현재 턴 주체 반환
	ILogable* GetCurrentLog() { return &m_BattleLog.back(); }
	const std::vector<ILogable*> GetBattleLog();

private:
	std::vector<LogWString>	m_BattleLog;
	std::shared_ptr<CBattleTeam> m_pPlayer = nullptr;
	std::shared_ptr<CBattleTeam> m_pMonster = nullptr;
	CStaticDataManager* m_pStaticDataManager = nullptr;
	std::unique_ptr<IBattleTurnSelector> m_turnSelector;
	bool m_bIsBossBattle = false;
	int* m_pMonsterId = nullptr;
};
