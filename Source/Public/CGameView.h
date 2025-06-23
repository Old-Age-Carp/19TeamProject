#pragma once
#include <vector>
#include "CPrinter.h"
#include "CLogManager.h"
#include "CGameManager.h"
#include "CGameObject.h"

/// <summary>
/// 게임관련 출력을 담당하는 클래스 일종의 UI 역할
/// </summary>
class CGameView
{

public:
	void ViewLogs(const std::vector<std::unique_ptr<ILogable>>& logs);

	void ViewGameState(const CGameManager& gameMgr);

	void ViewObjectStat(const CGameObject& stat);

	void ViewRequireInputFor(const EGameState state);
};

