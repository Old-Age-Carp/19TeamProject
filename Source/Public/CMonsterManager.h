#pragma once
#include <unordered_map>
#include <string>
#include "CMonster.h"

class CMonsterManager
{
public:
    static CMonsterManager& GetInstance();

    bool LoadMonsterData();
    const MonsterData* GetMonsterData(const std::wstring& name) const;

private:
    CMonsterManager() = default;
    std::unordered_map<std::wstring, MonsterData> monsterDataTable;
};
