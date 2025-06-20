#pragma once
#include <string>
#include <vector>

class Monster{
public:
    enum class MonsterType { Normal, Boss };

private:
    MonsterType type;
    int expReward;
    std::vector<int> dropItemIds;

public:
    Monster(int id, const std::string& name, int atk, int def, int hp,
        MonsterType type, int exp, const std::vector<int>& drops);

   
    MonsterType GetType() const;
    int GetExpReward() const;
    std::vector<int> GetDropItems() const;
};
