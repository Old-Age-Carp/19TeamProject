#pragma once

#include "IHitAble.h"
#include "IAttack.h"
#include "define.h"
#include "CItem.h"
#include "CBattleAI.h"
#include "CGameObject.h"

#include <vector>
#include <memory>


// 전투 가능한 객체 정의
// 해야할 행동 결정 (공격, 아이템 사용, 기타...)
// 행동 대상 지정
// AI 라고 지정

class CBattleAbleObject : public CGameObject, public IHitAble, public IAttack
{
    std::unique_ptr<IBattleAI> ai;
public:
    CBattleAbleObject() = default;
    CBattleAbleObject(const std::wstring& name, int level = 1, int health = 200, int attack = 30)
        : CGameObject(name, level, health, attack)
    {
    }

    virtual ~CBattleAbleObject() = default;
    virtual std::vector<CItem*> GetHaveItems() = 0;

    const IBattleAI& GetAI() { return *ai; }

    inline void SetBattleAI(std::unique_ptr<IBattleAI> ai)
    {
        this->ai = std::move(ai);
    }

    void TakeDamage(int damage) override
    {
        iHealth -= damage;
        if (iHealth < 0)
        {
            iHealth = 0;
        }
    }

    int GetAttackValue() const override { return iAttack; }

    bool IsAlive() const override { return iHealth > 0; }
};
