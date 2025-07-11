﻿#pragma once
#include <string>

class IHitAble
{
public:
    virtual ~IHitAble() = default; 

    virtual void TakeDamage(int damage) = 0;

    virtual bool IsAlive() const = 0;
};
