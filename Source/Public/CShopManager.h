#pragma once
#include "define.h"

class CShopManager
{
	
private:
	static CShopManager* instance; //싱글톤 선언

	class CStaticDataManager* m_pStaticDataManager = nullptr;

	CShopManager(); // 생성자
	~CShopManager(); //소멸자



public:
	void Show_ShopItem();

	FItemData* Buy_Item(int i_arg,class CPlayer* pPlayer, int item_stock = 1);
	void Check_money();
	static CShopManager* GetInstance();
	static void				DestroyInstance();


protected:

};

