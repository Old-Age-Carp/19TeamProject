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
	case EGameState::VIEWALLLOG:
		goViewAllLog();
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
	//*(m_pPlayer->Get_pHealth()) = 20;

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
	CPrinter::PrintLine(L"5: 모든로그보기");
	CPrinter::PrintLine(L"6: 게임종료");

	
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
		Set_GameState(EGameState::VIEWALLLOG);
		break;

	case 6:
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
	wchar_t buffer[256];

	//플레이어 상태

	// 몬스터 생성중
	CPrinter::PrintLine(L"몬스터 생성 중");

	// 레벨에 맞는 데이터 가져와서 확인
	// 몬스터 생성
	MakeMonster();

	vector<CBattleAbleObject*> allyMembers{ m_pPlayer };
	vector<CBattleAbleObject*> enemyMembers{ m_pMonster };
	// 몬스터 스텟 출력
	// 전투 시작 입력 대기
	CBattleManager& battleManager = CBattleManager::getInstance();

	CGameView::getInstance().ViewObjectStat(*static_cast<CGameObject*>(m_pMonster));

	Stanby_enter();

	// 전투 진행 준비
	battleManager.SetBattle(std::make_unique<CBattleTurnSelectorEachTurn>(),
		std::make_shared<CIsBattleAble>(allyMembers),
		std::make_shared<CIsBattleAble>(enemyMembers));
	// 종료 될 때까지 반복
	battleManager.NextTurn();
	do
	{
		// 전투로그 관리하여 출력
		CPrinter::ClearScreen();
		swprintf_s(buffer, 256, L"전투 진행 중! vs %s", m_pMonster->getName().c_str());
		CPrinter::PrintLine(buffer);
		CGameView::getInstance().ViewLogs(battleManager.GetBattleLog());
		Sleep(500);	// 0.5초 간격 대기
	} while (battleManager.NextTurn());

	// 전체로그에 전투 로그 추가
	for (auto& log : battleManager.GetBattleLog())
	{
		CLogManager::getInstance().AddLog(std::make_unique<LogWString>(log->ToString()));
	}
	
	if (m_pPlayer->IsAlive() == false)
	{
		CPrinter::PrintLine(L"사망하셨습니다.");
		Set_GameState(EGameState::GAMEOVER);
	}
	else
	{
		CPrinter::PrintLine(L"승리!");

	}


	(*m_pPlayer->Get_pExp()) += m_pMonster->GetExpReward();
	swprintf_s(buffer, 256, L"%d 경험치 획득 ,현재경험치 %d / 100", m_pMonster->GetExpReward(), m_pMonster->GetExpReward());
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);
	m_pPlayer->LevelUp();	//레벨업 시도

	// 레벨업 했는지 확인

	// 종료시 결과 출력
	// 아이템 드롭
	int dropGold = 0;
	vector<CItem> drops = DropItem(m_pMonster, dropGold);
	if (drops.size() > 0)
	{
		swprintf_s(buffer, 256, L"%d 골드 획득", dropGold);
		CPrinter::PrintLine(buffer);
		CLogManager::getInstance().AddLog(buffer);

		swprintf_s(buffer, 256, L"%d 경험치 획득", m_pMonster->GetExpReward());
		CPrinter::PrintLine(buffer);
		CLogManager::getInstance().AddLog(buffer);
	}

	for (CItem item : drops)
	{
		m_pPlayer->Add_Inventory(new CItem(item));

		swprintf_s(buffer, 256, L"[아이템 획득 : %ws \t %d 개]", item.GetName().c_str(), item.GetCurrentStack());
		CPrinter::PrintLine(buffer);
		CLogManager::getInstance().AddLog(buffer);
	}

	// 몬스터 메모리 해재
	delete m_pMonster;
	m_pMonster = nullptr;



	CPrinter::PrintLine(L"이어서 전투하시겠습니까? (Y/N)");
	wstring input = GetInput<wstring>();
	// 이어서 전투한다면 상태변경하지 않고 탈출
	if (input == L"n" or input == L"N")
	{
		Set_GameState(EGameState::SELECT);
	}
}

void CGameManager::goShop()
{
	wchar_t buffer[256];
	int i_select = 0,i_stock;

	CPrinter::ClearScreen();
	m_pShopManager->Show_ShopItem();

	swprintf_s(buffer, 256, L"현재 골드 : %d", *m_pPlayer->Get_pGold());
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);

	swprintf_s(buffer, 256, L"구매할 아이템 ID 입력: (메뉴:9,판매:10)");
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);
	i_select = GetInput<int>();


	if (i_select == 9)
	{
		Set_GameState(EGameState::SELECT);
	}
	else if (i_select == 10)
	{
		m_pPlayer->Show_Inventory();

		swprintf_s(buffer, 256, L"판매할 아이템 ID 입력: (취소:9)");
		CPrinter::PrintLine(buffer);
		CLogManager::getInstance().AddLog(buffer);
		i_select = GetInput<int>();
		swprintf_s(buffer, 256, L"판매할 아이템의 갯수: (취소:9)");
		CPrinter::PrintLine(buffer);
		CLogManager::getInstance().AddLog(buffer);
		i_stock= GetInput<int>();

		m_pPlayer->Sell_item(i_select,i_stock);
	}
	else {
		swprintf_s(buffer, 256, L"구매할 아이템의 갯수: (취소:9)");
		CPrinter::PrintLine(buffer);
		CLogManager::getInstance().AddLog(buffer);
		i_stock = GetInput<int>();
		FItemData* Buyed_item = m_pShopManager->Buy_Item(i_select,m_pPlayer, i_stock);
		Stanby_enter();
	}


}

