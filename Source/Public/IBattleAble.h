#pragma once

#include "IHitAble.h"
#include "IAttack.h"

class IBattleAble: public IHitAble, public IAttack
{
public:
    virtual ~IBattleAble() = default;
};
