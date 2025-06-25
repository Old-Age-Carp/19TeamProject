// Copyright Epic Games, Inc. All Rights Reserved.
#include "..\Public\CGameManager.h"
#include "CShopManager.h"
#include "..\Public\CLogManager.h"
#include "..\Public\CPlayer.h"
#include "..\Public\CPrinter.h"
#include "..\Public\CStaticDataManager.h"

#include "CGameView.h"
#include "CBattleManager.h"
#include "CBattleTurnSelectorEachTurn.h"
#include "CMonster.h"

#include "CIsBattleAble.h"

#include <ctime>    // C++ 스타일

using std::wstring;
CGameManager* CGameManager::instance = nullptr;

CGameManager::CGameManager()
{
	m_pShopManager = CShopManager::GetInstance();

	m_pStaticDataManager = &CStaticDataManager::getInstance();
	m_pStaticDataManager->LoadAllStaticData();
	srand(static_cast<unsigned int>(time(nullptr)));
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
		goBattle();
		break;
	case EGameState::SELECT:
		SelectMenu();
		break;
	case EGameState::SHOP:
		goShop();
		break;
	case EGameState::LEVELUP:
		
		break;
	case EGameState::INVENTORY:
		goInvetory();
		break;
	case EGameState::GAMEOVER:
		goGameOver();
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
	wstring PlayerName;
	CPrinter::PrintLine(L"캐릭터 이름을 입력하세요 : ");
	PlayerName = GetInput<wstring>();
	//std::getline(std::wcin, PlayerName);
	//cout << "캐릭터의 이름 입력:" << endl;

	m_pPlayer = new CPlayer(PlayerName);
	m_pPlayer->SetBattleAI(std::make_unique<CBattleAI>(m_pPlayer));
	*(m_pPlayer->Get_pHealth()) = 20;

	ShowStatus();
	Stanby_enter();
	

	Set_GameState(EGameState::SELECT); 
	
}

void CGameManager::SelectMenu()
{
	CPrinter::ClearScreen();

	CPrinter::PrintLine(L"1: 현재정보 보기 ");
	CPrinter::PrintLine(L"2: 상점  ");
	CPrinter::PrintLine(L"3: 인벤토리 ");
	CPrinter::PrintLine(L"4: 사냥시작 ");
	CPrinter::PrintLine(L"5: 게임종료");

	int i_select = 0;
	CPrinter::PrintLine(L"원하시는 번호 입력:");
	//std::wcin >> i_select;
	i_select = GetInput<int>();

	switch (i_select)
	{
	case 1:
		Set_GameState(EGameState::STATUS);
		break;
	case 2:
		Set_GameState(EGameState::SHOP);

		break;
	case 3:
		Set_GameState(EGameState::INVENTORY);

		break;
	case 4:
		Set_GameState(EGameState::BATTLE);

		break;
	case 5:
		Set_GameState(EGameState::GAMEOVER);

		break;
	}
}

void CGameManager::goStatus()
{

	CPrinter::ClearScreen();


	ShowStatus();

	Stanby_enter();

	Set_GameState(EGameState::SELECT);

}
void CGameManager::goBattle()
{
	//플레이어 상태

	// 몬스터 생성중
	CPrinter::PrintLine(L"몬스터 생성 중");

	// 레벨에 맞는 데이터 가져와서 확인
	// 몬스터 생성
	CMonster* monster = MakeMonster(EMonsterType::Normal);
	// 몬스터 스텟 출력
	// 전투 시작 입력 대기
	//CBattleManager& battleManager = CBattleManager::getInstance();

	CGameView::getInstance().ViewObjectStat(*static_cast<CGameObject*>(monster));

	Stanby_enter();

	// 전투 진행 준비
	//battleManager.SetBattle(std::make_unique<CBattleTurnSelectorEachTurn>());

	
	// 로그 출력
	//while (battleManager.NextTurn())
	//{
	//	
	//}

	// 기다리기

	// 종료 될 때까지 반복

	// 종료시 결과 출력

}

void CGameManager::goShop()
{
	wchar_t buffer[256];
	int i_select = 0;

	CPrinter::ClearScreen();
	m_pShopManager->Show_ShopItem();

	swprintf_s(buffer, 256, L"현재 골드 : %d", *m_pPlayer->Get_pGold());
	CPrinter::PrintLine(buffer);

	swprintf_s(buffer, 256, L"구매할 아이템 ID 입력: %d, (메뉴:9)", i_select);
	CPrinter::PrintLine(buffer);

	i_select = GetInput<int>();
	if (i_select == 9)
	{
		Set_GameState(EGameState::SELECT);
	}
	else {
		FItemData* Buyed_item = m_pShopManager->Buy_Item(i_select,m_pPlayer);
		Stanby_enter();
	}


}

void CGameManager::goInvetory()
{
	int i_select = 0;

	wchar_t buffer[256];
	wstring testname = m_pPlayer->getName();

	m_pPlayer->Show_Inventory();


	swprintf_s(buffer, 256, L"이름: %ws", testname.c_str());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"공격력: %d", *m_pPlayer->Get_pAttack());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"방어력: %d", *m_pPlayer->Get_pArmor());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"체력: %d / %d", m_pPlayer->getHealth(), *m_pPlayer->Get_pHealthMax());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"골드: %d ", *m_pPlayer->Get_pGold());
	CPrinter::PrintLine(buffer);





	swprintf_s(buffer, 256, L"사용하거나 장착할 아이템 ID: %d, (메뉴:9)", i_select);
	CPrinter::PrintLine(buffer);
	//Stanby_enter();
	//i_select = GetInput
	i_select = GetInput<int>();
	if (i_select == 9)
	{
		Set_GameState(EGameState::SELECT);
	}
	else
	{
		m_pPlayer->Equip(i_select);
		Stanby_enter();
	}

}

