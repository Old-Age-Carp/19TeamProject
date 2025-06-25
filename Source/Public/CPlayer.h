#pragma once
//


#include "CBattleAbleObject.h"
#include "define.h"

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

public:
	void LevelUp();

	void Show_Inventory();
	void Show_Inventory_part(int i_arg);
	void Add_Inventory(FItemData* Item);
	int Sub_Inventory(int i_arg,int i_num, bool b_sell =false);

	void Equip(int i_arg);
	void UsePotion(int i_arg);
	std::vector<CItem*> GetHaveItems() override;
protected:
	virtual ~CPlayer() = default;
	std::vector<std::pair<int, FItemData*>> m_vecInventory;
private:

};
