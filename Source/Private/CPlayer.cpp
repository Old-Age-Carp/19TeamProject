#pragma once

#include "..\Public\CPlayer.h"
#include "..\Public\CPrinter.h"


bool CPlayer::LevelUp()
{
    bool result = false;
	if (iExp >= 100)
	{
		iExp -= 100;
	}
	iLevel++;
    if (iLevel == 10)
        result = true;
	iHealth_Max = iHealth_Max + (iLevel * 20);
	iHealth = iHealth_Max ;
	iAttack += iLevel * 5;

    return result;
}

void CPlayer::Show_Inventory()
{
    CPrinter::PrintLine(L"==================== [보유 인벤토리] ====================");

    if (m_vecInventory.empty())
    {
        CPrinter::PrintLine(L"인벤토리에 아이템이 없습니다.");
        return;
    }

    wchar_t buffer[256];

    for (const auto& invItem : m_vecInventory)
    {
        const FItemData* pItem = invItem.second;
        if (!pItem) continue;

        std::wstring name = pItem->name;
        int id = pItem->id;
        int value = pItem->value;
        int quantity = invItem.first;
        std::wstring Equipped;
        // 이름/가격/수량/장착 상태
        swprintf_s(buffer, 256, L"이름: %ws | ID: %d | 가격: %d ,보유량 : %d ",
            name.c_str(), id, value, quantity);
        CPrinter::PrintLine(buffer);

        // 아이템 타입별 정보
        if (auto pPotion = dynamic_cast<const FItemPotionData*>(pItem))
        {
            swprintf_s(buffer, 256, L"[포션] 회복량: %d", pPotion->healAmount);
        }
        else if (auto pWeapon = dynamic_cast<const FItemWeaponData*>(pItem))
        {
            if (pWeapon->bEquipped == true)
            {
                Equipped = L"장착 ON";
            }
            else
            {
                Equipped = L"장착 OFF";
            }
            swprintf_s(buffer, 256, L"[무기] 공격력: %d, 방어력: %d, 체력: %d,%ws ",
                pWeapon->attackBonus, pWeapon->defenseBonus, pWeapon->healthBonus,Equipped.c_str());
        }
        else if (auto pArmor = dynamic_cast<const FItemArmorData*>(pItem))
        {
            if (pArmor->bEquipped == true)
            {
                Equipped = L"장착 ON";
            }
            else
            {
                Equipped = L"장착 OFF";
            }
            swprintf_s(buffer, 256, L"[방어구] 방어력: %d, 체력: %d ,%ws",
                pArmor->defenseBonus, pArmor->healthBonus,Equipped.c_str());
        }

        CPrinter::PrintLine(buffer);
        CPrinter::PrintLine(L"--------------------------------------------------------");
    }

    CPrinter::PrintLine(L"========================================================");
}

void CPlayer::Show_Inventory_part(int i_arg)
{
    
    CPrinter::PrintLine(L"================ [인벤토리 필터 보기] ================");

    if (m_vecInventory.empty())
    {
        CPrinter::PrintLine(L"인벤토리에 아이템이 없습니다.");
        return;
    }

    wchar_t buffer[256];
    bool bFound = false;

    for (const auto& invItem : m_vecInventory)
    {
        const FItemData* pItem = invItem.second;
        if (!pItem) continue;

        std::wstring name = pItem->name;
        int id = pItem->id;
        int value = pItem->value;
        int quantity = invItem.first;
        std::wstring Equipped;

        switch (i_arg)
        {
        case 1: // 포션
            if (auto pPotion = dynamic_cast<const FItemPotionData*>(pItem))
            {
                bFound = true;
                swprintf_s(buffer, 256, L"이름: %ws | ID: %d | 가격: %d | 수량: %d", name.c_str(), id, value, quantity);
                CPrinter::PrintLine(buffer);
                swprintf_s(buffer, 256, L"[포션] 회복량: %d", pPotion->healAmount);
                CPrinter::PrintLine(buffer);
                CPrinter::PrintLine(L"--------------------------------------------------------");
            }
            break;

        case 2: // 무기
            if (auto pWeapon = dynamic_cast<const FItemWeaponData*>(pItem))
            {
                bFound = true;
                Equipped = pWeapon->bEquipped ? L"장착 ON" : L"장착 OFF";
                swprintf_s(buffer, 256, L"이름: %ws | ID: %d | 가격: %d | 수량: %d", name.c_str(), id, value, quantity);
                CPrinter::PrintLine(buffer);
                swprintf_s(buffer, 256, L"[무기] 공격력: %d, 방어력: %d, 체력: %d | %ws",
                    pWeapon->attackBonus, pWeapon->defenseBonus, pWeapon->healthBonus, Equipped.c_str());
                CPrinter::PrintLine(buffer);
                CPrinter::PrintLine(L"--------------------------------------------------------");
            }
            break;

        case 3: // 방어구
            if (auto pArmor = dynamic_cast<const FItemArmorData*>(pItem))
            {
                bFound = true;
                Equipped = pArmor->bEquipped ? L"장착 ON" : L"장착 OFF";
                swprintf_s(buffer, 256, L"이름: %ws | ID: %d | 가격: %d | 수량: %d", name.c_str(), id, value, quantity);
                CPrinter::PrintLine(buffer);
                swprintf_s(buffer, 256, L"[방어구] 방어력: %d, 체력: %d | %ws",
                    pArmor->defenseBonus, pArmor->healthBonus, Equipped.c_str());
                CPrinter::PrintLine(buffer);
                CPrinter::PrintLine(L"--------------------------------------------------------");
            }
            break;

        default:
            CPrinter::PrintLine(L"잘못된 입력입니다. (1: 포션, 2: 무기, 3: 방어구)");
            return;
        }
    }

    if (!bFound)
    {
        CPrinter::PrintLine(L"해당 타입의 아이템이 없습니다.");
    }

    CPrinter::PrintLine(L"========================================================");
}

