#pragma once
#include <string>
#include <vector>
#include "CBattleAbleObject.h"
#include "CItem.h"

using std::vector;

enum class EMonsterType
{
    Normal,
    Boss,
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
class CMonster : public CBattleAbleObject
{
public:
    CMonster(const FMonsterData* baseData)
        : CBattleAbleObject(baseData ? baseData->name : L"Unknown Monster",
            1,
            baseData ? baseData->hp : 0,
            baseData ? baseData->atk : 0),
        m_baseData(baseData)
    {
    }

    CMonster() : CBattleAbleObject(),
        m_baseData(nullptr)
    {
    }

public:

    int GetCurrentHP() const { return iHealth; }

    const std::vector<int>& GetDropItemIDs() const
    {
        static const std::vector<int> emptyVec;
        return m_baseData ? m_baseData->dropItemTableIDs : emptyVec;
    }

    int GetExpReward() const { return m_baseData ? m_baseData->expReward : 0; }
    
    EMonsterType GetType() const { return m_baseData ? m_baseData->type : EMonsterType::Normal; }

    vector<CItem*> GetHaveItems() override { return vector<CItem*>(); }

private:
    const FMonsterData* m_baseData;
};