void CGameManager::goViewAllLog()
{
	CPrinter::PrintLine(L"모든 로그 출력");
	CPrinter::ClearScreen();
	CGameView::getInstance().ViewLogs(CLogManager::getInstance().GetLogs());
	CPrinter::Pause();


	Set_GameState(EGameState::SELECT);
}

void CGameManager::goInvetory()
{
	int i_select = 0;

	wchar_t buffer[256];
	wstring testname = m_pPlayer->getName();

	m_pPlayer->Show_Inventory();


	swprintf_s(buffer, 256, L"이름: %ws", testname.c_str());
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);
	swprintf_s(buffer, 256, L"공격력: %d", *m_pPlayer->Get_pAttack());
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);
	swprintf_s(buffer, 256, L"방어력: %d", *m_pPlayer->Get_pArmor());
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);
	swprintf_s(buffer, 256, L"체력: %d / %d", m_pPlayer->getHealth(), *m_pPlayer->Get_pHealthMax());
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);
	swprintf_s(buffer, 256, L"골드: %d ", *m_pPlayer->Get_pGold());
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);





	swprintf_s(buffer, 256, L"사용하거나 장착할 아이템 ID: %d, (메뉴:9)", i_select);
	CPrinter::PrintLine(buffer);
	CLogManager::getInstance().AddLog(buffer);
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

	swprintf_s(buffer, 256, L"게임을 클리어했습니다.");
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
		bool LevelUp_result = m_pPlayer->LevelUp();

		wchar_t buffer[256];
		swprintf_s(buffer, 256, L"레벨업!  %d  -> %d", pre_level, m_pPlayer->getLevel());
		CPrinter::PrintLine(buffer);
		swprintf_s(buffer, 256, L"공격력:  %d  -> %d", pre_attack, m_pPlayer->getAttack());
		CPrinter::PrintLine(buffer);
		swprintf_s(buffer, 256, L"체력:  %d  -> %d", pre_health, m_pPlayer->getHealth_Max());
		CPrinter::PrintLine(buffer);
		if (LevelUp_result == true)
		{
			CPrinter::Pause();
			Set_GameState(EGameState::GAMEOVER);
			//게임클리어
		}

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

void CGameManager::Show_LevelUp()
{
	int pre_level = 0, pre_attack = 0, pre_health = 0;


	pre_level = *m_pPlayer->Get_pLevel();
	pre_attack = *m_pPlayer->Get_pAttack();
	pre_health = m_pPlayer->getHealth_Max();
	//bool LevelUp_result = m_pPlayer->LevelUp();

	wchar_t buffer[256];
	swprintf_s(buffer, 256, L"레벨업!  %d  -> %d", pre_level, m_pPlayer->getLevel());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"공격력:  %d  -> %d", pre_attack, m_pPlayer->getAttack());
	CPrinter::PrintLine(buffer);
	swprintf_s(buffer, 256, L"체력:  %d  -> %d", pre_health, m_pPlayer->getHealth_Max());
	CPrinter::PrintLine(buffer);

}

void CGameManager::Stanby_enter()
{
	//CPrinter::PrintLine(L"\nEnter를 눌러서 계속...");
	CPrinter::Pause();
}

//몬스터 생성
void CGameManager::MakeMonster()
{
	EMonsterType type = m_pPlayer->getLevel() == MaxPlayerLevel ? EMonsterType::Boss : EMonsterType::Normal;

	const vector<FMonsterData>& monsterDatas = m_pStaticDataManager->GetAllMonsterDatas();
	int randomIndex = std::rand() % monsterDatas.size();
	int id = monsterDatas[randomIndex].id;
	m_pMonster = new CMonster(m_pStaticDataManager->GetMonsterData(id));

	int level = m_pPlayer->getLevel();
	// 공격력: (레벨 × 5) ~ (레벨 × 10)
	// 체력·공격력은 기존 몬스터의 1.5배 범위를 랜덤으로 설정!
	int attack = level * (rand() % 5 + 5);
	// 체력: (레벨 × 20) ~ (레벨 × 30)
	int health = level * (rand() % 10 + 20);

	if (type == EMonsterType::Boss)
	{
		float multiple = (static_cast<float>(rand()) / RAND_MAX) * 0.5f + 1.0f;
		attack = (float)attack * multiple;	// 소수점 단위 절삭
	}


	*(m_pMonster->Get_pAttack()) = attack;
	*(m_pMonster->Get_pHealth()) = health;
	*(m_pMonster->Get_pHealthMax()) = health;
	*(m_pMonster->Get_pArmor()) = level;
	*(m_pMonster->Get_pLevel()) = level;

	m_pMonster->SetBattleAI(std::make_unique<CBattleAI>(m_pMonster));
}

