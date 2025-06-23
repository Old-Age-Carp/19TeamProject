// Copyright Epic Games, Inc. All Rights Reserved.
#include "..\Public\CGameManager.h"
#include "CShopManager.h"
#include "..\Public\CLogManager.h"

CGameManager* CGameManager::instance = nullptr;

CGameManager::CGameManager()
{
	m_pShopManager = CShopManager::GetInstance();

	//m_pLogManager 

}

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
