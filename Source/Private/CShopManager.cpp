#include "..\Public\CShopManager.h"

#include "..\Public\CStaticDataManager.h"
#include "..\Public\CPrinter.h"
#include		"define.h"
#include "..\Public\CPlayer.h"
#include "..\Public\CLogManager.h"

CShopManager* CShopManager::instance = nullptr;

CShopManager::CShopManager()
{
	m_pStaticDataManager = &CStaticDataManager::getInstance();

}

CShopManager::~CShopManager()
{
}

void CShopManager::Show_ShopItem()
{
	m_pStaticDataManager->Print_AllItem();

}

FItemData* CShopManager::Buy_Item(int i_arg ,class CPlayer* pPlayer, int item_stock)
{
	FItemData* Select_item = nullptr;
	wchar_t buffer[256];
	int item_value = 0;

	Select_item = m_pStaticDataManager->GetItemData(i_arg);
	
	
	if (Select_item == nullptr)
	{
		swprintf_s(buffer, 256, L"%d 인 상품은 없습니다",i_arg);
		CPrinter::PrintLine(buffer);

		CLogManager::getInstance().AddLog(buffer);
	}
	else
	{
		int total_price = Select_item->value * item_stock;
		swprintf_s(buffer, 256, L"%ws x %d 의 가격은 %d 입니다.", Select_item->name.c_str(),item_stock, total_price);
		CPrinter::PrintLine(buffer);
		CLogManager::getInstance().AddLog(buffer);

		item_value = Select_item->value;

		int* Player_gold = pPlayer->Get_pGold();
		if (item_value * item_stock> *Player_gold)
		{
			swprintf_s(buffer, 256, L"골드가 부족합니다.");
			CPrinter::PrintLine(buffer);
			CLogManager::getInstance().AddLog(buffer);
		}
		else
		{
			*Player_gold -= total_price;
			//pPlayer->Add_Inventory(Select_item);
			//CItem* pCItem
			pPlayer->Add_Inventory_FItemData(Select_item,item_stock);
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
