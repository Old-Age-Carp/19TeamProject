#pragma once

#include "TSingleton.h"
#include "define.h"
#include <memory>
#include <unordered_map>
#include <string>
#include "CMonster.h"
#include "CItem.h"

class CStaticDataManager : public TSingleton<CStaticDataManager>
{

	friend class TSingleton<CStaticDataManager>;

public:
    bool LoadAllStaticData();

    FMonsterData* GetMonsterData(const std::wstring& name) ;
    FMonsterData* GetMonsterData(int id) ;

    FItemData* GetItemData(const std::wstring& name) ;
    FItemData* GetItemData(int id) ;



    void Print_AllItem();

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
