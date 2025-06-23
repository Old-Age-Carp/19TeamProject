#pragma once

#include <string>



class CGameObject
{
public:
	CGameObject() = default;

	// 매개변수 생성자
	CGameObject(const std::wstring& name, int level = 1, int health = 200, int attack = 30)
		: sName(name), iLevel(level), iHealth_Max(health), iHealth(health), iAttack(attack) {
	}

	std::wstring	getName() const { return sName; }
	int		getHealth()	const { return iHealth; }
	int		getHealth_Max() const { return iHealth_Max; }
	int		getAttack() const { return iAttack; }
	int		getArmor() const { return iArmor; }
	int		getLevel()	const { return iLevel; }

	void    setName(std::wstring arg) { sName = arg; }

	//겟셋대체용으로 포인터 가져와서 활용
	
	int* Get_pLevel()				{ return &iLevel; }
	int* Get_pHealthMax()			{ return &iHealth_Max; }
	int* Get_pHealth()				{ return &iHealth; }
	int* Get_pExp()					{ return &iExp; }
	int* Get_pGold()				{ return &iGold; }
	int* Get_pAttack()				{ return &iAttack; }
	int* Get_pArmor()				{ return &iArmor; }

	virtual ~CGameObject() = default;
private:

	

protected:
	std::wstring sName;
	int		iLevel = 1;
	int		iHealth_Max = 200;
	int		iHealth = 200; //현재체력
	int		iExp = 0;
	int		iGold = 0;
	int		iAttack = 30;
	int		iArmor = 10;

};

