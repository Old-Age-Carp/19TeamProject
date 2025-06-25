#include "..\Public\CShopManager.h"

#include "..\Public\CStaticDataManager.h"
#include "..\Public\CPrinter.h"
#include		"define.h"
#include "..\Public\CPlayer.h"

CShopManager* CShopManager::instance = nullptr;

CShopManager::CShopManager()
{
	m_pStaticDataManger = &CStaticDataManager::getInstance();

}

CShopManager::~CShopManager()
{
}

void CShopManager::Show_ShopItem()
{
	m_pStaticDataManger->Print_AllItem();

}

FItemData* CShopManager::Buy_Item(int i_arg , class CPlayer* pPlayer)
{
	FItemData* Select_item = nullptr;
	wchar_t buffer[256];
	int item_value = 0;

	Select_item = m_pStaticDataManger->GetItemData(i_arg);
	
	
	if (Select_item == nullptr)
	{
		swprintf_s(buffer, 256, L"%d 인 상품은 없습니다",i_arg);
		CPrinter::PrintLine(buffer);

	

	}
	else
	{
		swprintf_s(buffer, 256, L"%ws의 가격은 %d 입니다.", Select_item->name.c_str(), Select_item->value);
		CPrinter::PrintLine(buffer);
	
		item_value = Select_item->value;

		int* Player_gold = pPlayer->Get_pGold();
		if (item_value > *Player_gold)
		{
			swprintf_s(buffer, 256, L"골드가 부족합니다.");
			CPrinter::PrintLine(buffer);
		}
		else
		{
			*Player_gold -= item_value;
			//pPlayer->Add_Inventory(Select_item);
			//CItem* pCItem
			pPlayer->Add_Inventory_FItemData(Select_item);
		}

		return Select_item;
	}
	return nullptr;
}



CShopManager* CShopManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CShopManager();
	}
	return instance;
}

void CShopManager::DestroyInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}
