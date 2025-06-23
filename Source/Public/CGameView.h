#pragma once
#include <vector>
#include "CPrinter.h"
#include "CLogManager.h"
#include "CGameManager.h"

/// <summary>
/// 게임관련 입출력을 담당하는 클래스
/// </summary>
class CGameView
{

public:
	void ViewLogs(const std::vector<std::unique_ptr<ILogable>>& logs);

	void ViewGameState(const CGameManager& gameMgr);

};

