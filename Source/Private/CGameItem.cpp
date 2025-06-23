#include "CGameItem.h"
#include <iostream>
#include <string>
#include <typeinfo>

CItem::CItem(const FItemData* InDefinition, int InStack)
    : ItemDefinition(InDefinition), CurrentStack(InStack), bIsEquipped(false)
{
    if (!ItemDefinition)
    {
        std::wcout << L"경고: 유효하지 않은 아이템 정의로 CItem 인스턴스가 생성되었습니다." << std::endl;
    }
}

void CItem::Use()
{
    if (!ItemDefinition || CurrentStack <= 0)
    {
        std::wcout << GetName() << L"을(를) 사용할 수 없습니다 (정의 없음 또는 수량 부족)." << std::endl;
        return;
    }

    CurrentStack--;

    std::wcout << GetName() << L"을(를) 사용했습니다! ";

    if (const FItemPotionData* PotionData = dynamic_cast<const FItemPotionData*>(ItemDefinition))
    {
        std::wcout << PotionData->healAmount << L" HP 회복! ";
    }
    else if (const FItemWeaponData* WeaponData = dynamic_cast<const FItemWeaponData*>(ItemDefinition))
    {
        if (!bIsEquipped)
        {
            bIsEquipped = true;
            std::wcout << L"장착! 공격력 " << WeaponData->attackBonus
                << L", 방어력 " << WeaponData->defenseBonus
                << L", 체력 " << WeaponData->healthBonus << L" 증가! ";
        }
        else
        {
            bIsEquipped = false;
            std::wcout << L"해제! ";
        }
    }
    else if (const FItemArmorData* ArmorData = dynamic_cast<const FItemArmorData*>(ItemDefinition))
    {
        if (!bIsEquipped)
        {
            bIsEquipped = true;
            std::wcout << L"장착! 방어력 " << ArmorData->defenseBonus
                << L", 체력 " << ArmorData->healthBonus << L" 증가! ";
        }
        else
        {
            bIsEquipped = false;
            std::wcout << L"해제! ";
        }
    }
    else
    {
        std::wcout << L"알 수 없는 효과. ";
    }

    std::wcout << L"(남은 수량: " << CurrentStack << L")" << std::endl;
}

void CItem::DisplayInfo() const
{
    if (!ItemDefinition)
    {
        std::wcout << L"--- 아이템 정보 ---" << std::endl;
        std::wcout << L"유효하지 않은 아이템 인스턴스." << std::endl;
        std::wcout << L"--------------------" << std::endl;
        return;
    }

    std::wcout << L"--- 아이템 정보 ---" << std::endl;
    std::wcout << L"ID: " << ItemDefinition->id << std::endl;
    std::wcout << L"이름: " << ItemDefinition->name << std::endl;
    std::wcout << L"가치: " << ItemDefinition->value << L" 골드" << std::endl;
    std::wcout << L"현재 수량: " << CurrentStack << std::endl;
    std::wcout << L"장착 상태: " << (bIsEquipped ? L"장착됨" : L"미장착") << std::endl;

    if (const FItemPotionData* PotionData = dynamic_cast<const FItemPotionData*>(ItemDefinition))
    {
        std::wcout << L"타입: 물약 (Potion)" << std::endl;
        std::wcout << L"회복량: " << PotionData->healAmount << L" HP" << std::endl;
    }
    else if (const FItemWeaponData* WeaponData = dynamic_cast<const FItemWeaponData*>(ItemDefinition))
    {
        std::wcout << L"타입: 무기 (Weapon)" << std::endl;
        std::wcout << L"공격력 보너스: " << WeaponData->attackBonus << std::endl;
        if (WeaponData->defenseBonus != 0) std::wcout << L"방어력 보너스: " << WeaponData->defenseBonus << std::endl;
        if (WeaponData->healthBonus != 0) std::wcout << L"체력 보너스: " << WeaponData->healthBonus << std::endl;
    }
    else if (const FItemArmorData* ArmorData = dynamic_cast<const FItemArmorData*>(ItemDefinition))
    {
        std::wcout << L"타입: 방어구 (Armor)" << std::endl;
        std::wcout << L"방어력 보너스: " << ArmorData->defenseBonus << std::endl;
        if (ArmorData->healthBonus != 0) std::wcout << L"체력 보너스: " << ArmorData->healthBonus << std::endl;
    }
    else
    {
        std::wcout << L"타입: 알 수 없음" << std::endl;
    }
    std::wcout << L"--------------------" << std::endl;
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

void CItem::SetEquipped(bool bEquipped)
{
    bIsEquipped = bEquipped;
}
