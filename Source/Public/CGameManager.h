// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "define.h"
#include <iostream>


using namespace std;

//이준식 작업
class CGameManager
{
private:
	static CGameManager* instance; //싱글톤 선언

	void CreateHero(); //캐릭터생성
	void SelectMenu();
	void goBattle();
	void goShop();
	void goInvetory();
	void SeleteMenu();

	void Set_GameState(EGameState arg) { m_eGameState = arg; }
public:

	~CGameManager(); //소멸자
	static CGameManager*	GetInstance();
	static void				DestroyInstance();
	void Main(); //




protected:
	EGameState	m_eGameState = EGameState::END;


};

