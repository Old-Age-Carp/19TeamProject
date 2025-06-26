#pragma once

#include "..\Public\CPlayer.h"
#include "..\Public\CPrinter.h"
#include "..\Public\CLogManager.h"
#include <cmath>


CPlayer::~CPlayer()
{
    for (CItem* pItem : m_vecInventory)
        delete pItem;

    m_vecInventory.clear();

}

bool CPlayer::LevelUp()
{
    bool result = false;
	while (iExp >= 100)
	{
		iExp -= 100;
	    iLevel++;
        LevelUp_Stat();
        result = true;
	}
    //if (iLevel == 10)
    //    result = true;
    return result;
}

void CPlayer::LevelUp_Stat()
{
    int pre_level = 0, pre_attack = 0, pre_health = 0;


    pre_level = getLevel();
    pre_attack = getAttack();
    pre_health = getHealth_Max();

    iHealth_Max = iHealth_Max + (iLevel * 20);
    iHealth = iHealth_Max;
    iAttack += iLevel * 5;


    //bool LevelUp_result = m_pPlayer->Level)Up();

    wchar_t buffer[256];
    swprintf_s(buffer, 256, L"레벨업!  %d  -> %d", iLevel- 1, iLevel);
    CPrinter::PrintLine(buffer);
    swprintf_s(buffer, 256, L"공격력:  %d  -> %d", pre_attack, iAttack);
    CPrinter::PrintLine(buffer);
    swprintf_s(buffer, 256, L"체력:  %d  -> %d", pre_health, iHealth_Max);
    CPrinter::PrintLine(buffer);
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

    for (auto& invItem : m_vecInventory)
    {
        //CItem*      pItem = invItem;
        const FItemData* PItemData = invItem->Get_pItemData();
        if (!invItem) continue;

        std::wstring Equipped;
        std::wstring name   = invItem->GetName();
        int id              = invItem->GetID();
        int value           = invItem->GetValue();
        int quantity        = invItem->GetCurrentStack();
        bool* p_Equipped    = invItem->Get_pEquipped();

        // 이름/가격/수량/장착 상태
        swprintf_s(buffer, 256, L"이름: %ws | ID: %d | 가격: %d ,보유량 : %d ",
            name.c_str(), id, value, quantity);
        CPrinter::PrintLine(buffer);

        // 아이템 타입별 정보
        if (auto pPotion = dynamic_cast<const FItemPotionData*>(PItemData))
        {
            swprintf_s(buffer, 256, L"[포션] 회복량: %d", pPotion->healAmount);
        }
        else if (auto pWeapon = dynamic_cast<const FItemWeaponData*>(PItemData))
        {
            if (*p_Equipped == true)
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
        else if (auto pArmor = dynamic_cast<const FItemArmorData*>(PItemData))
        {
            if (*p_Equipped == true)
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
        const FItemData* PItemData = invItem->Get_pItemData();
        if (!PItemData) continue;

        std::wstring Equipped;
        std::wstring name = invItem->GetName();
        int id = invItem->GetID();
        int value = invItem->GetValue();
        int quantity = invItem->GetCurrentStack();
        bool* p_Equipped = invItem->Get_pEquipped();

        switch (i_arg)
        {
        case 1: // 포션
            if (auto pPotion = dynamic_cast<const FItemPotionData*>(PItemData))
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
            if (auto pWeapon = dynamic_cast<const FItemWeaponData*>(PItemData))
            {
                bFound = true;
                Equipped = *p_Equipped ? L"장착 ON" : L"장착 OFF";
                swprintf_s(buffer, 256, L"이름: %ws | ID: %d | 가격: %d | 수량: %d", name.c_str(), id, value, quantity);
                CPrinter::PrintLine(buffer);
                swprintf_s(buffer, 256, L"[무기] 공격력: %d, 방어력: %d, 체력: %d | %ws",
                    pWeapon->attackBonus, pWeapon->defenseBonus, pWeapon->healthBonus, Equipped.c_str());
                CPrinter::PrintLine(buffer);
                CPrinter::PrintLine(L"--------------------------------------------------------");
            }
            break;

        case 3: // 방어구
            if (auto pArmor = dynamic_cast<const FItemArmorData*>(PItemData))
            {
                bFound = true;
                Equipped = *p_Equipped ? L"장착 ON" : L"장착 OFF";
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

void CPlayer::Add_Inventory(CItem* Item)
{
    if (Item == nullptr)
        return;
    //m_vec
    for (auto& invItem : m_vecInventory)
    {
        if (invItem && invItem->GetID() == Item->GetID())
        {
            invItem->AddCurrentStack(1);
            return;
        }
    }

    m_vecInventory.push_back(Item);
}

void CPlayer::Add_Inventory_FItemData(FItemData* Item, int item_stock )
{
    if (Item == nullptr)
        return;
    //m_vec
    for (auto& invItem : m_vecInventory)
    {
        if (invItem->Get_pItemData() == Item)
        {
            invItem->AddCurrentStack(item_stock);
            return;
        }
    }

    CItem* new_Item = new CItem(Item);
    new_Item->SetCurrentStack(item_stock);
    m_vecInventory.push_back(new_Item);

}

int CPlayer::Sub_Inventory(int i_id, int i_num,bool b_sell)
{
    int result = 0;
    for (auto it = m_vecInventory.begin(); it != m_vecInventory.end(); ++it)
    {
        if (*it && (*it)->GetID() == i_id)
        {
            if ((*it)->GetCurrentStack() < i_num)
                return 0;

            if (b_sell)
                result = i_num * (*it)->GetValue();

            (*it)->AddCurrentStack(-i_num);  

            if ((*it)->GetCurrentStack() == 0)
                it = m_vecInventory.erase(it); 
            return result;
        }
    }


    return result;
}


void CPlayer::Equip(int i_arg)
{
    wchar_t buffer[256];

    for (auto& pair : m_vecInventory)
    {
        if (!pair)
            continue;

        const FItemData* pData = pair->Get_pItemData();

        if (pair->GetID() != i_arg)
            continue;

        // 무기인 경우
        if (const FItemWeaponData* WeaponData = dynamic_cast<const FItemWeaponData*>(pData))
        {
            // 먼저 기존 무기 해제
            for (auto& other : m_vecInventory)
            {
                if (other && other != pair && other->IsEquipped())
                {
                    const FItemData* otherData = other->Get_pItemData();
                    if (dynamic_cast<const FItemWeaponData*>(otherData))
                    {
                        other->SetEquipped(false);
                        iAttack     -= dynamic_cast<const FItemWeaponData*>(otherData)->attackBonus;
                        iArmor      -= dynamic_cast<const FItemWeaponData*>(otherData)->defenseBonus;
                        iHealth_Max -= dynamic_cast<const FItemWeaponData*>(otherData)->healthBonus;
                        iHealth     -= dynamic_cast<const FItemWeaponData*>(otherData)->healthBonus;
                    }
                }
            }

            // 장착 or 해제
            if (!pair->IsEquipped()) //장착!
            {
                pair->SetEquipped(true);
                iAttack         += WeaponData->attackBonus;
                iArmor          += WeaponData->defenseBonus;
                iHealth_Max     += WeaponData->healthBonus;
                iHealth         += WeaponData->healthBonus;

                
                // 장착시 로그
                swprintf_s(buffer, 256, L"이름: %ws (을)를 장비하여 공격력: %d, 방어력 : %d ,체력: %d 을 얻습니다.",
                    (WeaponData->name).c_str(), WeaponData->attackBonus, WeaponData->defenseBonus, WeaponData->healthBonus);
                CPrinter::PrintLine(buffer);
                CLogManager::getInstance().AddLog(buffer);
            }
            else //해제!
            {
                pair->SetEquipped(false);
                iAttack     -= WeaponData->attackBonus;
                iArmor      -= WeaponData->defenseBonus;
                iHealth_Max -= WeaponData->healthBonus;
                iHealth     -= WeaponData->healthBonus;
            }
            return;
        }

        // 방어구인 경우
        else if (const FItemArmorData* ArmorData = dynamic_cast<const FItemArmorData*>(pData))
        {
            // 기존 방어구 해제
            for (auto& other : m_vecInventory)
            {
                if (other && other != pair && other->IsEquipped())
                {
                    const FItemData* otherData = other->Get_pItemData();
                    if (dynamic_cast<const FItemArmorData*>(otherData))
                    {
                        other->SetEquipped(false);
                        iArmor          -= dynamic_cast<const FItemArmorData*>(otherData)->defenseBonus;
                        iHealth_Max     -= dynamic_cast<const FItemArmorData*>(otherData)->healthBonus;
                        iHealth         -= dynamic_cast<const FItemArmorData*>(otherData)->healthBonus;
                    }
                }
            }

            // 장착 or 해제
            if (!pair->IsEquipped())
            {
                pair->SetEquipped(true);
                iArmor      += ArmorData->defenseBonus;
                iHealth_Max += ArmorData->healthBonus;
                iHealth     += ArmorData->healthBonus;

                // 장착시 로그
                swprintf_s(buffer, 256, L"이름: %ws (을)를 장비하여 , 방어력 : %d ,체력: %d 을 얻습니다.",
                    (ArmorData->name).c_str(), ArmorData->defenseBonus, ArmorData->healthBonus);
                CPrinter::PrintLine(buffer);
                CLogManager::getInstance().AddLog(buffer);
            }
            else
            {
                pair->SetEquipped(false);
                iArmor      -= ArmorData->defenseBonus;
                iHealth_Max -= ArmorData->healthBonus;
                iHealth     -= ArmorData->healthBonus;
            }
            return;
        }

        // 포션인 경우
        else if (const FItemPotionData* PotionData = dynamic_cast<const FItemPotionData*>(pData))
        {
            UsePotion(i_arg);
            return;
        }
    }
}



void CPlayer::UsePotion(int i_arg)
{
    wchar_t buffer[256];

    for (auto it = m_vecInventory.begin(); it != m_vecInventory.end(); )
    {
        CItem* pair = *it;
        if (pair&& pair->GetID() == i_arg)
        {
            const FItemData* PItemData = pair->Get_pItemData();
            if (const FItemPotionData* PotionData = dynamic_cast<const FItemPotionData*>(PItemData))
            {
                if (pair->GetCurrentStack() > 0)
                {
                    int Potion_Heal = PotionData->healAmount;

                    iHealth += Potion_Heal;
                    if (iHealth >= iHealth_Max)
                    {
                        iHealth = iHealth_Max;
                    }
                    swprintf_s(buffer, 256, L"포션을 마셔 체력을 회복합니다 ");
                    CPrinter::PrintLine(buffer);
                    swprintf_s(buffer, 256, L"체력: %d / %d ",iHealth, iHealth_Max);
                    CPrinter::PrintLine(buffer);
                    pair->AddCurrentStack(-1);

                    //0되면 삭제
                    if (pair->GetCurrentStack() == 0)
                    {
                        delete pair;
                        it = m_vecInventory.erase(it); //벡터에서도 삭제;
                        //pair = nullptr; //포인트 삭제
                        break;
                    }
                }
                else {
                    CPrinter::PrintLine(L"포션이 부족합니다");
                }

            }
        }

        ++it;

    }
}

void CPlayer::Sell_item(int item_id, int item_stock)
{
    wchar_t buffer[256];

    bool b_sell = false;
    for (auto it = m_vecInventory.begin(); it != m_vecInventory.end(); )
    {
        CItem* pair = *it;
        if (pair && pair->GetID() == item_id)
        {
            const FItemData* PItemData = pair->Get_pItemData();

            if (pair->IsEquipped() == true)
            {
                CPrinter::PrintLine(L"장착한 아이템은 팔 수 없습니다.");
                CPrinter::Pause();
            }
            else
            {
                if (pair->GetCurrentStack() >= item_stock && b_sell == false)
                {

                    b_sell = true;
                    int item_price = pair->GetValue();
                    int sell_price = static_cast<int>(std::round(item_price * 0.6f));
                    iGold += sell_price * item_stock;

                    swprintf_s(buffer, 256, L"%ws 의 판매금액의 합은 %d 입니다.", pair->GetName().c_str(), sell_price * item_stock);
                    CPrinter::PrintLine(buffer);
                    CLogManager::getInstance().AddLog(buffer);
                    pair->AddCurrentStack(-1 * item_stock);
                    CPrinter::Pause();
                    //0되면 삭제
                    if (pair->GetCurrentStack() == 0)
                    {
                        delete pair;
                        it = m_vecInventory.erase(it); //벡터에서도 삭제;
                        //pair = nullptr; //포인트 삭제
                        break;
                    }
                }
                else
                {
                    CPrinter::PrintLine(L"판매할 아이템이 부족합니다");
                    CPrinter::Pause();

                }
            }
   

            
        }

        ++it;

    }


}

std::vector<CItem*> CPlayer::GetHaveItems()
{
    vector<CItem*> returnVector;

    for (CItem* item : m_vecInventory)
    {
        // 사용할 수 있는 아이템인지 확인
        if (item->Get_pItemData()->IsUseAble())
        {
            returnVector.push_back(item);
        }
    }
    return returnVector;
}

void CPlayer::UseItem(CItem* item)
{
    if (item->GetCurrentStack() > 0)
    {
        const FItemData* data = item->Get_pItemData();
        const FItemPotionData* potionData = dynamic_cast<const FItemPotionData*>(data);
        if (potionData)
        {
            UsePotion(potionData->id);
        }
    }
}
