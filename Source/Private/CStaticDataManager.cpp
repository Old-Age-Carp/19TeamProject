#include "CStaticDataManager.h"
#include "define.h"
#include "TSingleton.h"
#include <iostream>
#include <exception>
#include <utility>
#include <map>
#include <string>
#include <locale>
#include <memory>
//준식추가
#include "..\Public\CPrinter.h"
#include <algorithm>

bool CStaticDataManager::LoadAllStaticData()
{
    if (!LoadMonsterDataInternal())
    {
        std::wcerr << L"몬스터 데이터 로드 실패!" << std::endl;
        return false;
    }

    if (!LoadItemDataInternal())
    {
        std::wcerr << L"아이템 데이터 로드 실패!" << std::endl;
        return false;
    }

    if (!LoadDropTableDataInternal())
    {
        std::wcerr << L"드롭 테이블 데이터 로드 실패!" << std::endl;
        return false;
    }

    return true;
}

bool CStaticDataManager::LoadMonsterDataInternal()
{
    try
    {
        FMonsterData goblin =
        {
            101,
            L"고블린",
            10,
            50,
            EMonsterType::Normal,
            20,
            {1001}
        };
        monsterDataTable.insert({ goblin.name, goblin });
        monsterDataTableByID.insert({ goblin.id, goblin });

        FMonsterData orc =
        {
            102,
            L"오크",
            25,
            120,
            EMonsterType::Normal,
            50,
            {2001, 1001}
        };
        monsterDataTable.insert({ orc.name, orc });
        monsterDataTableByID.insert({ orc.id, orc });

        FMonsterData slime =
        {
            103,
            L"슬라임",
            5,
            30,
            EMonsterType::Normal,
            10,
            {3001}
        };
        monsterDataTable.insert({ slime.name, slime });
        monsterDataTableByID.insert({ slime.id, slime });

        FMonsterData zombie =
        {
            104,
            L"좀비",
            15,
            70,
            EMonsterType::Normal,
            30,
            {1001, 3001}
        };
        monsterDataTable.insert({ zombie.name, zombie });
        monsterDataTableByID.insert({ zombie.id, zombie });

        FMonsterData skeleton =
        {
            105,
            L"스켈레톤",
            20,
            60,
            EMonsterType::Normal,
            25,
            {2001}
        };
        monsterDataTable.insert({ skeleton.name, skeleton });
        monsterDataTableByID.insert({ skeleton.id, skeleton });

        FMonsterData golem =
        {
            106,
            L"골렘",
            40,
            200,
            EMonsterType::Normal,
            80,
            {3002, 1002}
        };
        monsterDataTable.insert({ golem.name, golem });
        monsterDataTableByID.insert({ golem.id, golem });

        FMonsterData lich =
        {
            107,
            L"리치",
            60,
            350,
            EMonsterType::Boss,
            300,
            {2002, 3002, 1002}
        };
        monsterDataTable.insert({ lich.name, lich });
        monsterDataTableByID.insert({ lich.id, lich });

        FMonsterData dragon =
        {
            108,
            L"드래곤",
            80,
            500,
            EMonsterType::Boss,
            500,
            {2003, 3003, 1002}
        };
        monsterDataTable.insert({ dragon.name, dragon });
        monsterDataTableByID.insert({ dragon.id, dragon });

        return true;
    }
    catch (const std::exception& e)
    {
        std::wcerr << L"몬스터 데이터 로드 중 오류 발생: " << e.what() << std::endl;
        return false;
    }
}

