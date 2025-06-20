#pragma once
#include <string>
#include <vector>
#include "CObject.h"

class CMonster : public CObject {
public:
    enum class EMonsterType { Normal, Boss };

private:
    EMonsterType type;
    int expReward;
    std::vector<int> dropItemTableIDs;

public:
    CMonster(const std::string& name, int atk, int hp,
        EMonsterType type, int exp, const std::vector<int>& dropItemTableIDs);


    EMonsterType GetType() const;
    int GetExpReward() const;
    std::vector<int> GetDropItemTableIDs() const;
};
