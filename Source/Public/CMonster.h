#pragma once
#include <string>
#include <vector>

class CMonster {
public:
    enum class EMonsterType { Normal, Boss };

private:
    EMonsterType type;
    int expReward;
    std::vector<int> dropItemTableIDs;  

public:
    CMonster(int id, const std::string& name, int atk, int def, int hp,
        EMonsterType type, int exp, const std::vector<int>& dropItemTableIDs);

    EMonsterType GetType() const;
    int GetExpReward() const;
    std::vector<int> GetDropItemTableIDs() const;
};
