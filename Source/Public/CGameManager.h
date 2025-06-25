// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "define.h"
///#include <iostream>
#include <memory>

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
	class CStaticDataManager*	m_pStaticDataManger = nullptr;
	class CPlayer* m_pPlayer = nullptr;
	class std::unique_ptr<class CGameView> m_pView = nullptr;
	CGameManager(); // 생성자
	~CGameManager(); //소멸자


private:

	void CreateHero(); //캐릭터생성
	void SelectMenu();
	void goStatus();
	void goBattle();
	void goShop();
	void goInvetory();
	void goLevelUp();

	vector<class CItem> DropItem(class CMonster* monster);
	CMonster* MakeMonster(EMonsterType type);

	void ShowStatus();
	void Stanby_enter(); //엔터입력 대기
	void Set_GameState(EGameState arg) { m_eGameState = arg; }
public:
	static CGameManager* GetInstance();
	static void				DestroyInstance();

	void Main(); //


	EGameState	GetGameState()			 const { return m_eGameState; }
	void		SetGameState(EGameState state) { m_eGameState = state; }

protected:
	EGameState	m_eGameState = EGameState::START;


};

