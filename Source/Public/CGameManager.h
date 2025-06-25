// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "define.h"
#include "CMonster.h"
///#include <iostream>
#include <memory>
#include <optional>
#include "CPrinter.h"

class CPlayer;
//class CStaticDataManager;

//이준식 작업
class CGameManager
{
private:
	static CGameManager* instance; //싱글톤 선언
	//class CPrinter*			m_pPrinter = nullptr;

	class CShopManager*			m_pShopManager		= nullptr;
	class CLogManager*			m_pLogManager		= nullptr;
	//class CStaticDataManager	m_pStaticDataManger;
	class CStaticDataManager*	m_pStaticDataManager = nullptr;
	class CPlayer* m_pPlayer = nullptr;
	std::unique_ptr<class CIsBattleAble> m_pPlayerTeam = nullptr;
	
	CGameManager(); // 생성자
	~CGameManager(); //소멸자


private:

	void CreateHero(); //캐릭터생성
	void SelectMenu();
	void goStatus();
	void goBattle();
	void goShop();
	void goInvetory();
	void goGameOver();
	void goLevelUp();

	vector<class CItem> DropItem( CMonster* monster);
	CMonster* MakeMonster(EMonsterType type);

	void ShowStatus();
	void Stanby_enter(); //엔터입력 대기
	template<typename T>
	T GetInput();
	void Set_GameState(EGameState arg) { m_eGameState = arg; }
public:
	static CGameManager* GetInstance();
	static void				DestroyInstance();

	bool* Get_pGameRunning() { return &m_bGameRunning; }
	void Main(); //


	EGameState	GetGameState()			 const { return m_eGameState; }
	void		SetGameState(EGameState state) { m_eGameState = state; }

protected:
	bool		m_bGameRunning = true;
	EGameState	m_eGameState = EGameState::START;


};

template<typename T>
T CGameManager::GetInput()
{
	std::optional<T> retOpt = std::nullopt;
	while (true)
	{
		retOpt = CPrinter::GetInput<T>();
		if (retOpt.has_value() == false)
		{
			CPrinter::PrintLine(L"잘못 된 입력입니다 다시 입력해주세요.");
		}
		else break;
	}

	return retOpt.value();
}