void CPlayer::Add_Inventory(FItemData* Item)
{
    if (Item == nullptr)
        return;
    //m_vec
    for (auto& pair :m_vecInventory)
    {
        if (pair.second && pair.second->id == Item->id)
        {
            pair.first++;
            return;
        }
    }

    m_vecInventory.push_back(std::make_pair(1, Item));
}

int CPlayer::Sub_Inventory(int i_arg, int i_num,bool b_sell)
{
    int result = 0;
    for (auto it = m_vecInventory.begin(); it != m_vecInventory.end(); ++it)
    {
        if (it->second && it->second->id == i_arg)
        {
            // 수량 부족 시 처리
            if (it->first < i_num)
                return 0;

            // 판매 금액 계산
            if (b_sell)
                result = i_num * it->second->value;

            // 수량 차감
            it->first -= i_num;

            // 0개가 되면 제거
            if (it->first == 0)
                m_vecInventory.erase(it);

            return result;
        }
    }


    return result;
}

void CPlayer::Equip(int i_arg)
{
    for (auto& pair : m_vecInventory)
    {
        if (pair.second && pair.second->id == i_arg)
        {
            if (auto pWeapon = dynamic_cast<FItemWeaponData*>(pair.second))
            {
                if (pWeapon->bEquipped == false)
                {
                    pWeapon->bEquipped = true;

                    iAttack         += pWeapon->attackBonus;
                    iArmor          += pWeapon->defenseBonus;
                    iHealth_Max     += pWeapon->healthBonus;
                    iHealth         += pWeapon->healthBonus;
                }
                else
                {
                    pWeapon->bEquipped = false;

                    iAttack     -= pWeapon->attackBonus;
                    iArmor      -= pWeapon->defenseBonus;
                    iHealth_Max -= pWeapon->healthBonus;
                    iHealth     -= pWeapon->healthBonus;
                }
      
            }
            else if (auto pArmor = dynamic_cast<FItemArmorData*>(pair.second))
            {
                if (pArmor->bEquipped == false)
                {
                    pArmor->bEquipped = true;

                    iArmor          += pArmor->defenseBonus;
                    iHealth_Max     += pArmor->healthBonus;
                    iHealth         += pArmor->healthBonus;

                }
                else
                {
                    pArmor->bEquipped = false;

                    iArmor          -= pArmor->defenseBonus;
                    iHealth_Max     -= pArmor->healthBonus;
                    iHealth         -= pArmor->healthBonus;
                }

            }

            else if (auto pWeapon = dynamic_cast<FItemPotionData*>(pair.second))
            {
                UsePotion(i_arg);
            }
        }

        else if (pair.second && pair.second->id != i_arg)
        {
            if (auto pWeapon = dynamic_cast<FItemWeaponData*>(pair.second))
            {
                if (pWeapon->bEquipped == true)
                {
                    pWeapon->bEquipped = false;

                    iAttack     -= pWeapon->attackBonus;
                    iArmor      -= pWeapon->defenseBonus;
                    iHealth_Max -= pWeapon->healthBonus;
                    iHealth     -= pWeapon->healthBonus;
                }
         
            }
            else if (auto pArmor = dynamic_cast<FItemArmorData*>(pair.second))
            {

                if (pArmor->bEquipped == true)
                {
                    pArmor->bEquipped = false;

                    iArmor      -= pArmor->defenseBonus;
                    iHealth_Max -= pArmor->healthBonus;
                    iHealth     -= pArmor->healthBonus;
                
                }

       
            }
        }
    }
}

void CPlayer::UsePotion(int i_arg)
{
    wchar_t buffer[256];

    for (auto& pair : m_vecInventory)
    {
        if (pair.second && pair.second->id == i_arg)
        {
            if (auto pPotion = dynamic_cast<FItemPotionData*>(pair.second))
            {
                if (pair.first > 0)
                {
                    int Potion_Heal = pPotion->healAmount;

                    iHealth += Potion_Heal;
                    if (iHealth >= iHealth_Max)
                    {
                        iHealth = iHealth_Max;
                    }
                    swprintf_s(buffer, 256, L"체력: %d / %d ",iHealth, iHealth_Max);
                    CPrinter::PrintLine(buffer);
                    pair.first--;
                }
                else {
                    CPrinter::PrintLine(L"포션이 부족합니다");
                }

            }
        }
    }
}

std::vector<CItem*> CPlayer::GetHaveItems()
{
    return std::vector<CItem*>();
}
