#include "CMonster.h"


CMonster::CMonster(const std::string& name, int atk, int hp,
    EMonsterType type, int exp, const std::vector<int>& dropItemTableIDs)
    : CGameObject(name, 1, hp, atk),
    type(type), expReward(exp), dropItemTableIDs(dropItemTableIDs)
{
}


CMonster::EMonsterType CMonster::GetType() const
{
    return type;
}

int CMonster::GetExpReward() const
{
    return expReward;
}

std::vector<int> CMonster::GetDropItemTableIDs() const
{
    return dropItemTableIDs;
}
