#include "CGameItem.h"
#include <iostream>
#include <string>
#include <map>
#include <locale>

StaticDataManager::StaticDataManager() {
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale(""));

	loadItemData();
}

void StaticDataManager::loadItemData() {
	itemTable[1001] = {
		1001,
		L"작은 물약",
		10,
		0,
		0,
		0,
		50,
		L"Potion"
	};

	itemTable[1002] = {
		1002,
		L"큰 물약",
		30,
		0,
		0,
		0,
		100,
		L"Potion"
	};

	itemTable[2001] = {
		2001,
		L"철검",
		20,
		5,
		0,
		0,
		0,
		L"Weapon"
	};

	itemTable[2002] = {
		2002,
		L"미스릴검",
		50,
		15,
		5,
		0,
		0,
		L"Weapon"
	};

	itemTable[2003] = {
		2003,
		L"전설의명검",
		100,
		50,
		15,
		50,
		0,
		L"Weapon"
	};

	itemTable[3001] = {
		3001,
		L"낡은 도복",
		20,
		0,
		5,
		0,
		0,
		L"Armor"
	};

	itemTable[3002] = {
		3002,
		L"철 갑옷",
		50,
		0,
		30,
		10,
		0,
		L"Armor"
	};

	itemTable[3003] = {
		3003,
		L"불멸의흑갑",
		100,
		10,
		60,
		100,
		0,
		L"Armor"
	};


}

const StaticDataManager::ItemData* StaticDataManager::GetItemData(int id) const {
	auto it = itemTable.find(id);
	if (it != itemTable.end()) {
		return &(it->second);
	}
	return nullptr;
}
