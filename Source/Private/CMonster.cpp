#include "CMonster.h"


CMonster::CMonster(int id, const std::string& name, int atk, int def, int hp,
    EMonsterType type, int exp, const std::vector<int>& dropItemTableIDs)
    : //CGameObject(id, name, atk, def, hp), 컴파일 에러로 인한 임시처리.
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
