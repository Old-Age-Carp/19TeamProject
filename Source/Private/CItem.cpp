#include "CItem.h"
#include <iostream>
#include <string>
#include <typeinfo>

CItem::CItem(const FItemData* InDefinition, int InStack)
    : ItemDefinition(InDefinition), CurrentStack(InStack), bIsEquipped(false)
{}

void CItem::Use() // 아이템, 누구한테, 사용되면 어떻게되는지
{
    if (!ItemDefinition || CurrentStack <= 0)
    {
        return;
    }

    CurrentStack--;

    if (const FItemPotionData* PotionData = dynamic_cast<const FItemPotionData*>(ItemDefinition))
    {
    }
    else if (const FItemWeaponData* WeaponData = dynamic_cast<const FItemWeaponData*>(ItemDefinition))
    {
        if (!bIsEquipped)
        {
            bIsEquipped = true;
        }
        else
        {
            bIsEquipped = false;
        }
    }
    else if (const FItemArmorData* ArmorData = dynamic_cast<const FItemArmorData*>(ItemDefinition))
    {
        if (!bIsEquipped)
        {
            bIsEquipped = true;
        }
        else
        {
            bIsEquipped = false;
        }
    }
    else
    {
    }

}

int CItem::GetID() const
{
    return ItemDefinition ? ItemDefinition->id : -1;
}

std::wstring CItem::GetName() const
{
    return ItemDefinition ? ItemDefinition->name : L"알 수 없는 아이템";
}

int CItem::GetValue() const
{
    return ItemDefinition ? ItemDefinition->value : 0;
}

int CItem::GetCurrentStack() const
{
    return CurrentStack;
}

bool CItem::IsEquipped() const
{
    return bIsEquipped;
}

void CItem::SetCurrentStack(int NewStack)
{
    CurrentStack = NewStack > 0 ? NewStack : 0;
}

void CItem::AddCurrentStack(int NewStack)
{
    SetCurrentStack(CurrentStack + NewStack);
}

void CItem::SetEquipped(bool bEquipped)
{
    bIsEquipped = bEquipped;
}
