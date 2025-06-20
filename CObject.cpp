#include "CObject.h"

CObject::CObject(int id, const std::wstring& name, int atk, int def, int hp)
    : id(id), name(name), atk(atk), def(def), hp(hp)
{
}

int CObject::GetID() const
{
    return id;
}

const std::wstring& CObject::GetName() const
{
    return name;
}

int CObject::GetAtk() const
{
    return atk;
}

int CObject::GetDef() const
{
    return def;
}

int CObject::GetHP() const
{
    return hp;
}
