#pragma once

#include "TSingleton.h"
#include "define.h"
#include <map>
#include <memory>

class StaticDataManager : public TSingleton<StaticDataManager>
{
	friend class TSingleton<StaticDataManager>;

public:
	const FItemData* GetItemData(int id) const;

private:
	std::map<int, std::unique_ptr<FItemData>> itemTable;
	StaticDataManager();
	void loadItemData();
};
