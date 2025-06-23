#pragma once
//


#include "CGameObject.h"

class CPlayer : public CGameObject
{
public:
	CPlayer() = default;


	CPlayer(const std::string& name, int level = 1, int health = 200, int attack = 30)
		: CGameObject(name, level, health, attack)
	{
	}

public:
	void LevelUp();

protected:
	virtual ~CPlayer() = default;


};