bool CStaticDataManager::LoadItemDataInternal()
{
    try
    {
        itemDataTableByID[1001] = std::make_unique<FItemPotionData>(1001, L"작은 물약", 10, 50);
        itemDataTableByName.insert({ L"작은 물약", itemDataTableByID[1001].get() });

        itemDataTableByID[1002] = std::make_unique<FItemPotionData>(1002, L"큰 물약", 30, 100);
        itemDataTableByName.insert({ L"큰 물약", itemDataTableByID[1002].get() });

        itemDataTableByID[2001] = std::make_unique<FItemWeaponData>(2001, L"철검", 20, 5, 0, 0);
        itemDataTableByName.insert({ L"철검", itemDataTableByID[2001].get() });

        itemDataTableByID[2002] = std::make_unique<FItemWeaponData>(2002, L"미스릴검", 50, 15, 5, 0);
        itemDataTableByName.insert({ L"미스릴검", itemDataTableByID[2002].get() });

        itemDataTableByID[2003] = std::make_unique<FItemWeaponData>(2003, L"전설의명검", 100, 50, 15, 50);
        itemDataTableByName.insert({ L"전설의명검", itemDataTableByID[2003].get() });

        itemDataTableByID[3001] = std::make_unique<FItemArmorData>(3001, L"낡은 도복", 20, 5, 0);
        itemDataTableByName.insert({ L"낡은 도복", itemDataTableByID[3001].get() });

        itemDataTableByID[3002] = std::make_unique<FItemArmorData>(3002, L"철 갑옷", 50, 30, 10);
        itemDataTableByName.insert({ L"철 갑옷", itemDataTableByID[3002].get() });

        itemDataTableByID[3003] = std::make_unique<FItemArmorData>(3003, L"불멸의흑갑", 100, 60, 100);
        itemDataTableByName.insert({ L"불멸의흑갑", itemDataTableByID[3003].get() });

        return true;
    }
    catch (const std::exception& e)
    {
        std::wcerr << L"아이템 데이터 로드 중 오류 발생: " << e.what() << std::endl;
        return false;
    }
}

FMonsterData* CStaticDataManager::GetMonsterData(const std::wstring& name)
{
    auto it = monsterDataTable.find(name);
    if (it != monsterDataTable.end())
    {
        return &(it->second);
    }
    return nullptr;
}

FMonsterData* CStaticDataManager::GetMonsterData(int id)
{
    auto it = monsterDataTableByID.find(id);
    if (it != monsterDataTableByID.end())
    {
        return &(it->second);
    }
    return nullptr;
}

FItemData* CStaticDataManager::GetItemData(const std::wstring& name)
{
    auto it = itemDataTableByName.find(name);
    if (it != itemDataTableByName.end())
    {
        return it->second;
    }
    return nullptr;
}

FItemData* CStaticDataManager::GetItemData(int id)
{
    auto it = itemDataTableByID.find(id);
    if (it != itemDataTableByID.end())
    {
        return it->second.get();
    }
    return nullptr;
}

FGameDropTable* CStaticDataManager::GetDropTable(int id)
{
    auto it = dropTableDataByID.find(id);
    if (it != dropTableDataByID.end())
    {
        return &it->second;
    }
    return nullptr;
}

void CStaticDataManager::Print_AllItem()
{
    CPrinter::PrintLine(L"========================================================");
    int item_id = 0, item_gold = 0, item_hp = 0, item_atk = 0, item_dep = 0;
    wchar_t buffer[256];
    std::wstring item_name;

    std::vector<int> sortedIDs;
    for (const auto& pair : itemDataTableByID)
    {
        sortedIDs.push_back(pair.first);
    }
    std::sort(sortedIDs.begin(), sortedIDs.end());

    for (int id : sortedIDs)
    {
        const FItemData* pItem = itemDataTableByID[id].get();

        item_id = pItem->id;
        item_gold = pItem->value;
        item_name = pItem->name;
        swprintf_s(buffer, 256, L"이름: %ws", item_name.c_str());
        CPrinter::PrintLine(buffer);
        swprintf_s(buffer, 256, L"ID : %d, 가격 : %d ", item_id, item_gold);
        CPrinter::PrintLine(buffer);

        if (auto pPotion = dynamic_cast<const FItemPotionData*>(pItem))
        {
            swprintf_s(buffer, 256, L"[포션] 회복량: %d", pPotion->healAmount);
            CPrinter::PrintLine(buffer);
        }
        else if (auto pWeapon = dynamic_cast<const FItemWeaponData*>(pItem))
        {
            swprintf_s(buffer, 256, L"[무기] 공격력: %d, 방어력: %d, 체력: %d",
                pWeapon->attackBonus, pWeapon->defenseBonus, pWeapon->healthBonus);
            CPrinter::PrintLine(buffer);
        }
        else if (auto pArmor = dynamic_cast<const FItemArmorData*>(pItem))
        {
            swprintf_s(buffer, 256, L"[방어구] 방어력: %d, 체력: %d",
                pArmor->defenseBonus, pArmor->healthBonus);
            CPrinter::PrintLine(buffer);
        }
    }

    CPrinter::PrintLine(L"========================================================");
}

