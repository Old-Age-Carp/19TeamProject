#pragma once
#include <string>
#include <vector>
#include "IAttack.h"
#include "IHitAble.h"


enum class EMonsterType
{
    Normal,
    Boss
};

struct FMonsterData
{
    int id;
    std::wstring name;
    int atk;
    int hp;
    EMonsterType type;
    int expReward;
    std::vector<int> dropItemTableIDs;
};

class CMonster
{
public:
    CMonster(const FMonsterData* baseData)
        : m_baseData(baseData), m_currentHP(baseData ? baseData->hp : 0)
    {
        if (!baseData)
        {
            m_currentHP = 0;
        }
    }
private:

    CMonster() : m_baseData(nullptr), m_currentHP(0) {}

public:
    void TakeDamage(int damage)
    {
        m_currentHP -= damage;
        if (m_currentHP < 0)
        {
            m_currentHP = 0;
        }
    }

    bool IsAlive() const { return m_currentHP > 0; }

    int GetCurrentHP() const { return m_currentHP; }

    int GetAttackValue() const { return m_baseData ? m_baseData->atk : 0; }

    const std::wstring& GetName() const { return m_baseData ? m_baseData->name : L"Unknown"; }

    const std::vector<int>& GetDropItemIDs() const
    {
        static const std::vector<int> emptyVec;
        return m_baseData ? m_baseData->dropItemTableIDs : emptyVec;
    }

    int GetExpReward() const { return m_baseData ? m_baseData->expReward : 0; }

    EMonsterType GetType() const { return m_baseData ? m_baseData->type : EMonsterType::Normal; }

private:
    const FMonsterData* m_baseData;
    int m_currentHP;
};
