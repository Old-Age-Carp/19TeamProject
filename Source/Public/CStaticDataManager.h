#pragma once

#include "TSingleton.h"
#include "define.h"
#include <memory>
#include <unordered_map>
#include <string>
#include "CMonster.h"
#include "CGameItem.h"

class CStaticDataManager : public TSingleton<CStaticDataManager>
{

	friend class TSingleton<CStaticDataManager>;

public:
    bool LoadAllStaticData();

    const FMonsterData* GetMonsterData(const std::wstring& name) const;
    const FMonsterData* GetMonsterData(int id) const;

    const FItemData* GetItemData(const std::wstring& name) const;
    const FItemData* GetItemData(int id) const;

private:
    CStaticDataManager() = default; 
    ~CStaticDataManager() = default; 

    bool LoadMonsterDataInternal(); 
    bool LoadItemDataInternal();    

    std::unordered_map<std::wstring, FMonsterData> monsterDataTable; 
    std::unordered_map<int, FMonsterData> monsterDataTableByID;     

    std::unordered_map<int, std::unique_ptr<FItemData>> itemDataTableByID;       
    std::unordered_map<std::wstring, FItemData*> itemDataTableByName;
};
