#pragma once
#include <unordered_map>
#include <string>
#include "MonsterData.h"

class StaticDataManager
{
public:
    static StaticDataManager& GetInstance();

    bool LoadMonsterData();
    const MonsterData* GetMonsterData(const std::wstring& name) const;

private:
    StaticDataManager() = default;
    std::unordered_map<std::wstring, MonsterData> monsterDataTable;
};
