#pragma once
#include <string>

class IAttack
{
public:
    virtual ~IAttack() = default;

    virtual int GetAttackValue() const = 0;
};
