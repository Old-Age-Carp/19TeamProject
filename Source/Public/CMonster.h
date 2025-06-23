#pragma once
#include <string>
#include <vector>

enum class EMonsterType
{
    Normal,
    Boss
};

struct MonsterDataf
{
    std::wstring name;
    int atk;
    int hp;
    EMonsterType type;
    int expReward;
    std::vector<int> dropItemTableIDs;
};
