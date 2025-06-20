#pragma once

#include <string>

using namespace std;

class CGameObject
{
public:
	CGameObject() = default;

	// 매개변수 생성자
	CGameObject(const std::string& name, int level = 1, int health = 200, int attack = 30)
		: sName(name), iLevel(level), iHealth_Max(health), iHealth(health), iAttack(attack) {
	}

	virtual string getName() const = 0;
	virtual int		getHealth() const = 0;
	virtual int		getAttack() const = 0;

	virtual ~CGameObject() = default;
private:

	

protected:
	string sName;
	int		iLevel = 1;
	int		iHealth_Max = 200;
	int		iHealth = 200; //현재체력
	int		iExp = 0;
	int		iGold = 0;
	int		iAttack = 30;

};

