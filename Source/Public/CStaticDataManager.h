#pragma once

#include "TSingleton.h"
#include "define.h"
#include <memory>
#include <unordered_map>
#include <string>
#include "CMonster.h"

class CStaticDataManager : public TSingleton<CStaticDataManager>
{
	friend class TSingleton<CStaticDataManager>;

	static CMonsterManager& GetInstance();

	bool LoadMonsterData();

	const FMonsterData* GetMonsterData(const std::wstring& name) const;

	const FMonsterData* GetMonsterData(int id) const;

public:
	const FItemData* GetItemData(int id) const;

private:
	std::map<int, std::unique_ptr<FItemData>> itemTable;
	CStaticDataManager();
	void loadItemData();
	CMonsterManager() = default;
	std::unordered_map<std::wstring, FMonsterData> monsterDataTable;
	std::unordered_map<int, FMonsterData> monsterDataTableByID;

};
