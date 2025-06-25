#pragma once
#include <string>
#include <vector>
#include "IAttack.h"
#include "IHitAble.h"
#include "CGameObject.h"


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

/// <summary>
/// 게임 내 몬스터 개체를 나타내는 클래스입니다.
/// </summary>
class CMonster : public CGameObject, public IAttack, public IHitAble
{
public:
    CMonster(const FMonsterData* baseData)
        : CGameObject(baseData ? baseData->name : L"Unknown Monster",
            1,
            baseData ? baseData->hp : 0,
            baseData ? baseData->atk : 0),
        m_baseData(baseData),
        m_currentHP(baseData ? baseData->hp : 0)
    {
    }

    CMonster() : CGameObject(),
        m_baseData(nullptr), m_currentHP(0)
    {
    }

public:
    void TakeDamage(int damage) override
    {
        iHealth -= damage;
        if (iHealth < 0)
        {
            iHealth = 0;
        }
        m_currentHP = iHealth;
    }

    bool IsAlive() const override { return iHealth > 0; }

    int GetAttackValue() const override { return iAttack; }

    const std::wstring& GetName() const override { return sName; }

    int GetCurrentHP() const { return iHealth; }

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
