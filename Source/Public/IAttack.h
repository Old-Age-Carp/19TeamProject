#pragma once
#include <string>

class IAttack
{
public:
    virtual ~IAttack() = default;

    virtual int GetAttackValue() const = 0;

    virtual const std::wstring& GetName() const = 0;
};
