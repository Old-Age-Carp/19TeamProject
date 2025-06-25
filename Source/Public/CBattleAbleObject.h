#pragma once

#include "IHitAble.h"
#include "IAttack.h"
#include "define.h"
#include "CItem.h"
#include "CBattleAI.h"

#include <vector>
#include <memory>


// 전투 가능한 객체 정의
// 해야할 행동 결정 (공격, 아이템 사용, 기타...)
// 행동 대상 지정
// AI 라고 지정

class CBattleAbleObject : public IHitAble, public IAttack
{
    std::unique_ptr<CBattleAI> ai;
public:
    CBattleAbleObject() = default;

    virtual ~CBattleAbleObject() = default;
    virtual std::vector<CItem&> GetHaveItems() = 0;
    inline void SetBattleAI(std::unique_ptr<CBattleAI> ai)
    {
        this->ai = std::move(ai);
    }
};
