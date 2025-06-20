#include "CMonster.h"


CMonster::CMonster(int id, const std::string& name, int atk, int def, int hp,
    EMonsterType type, int exp, const std::vector<int>& dropItemTableIDs)
    : Object(id, name, atk, def, hp),
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
