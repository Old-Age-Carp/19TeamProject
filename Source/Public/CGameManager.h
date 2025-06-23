// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "define.h"

//이준식 작업
class CGameManager
{
private:
	class CShopManager*		m_pShopManager	= nullptr;
	class CLogManager*		m_pLogManager	= nullptr;
	static CGameManager* instance; //싱글톤 선언

	CGameManager(); // 생성자
	~CGameManager(); //소멸자


private:

	void CreateHero(); //캐릭터생성
	void SelectMenu();
	void goBattle();
	void goShop();
	void goInvetory();
	void SeleteMenu();

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

