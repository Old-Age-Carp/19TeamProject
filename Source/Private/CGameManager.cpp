// Copyright Epic Games, Inc. All Rights Reserved.
#include "..\Public\CGameManager.h"
#include "CShopManager.h"
#include "..\Public\CLogManager.h"
#include "..\Public\CPlayer.h"
#include "..\Public\CPrinter.h"

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
	case EGameState::STATUS:
		goStatus();
		break;

	case EGameState::BATTLE:
		break;
	case EGameState::SELECT:
		SelectMenu();
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
	std::wstring PlayerName;
	CPrinter::PrintLine(L"캐릭터 이름을 입력하세요 : ");
	std::wcin >> PlayerName;
	//cout << "캐릭터의 이름 입력:" << endl;

	m_pPlayer = new CPlayer(PlayerName);

	std::wstring testName = m_pPlayer->getName();
	CPrinter::PrintLine(testName);
	//이름받고 플레이어 클래스 만들기

	Set_GameState(EGameState::SELECT); 
	
}

void CGameManager::SelectMenu()
{
	CPrinter::ClearScreen();

	CPrinter::PrintLine(L"1: 현재정보 보기 ");
	CPrinter::PrintLine(L"2: 상점  ");
	CPrinter::PrintLine(L"3: 장비창 ");
	CPrinter::PrintLine(L"4: 사냥시작 ");
	CPrinter::PrintLine(L"5: 게임종료");

	int i_select = 0;
	CPrinter::PrintLine(L"원하시는 번호 입력:");
	std::cin >> i_select;

	switch (i_select)
	{
	case 1:
		m_eGameState = EGameState::STATUS;
		break;
	case 2:
		m_eGameState = EGameState::SHOP;
		break;
	case 3:
		m_eGameState = EGameState::INVENTORY;
		break;
	case 4:
		m_eGameState = EGameState::BATTLE;
		break;
	case 5:
		m_eGameState = EGameState::GAMEOVER;
		break;
	}
}

void CGameManager::goStatus()
{

	CPrinter::ClearScreen();

	std::wstring testname = m_pPlayer->getName();
	wchar_t buffer[256];
	swprintf_s(buffer, 256, L"이름: %ws", testname.c_str());
	CPrinter::PrintLine(L"테스트 출력");
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"체력: %d", m_pPlayer->getHealth());
	CPrinter::PrintLine(buffer);
	CPrinter::PrintLine(L"마무리");

	CPrinter::PrintLine(L"\nEnter를 눌러서 계속...");
	std::cin.get();  // Enter 키까지 대기
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