void CGameManager::goGameOver()
{
	wchar_t buffer[256];

	swprintf_s(buffer, 256, L"게임오버입니다");
	CPrinter::PrintLine(buffer);

	Stanby_enter();

	m_bGameRunning = false;
}

void CGameManager::goLevelUp()
{
	int pre_level = 0, pre_attack = 0 ,pre_health=0;

	if (*m_pPlayer->Get_pExp() >= 100)
	{
		pre_level = *m_pPlayer->Get_pLevel();
		pre_attack = *m_pPlayer->Get_pAttack();
		pre_health  = m_pPlayer->getHealth_Max();
		m_pPlayer->LevelUp();


		wchar_t buffer[256];
		swprintf_s(buffer, 256, L"레벨업!  %d  -> %d", pre_level, m_pPlayer->getLevel());
		CPrinter::PrintLine(buffer);
		swprintf_s(buffer, 256, L"공격력:  %d  -> %d", pre_attack, m_pPlayer->getAttack());
		CPrinter::PrintLine(buffer);
		swprintf_s(buffer, 256, L"체력:  %d  -> %d", pre_health, m_pPlayer->getHealth_Max());
		CPrinter::PrintLine(buffer);

	}

}

void CGameManager::ShowStatus()
{
	wstring testname = m_pPlayer->getName();

	wchar_t buffer[256];
	swprintf_s(buffer, 256, L"이름: %ws", testname.c_str());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"레벨: %d", m_pPlayer->getLevel());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"경험치: %d  / 100", *m_pPlayer->Get_pExp());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"공격력: %d", *m_pPlayer->Get_pAttack());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"방어력: %d", *m_pPlayer->Get_pArmor());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"체력: %d / %d", m_pPlayer->getHealth(), *m_pPlayer->Get_pHealthMax());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"골드: %d ", *m_pPlayer->Get_pGold());
	CPrinter::PrintLine(buffer);

}

void CGameManager::Stanby_enter()
{
	//CPrinter::PrintLine(L"\nEnter를 눌러서 계속...");
	CPrinter::Pause();
}

//몬스터 생성
CMonster* CGameManager::MakeMonster(EMonsterType type)
{
	vector<int> monsterIDs;
	if (type == EMonsterType::Boss)
	{
		monsterIDs = { 107, 108 }; //리치 드래곤
	}
	else
	{
		monsterIDs = { 101, 102, 103, 104, 105, 106 };
	}

	if (monsterIDs.empty())
	{
	}
	return nullptr;
}

//몬스터 처치 후 아이템 드랍
vector<CItem> CGameManager::DropItem(CMonster* monster)
{
	vector<CItem> droppedCItems;

	//오류검사
	if (!monster)
		return droppedCItems;

	const FMonsterData* pMonsterData = monster->GetData();
	if (!pMonsterData)
		return droppedCItems;

	//골드 드랍 100% exp reward의 1~3배 골드 드랍
	int droppedGold = rand() % (pMonsterData->expReward * 2 + 1) + pMonsterData->expReward;
	*(m_pPlayer->Get_pGold()) += droppedGold;
	//디버깅 편의성을 위해 존재한대요..보고 삭제여부 확인좀..
	//m_pLogManager->AddLog(L"골드 획득: " + std::to_wstring(droppedGold) + L" 골드를 획득했습니다.");

	//아이템 드랍
	if (!pMonsterData->dropItemTableIDs.empty())
	{
		for (int itemID : pMonsterData->dropItemTableIDs)
		{
			const FItemData* pItemDef = m_pStaticDataManager->GetItemData(itemID);
			if (!pItemDef)
			{
				m_pLogManager->AddLog(L"  - 알 수 없는 아이템 (ID: " + std::to_wstring(itemID) + L")이 드롭되었으나 데이터에서 찾을 수 없습니다.");
				continue;
			}

			//아이템 드랍 확률
			bool bDropped = false;
			double dropChance = 0.0; //기본 확률 0

			if (dynamic_cast<const FItemPotionData*>(pItemDef))
			{
				dropChance = 0.3; //포션 30%
			}
			else if (dynamic_cast<const FItemSpecialData*>(pItemDef) && pItemDef->id == 1234) //그 즉발 아이템! 내용필
			{
				dropChance = 0.3;
			}

			if (static_cast<double>(rand()) / RAND_MAX < dropChance)
			{
				bDropped = true;
			}

			if (bDropped)
			{
				if (dynamic_cast<const FItemSpecialData*>(pItemDef) && pItemDef->id == 1234)
				{
					if (static_cast<double>(rand()) / RAND_MAX < 0.3)
					{
						//체력 회복
						int healAmount = 50;
						*(m_pPlayer->Get_pHealth()) += healAmount;
						if (*(m_pPlayer->Get_pHealth()) > *(m_pPlayer->Get_pHealthMax()))
						{
							*(m_pPlayer->Get_pHealth()) = *(m_pPlayer->Get_pHealthMax());
						}
					}
					else
					{
						//공격력 증가
						int attackBonus = 10;
						*(m_pPlayer->Get_pAttack()) += attackBonus;
					}
				}
				else
				{
					m_pPlayer->Add_Inventory(const_cast<FItemData*>(pItemDef));

					droppedCItems.emplace_back(pItemDef, 1);
				}
			}
			else
			{

			}
		}
	}
	return droppedCItems;
}
