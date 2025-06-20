// Copyright Epic Games, Inc. All Rights Reserved.
#include "..\Public\CGameManager.h"
CGameManager* CGameManager::instance = nullptr;

CGameManager::~CGameManager()
{
}

CGameManager* CGameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CGameManager();
	}
	return instance;
}

void CGameManager::DestroyInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void CGameManager::Main()
{
	switch (m_eGameState)
	{
	case EGameState::START:
		CreateHero();
		break;
	case EGameState::IDLE:
		break;
	case EGameState::BATTLE:
		break;
	case EGameState::SELECT:
		break;
	case EGameState::SHOP:
		break;
	case EGameState::LEVELUP:
		break;
	case EGameState::INVENTORY:
		break;
	case EGameState::GAMEOVER:
		break;
	case EGameState::END:
		DestroyInstance();
		break;
	default:

		break;
	}
}

void CGameManager::CreateHero()
{
	cout << "캐릭터의 이름 입력:" << endl;

	//이름받고 플레이어 클래스 만들기

	Set_GameState(EGameState::SELECT); 
	
}

void CGameManager::SelectMenu()
{
}

void CGameManager::goBattle()
{
}

void CGameManager::goShop()
{
}

void CGameManager::goInvetory()
{
}

void CGameManager::SeleteMenu()
{
}