bool CStaticDataManager::LoadDropTableDataInternal()
{
    try
    {
        FGameDropTable dropTable1001;
        dropTable1001.id = 1001;
        FDropItemData potionDropItem;
        potionDropItem.mItemIDList.push_back(1001);
        potionDropItem.mDropRate.push_back(300);
        dropTable1001.possibleDrops = potionDropItem;
        dropTableDataByID[dropTable1001.id] = dropTable1001;

        FGameDropTable dropTable1002;
        dropTable1002.id = 1002;
        FDropItemData bigPotionDropItem;
        bigPotionDropItem.mItemIDList.push_back(1002);
        bigPotionDropItem.mDropRate.push_back(200);
        dropTable1002.possibleDrops =(bigPotionDropItem);
        dropTableDataByID[dropTable1002.id] = dropTable1002;

        FGameDropTable dropTable2001;
        dropTable2001.id = 2001;
        FDropItemData ironSwordDropItem;
        ironSwordDropItem.mItemIDList.push_back(2001);
        ironSwordDropItem.mDropRate.push_back(150);
        dropTable2001.possibleDrops =(ironSwordDropItem);
        dropTableDataByID[dropTable2001.id] = dropTable2001;

        FGameDropTable dropTable2002;
        dropTable2002.id = 2002;
        FDropItemData mithrilSwordDropItem;
        mithrilSwordDropItem.mItemIDList.push_back(2002);
        mithrilSwordDropItem.mDropRate.push_back(100);
        dropTable2002.possibleDrops =(mithrilSwordDropItem);
        dropTableDataByID[dropTable2002.id] = dropTable2002;

        FGameDropTable dropTable2003;
        dropTable2003.id = 2003;
        FDropItemData legendarySwordDropItem;
        legendarySwordDropItem.mItemIDList.push_back(2003);
        legendarySwordDropItem.mDropRate.push_back(50);
        dropTable2003.possibleDrops =(legendarySwordDropItem);
        dropTableDataByID[dropTable2003.id] = dropTable2003;

        FGameDropTable dropTable3001;
        dropTable3001.id = 3001;
        FDropItemData oldRobeDropItem;
        oldRobeDropItem.mItemIDList.push_back(3001);
        oldRobeDropItem.mDropRate.push_back(250);
        dropTable3001.possibleDrops =(oldRobeDropItem);
        dropTableDataByID[dropTable3001.id] = dropTable3001;

        FGameDropTable dropTable3002;
        dropTable3002.id = 3002;
        FDropItemData ironArmorDropItem;
        ironArmorDropItem.mItemIDList.push_back(3002);
        ironArmorDropItem.mDropRate.push_back(150);
        dropTable3002.possibleDrops =(ironArmorDropItem);
        dropTableDataByID[dropTable3002.id] = dropTable3002;

        FGameDropTable dropTable3003;
        dropTable3003.id = 3003;
        FDropItemData immortalArmorDropItem;
        immortalArmorDropItem.mItemIDList.push_back(3003);
        immortalArmorDropItem.mDropRate.push_back(70);
        dropTable3003.possibleDrops =(immortalArmorDropItem);
        dropTableDataByID[dropTable3003.id] = dropTable3003;

        return true;
    }
    catch (const std::exception& e)
    {
        std::wcerr << L"드롭 테이블 데이터 로드 중 오류 발생: " << e.what() << std::endl;
        return false;
    }
}
