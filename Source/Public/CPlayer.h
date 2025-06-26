#pragma once
//


#include "CBattleAbleObject.h"
#include "define.h"
#include "CItem.h"
#include <vector>

class CPlayer : public CBattleAbleObject
{
public:
	CPlayer() = default;


	CPlayer(const std::wstring& name, int level = 1, int health = 200, int attack = 30)
		: CBattleAbleObject(name, level, health, attack)
	{
		int* pGold = Get_pGold();
		*pGold = 200;
	}

	~CPlayer();
public:
	bool LevelUp();

	void Show_Inventory();
	void Show_Inventory_part(int i_arg);
	void Add_Inventory(CItem* Item);
	void Add_Inventory_FItemData(FItemData* Item,int item_stock= 1);
	int Sub_Inventory(int i_id,int i_num, bool b_sell =false);

	void Equip(int i_arg);
	void UsePotion(int i_arg);
	void Sell_item(int item_id,int item_stock =1);
	std::vector<CItem*> GetHaveItems() override;
protected:
	//virtual ~CPlayer() = default;

	std::vector<CItem*> m_vecInventory;
private:

};