//몬스터 처치 후 아이템 드랍
vector<CItem> CGameManager::DropItem(CMonster* monster, int& outDropGolds)
{
	vector<CItem> droppedCItems;

	//오류검사
	if (!monster)
		return droppedCItems;

	const FMonsterData* pMonsterData = monster->GetData();
	if (!pMonsterData)
		return droppedCItems;

	//골드 드랍 100% exp reward의 1~3배 골드 드랍
	outDropGolds = rand() % (pMonsterData->expReward * 2 + 1) + pMonsterData->expReward;

	const vector<int> dropTableIds = pMonsterData->dropItemTableIDs;

	if (pMonsterData->dropItemTableIDs.empty())
	{
		return droppedCItems;
	}

	for (int itemID : pMonsterData->dropItemTableIDs)
	{
		const FGameDropTable* dropData = m_pStaticDataManager->GetDropTable(itemID);
		const FDropItemData& data = dropData->possibleDrops;

		for (int i = 0; i < data.mItemIDList.size(); i++)
		{
			float value = static_cast<float>(std::rand()) / RAND_MAX;
			if (data.mDropRate[i] >= value)
			{
				const FItemData* itemData = m_pStaticDataManager->GetItemData(data.mItemIDList[i]);
				droppedCItems.push_back(CItem(itemData, 1));
			}
		}
	}

	//디버깅 편의성을 위해 존재한대요..보고 삭제여부 확인좀..
	//m_pLogManager->AddLog(L"골드 획득: " + std::to_wstring(droppedGold) + L" 골드를 획득했습니다.");
#pragma region 이전코드
	//아이템 드랍
	//if (!pMonsterData->dropItemTableIDs.empty())
	//{
	//	for (int itemID : pMonsterData->dropItemTableIDs)
	//	{
	//		const FItemData* pItemDef = m_pStaticDataManager->GetItemData(itemID);
	//		if (!pItemDef)
	//		{
	//			m_pLogManager->AddLog(L"  - 알 수 없는 아이템 (ID: " + std::to_wstring(itemID) + L")이 드롭되었으나 데이터에서 찾을 수 없습니다.");
	//			continue;
	//		}

	//		//아이템 드랍 확률
	//		bool bDropped = false;
	//		double dropChance = 0.0; //기본 확률 0

	//		if (dynamic_cast<const FItemPotionData*>(pItemDef))
	//		{
	//			dropChance = 0.3; //포션 30%
	//		}
	//		else if (dynamic_cast<const FItemSpecialData*>(pItemDef) && pItemDef->id == 1234) //그 즉발 아이템! 내용필
	//		{
	//			dropChance = 0.3;
	//		}

	//		if (static_cast<double>(rand()) / RAND_MAX < dropChance)
	//		{
	//			bDropped = true;
	//		}

	//		if (bDropped)
	//		{
	//			if (dynamic_cast<const FItemSpecialData*>(pItemDef) && pItemDef->id == 1234)
	//			{
	//				if (static_cast<double>(rand()) / RAND_MAX < 0.3)
	//				{
	//					//체력 회복
	//					int healAmount = 50;
	//					*(m_pPlayer->Get_pHealth()) += healAmount;
	//					if (*(m_pPlayer->Get_pHealth()) > *(m_pPlayer->Get_pHealthMax()))
	//					{
	//						*(m_pPlayer->Get_pHealth()) = *(m_pPlayer->Get_pHealthMax());
	//					}
	//				}
	//				else
	//				{
	//					//공격력 증가
	//					int attackBonus = 10;
	//					*(m_pPlayer->Get_pAttack()) += attackBonus;
	//				}
	//			}
	//			else
	//			{
	//				m_pPlayer->Add_Inventory(const_cast<FItemData*>(pItemDef));

	//				droppedCItems.emplace_back(pItemDef, 1);
	//			}
	//		}
	//		else
	//		{

	//		}
	//	}
	//}
#pragma endregion
	return droppedCItems;
}

/// <summary>
/// 여태 있었던 모든 로그 출력
/// </summary>
void goLogs()
{
	CPrinter::PrintLine(L"모든 로그 출력");
	CPrinter::ClearScreen();
	CGameView::getInstance().ViewLogs(CLogManager::getInstance().GetLogs());
	CPrinter::Pause();
}
