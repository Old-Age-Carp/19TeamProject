#pragma once
#include <unordered_map>
#include <string>
#include "CMonster.h"

class CMonsterManager
{
public:
    static CMonsterManager& GetInstance();

    bool LoadMonsterData();

    const FMonsterData* GetMonsterData(const std::wstring& name) const;

    const FMonsterData* GetMonsterData(int id) const;

private:
    CMonsterManager() = default;
    std::unordered_map<std::wstring, FMonsterData> monsterDataTable;
    std::unordered_map<int, FMonsterData> monsterDataTableByID;
};
