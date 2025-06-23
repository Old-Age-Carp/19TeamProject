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
            {}
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

const FMonsterData* CStaticDataManager::GetMonsterData(const std::wstring& name) const
{
    auto it = monsterDataTable.find(name);
    if (it != monsterDataTable.end())
    {
        return &(it->second);
    }
    return nullptr;
}

const FMonsterData* CStaticDataManager::GetMonsterData(int id) const
{
    auto it = monsterDataTableByID.find(id);
    if (it != monsterDataTableByID.end())
    {
        return &(it->second);
    }
    return nullptr;
}

const FItemData* CStaticDataManager::GetItemData(int id) const
{
    auto it = itemDataTableByID.find(id);
    if (it != itemDataTableByID.end())
    {
        return it->second.get();
    }
    return nullptr;
}

const FItemData* CStaticDataManager::GetItemData(const std::wstring& name) const
{
    auto it = itemDataTableByName.find(name); 
    if (it != itemDataTableByName.end())
    {
        return it->second; 
    }
    return nullptr;
}
