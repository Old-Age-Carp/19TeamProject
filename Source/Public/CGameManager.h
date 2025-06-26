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
	void Set_GameState(EGameState arg) { m_eGameState = arg; }

	void CreateHero(); //캐릭터생성
	void SelectMenu();
	void goStatus();
	void goBattle();
	void goShop();
	void goInvetory();
	void goGameOver();
	void goLevelUp();

	vector<class CItem> DropItem( CMonster* monster, int& outDropGolds);
	void MakeMonster(); //멤버변수에 할당하도록 수정

	void ShowStatus();
	void Show_LevelUp();
	void Stanby_enter(); //엔터입력 대기
	template<typename T>
	T GetInput();
public:
	static CGameManager*	 GetInstance();
	static void				 DestroyInstance();

	bool* Get_pGameRunning() { return &m_bGameRunning; } //Main에서 돌아갈지말지 체크하는 변수 = 게임클리어
	void Main(); //


	EGameState	GetGameState()			 const { return m_eGameState; }
	void		SetGameState(EGameState state) { m_eGameState = state; }

protected:
	bool		m_bGameRunning = true;
	EGameState	m_eGameState = EGameState::START;


private:
	static CGameManager* instance; //싱글톤 선언
	class CShopManager*			m_pShopManager = nullptr;
	class CLogManager*			m_pLogManager = nullptr;
	class CStaticDataManager*	m_pStaticDataManager = nullptr;
	class CPlayer*				m_pPlayer = nullptr;
	class CMonster*				m_pMonster = nullptr;
	CGameManager(); // 생성자
	~CGameManager(); //소멸자

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
