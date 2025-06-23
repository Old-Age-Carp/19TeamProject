#pragma once

#include <string>

using namespace std;

class CGameObject
{
public:
	CGameObject() = default;

	// 매개변수 생성자
	CGameObject(const std::wstring& name, int level = 1, int health = 200, int attack = 30)
		: sName(name), iLevel(level), iHealth_Max(health), iHealth(health), iAttack(attack) {
	}

	wstring	getName() const { return sName; }
	int		getHealthMax()	const { return iHealth_Max; }
	int		getHealth()	const { return iHealth; }
	int		getAttack()	const { return iAttack; }
	int		getDefense()const { return iDefense; }
	int		getLevel()	const { return iLevel; }

	virtual ~CGameObject() = default;
private:

	

protected:
	wstring sName;
	int		iLevel = 1;
	int		iHealth_Max = 200;
	int		iHealth = 200; //현재체력
	int		iExp = 0;
	int		iGold = 0;
	int		iAttack = 30;
	int		iDefense = 5;
};

