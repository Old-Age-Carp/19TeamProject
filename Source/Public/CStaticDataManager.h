#pragma once

#include "TSingleton.h"
#include "define.h"
#include <map>
#include <memory>

class CStaticDataManager : public TSingleton<CStaticDataManager>
{
	friend class TSingleton<CStaticDataManager>;

public:
	const FItemData* GetItemData(int id) const;

private:
	std::map<int, std::unique_ptr<FItemData>> itemTable;
	CStaticDataManager();
	void loadItemData();
};
