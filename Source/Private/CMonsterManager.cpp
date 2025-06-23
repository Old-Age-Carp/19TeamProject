#include "CMonsterManager.h" 
#include "CMonster.h"       
#include <iostream>           
#include <unordered_map>                 

const FMonsterData* CMonsterManager::GetMonsterData(int id) const
{
    auto it = monsterDataTableByID.find(id); // ID 기반 맵에서 검색
    if (it != monsterDataTableByID.end())
    {
        return &(it->second);
    }
    return nullptr; 
}


bool CMonsterManager::LoadMonsterData()
{
    
    try
    {
        FMonsterData goblin = {
            101,
            L"고블린",
            10,
            50,
            EMonsterType::Normal,
            20,
            {1001}
        }; // 드롭 아이템 ID 1001 (작은 물약)
        monsterDataTable.insert({ goblin.name, goblin }); 
        monsterDataTableByID.insert({ goblin.id, goblin });

        FMonsterData orc = {
            102,
            L"오크",
            25,
            120,
            EMonsterType::Normal,
            50,
            {2001, 1001}
        }; // 드롭 아이템 ID 2001 (철검), 1001 (작은 물약)
        monsterDataTable.insert({ orc.name, orc });
        monsterDataTableByID.insert({ orc.id, orc });

        FMonsterData slime = {
            103,
            L"슬라임",
            5,
            30,
            EMonsterType::Normal,
            10,
            {}
        }; // 드롭 아이템 없음
        monsterDataTable.insert({ slime.name, slime });
        monsterDataTableByID.insert({ slime.id, slime });

        FMonsterData zombie = {
            104,
            L"좀비",
            15,
            70,
            EMonsterType::Normal,
            30,
            {1001, 3001}
        }; // 작은 물약, 낡은 도복
        monsterDataTable.insert({ zombie.name, zombie });
        monsterDataTableByID.insert({ zombie.id, zombie });

        FMonsterData skeleton = {
            105,
            L"스켈레톤",
            20,
            60,
            EMonsterType::Normal,
            25,
            {2001}
        }; // 철검
        monsterDataTable.insert({ skeleton.name, skeleton });
        monsterDataTableByID.insert({ skeleton.id, skeleton });

        FMonsterData golem = {
            106,
            L"골렘",
            40,
            200,
            EMonsterType::Normal,
            80,
            {3002, 1002}
        }; // 철 갑옷, 큰 물약
        monsterDataTable.insert({ golem.name, golem });
        monsterDataTableByID.insert({ golem.id, golem });

        FMonsterData lich = {
            107,
            L"리치",
            60,
            350,
            EMonsterType::Boss,
            300,
            {2002, 3002, 1002}
        }; // 미스릴검, 철 갑옷, 큰 물약
        monsterDataTable.insert({ lich.name, lich });
        monsterDataTableByID.insert({ lich.id, lich });

        FMonsterData dragon = {
            108,
            L"드래곤",
            80,
            500,
            EMonsterType::Boss,
            500,
            {2003, 3003, 1002}
        }; // 전설의명검, 불멸의흑갑, 큰 물약
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


const FMonsterData* CMonsterManager::GetMonsterData(const std::wstring& name) const
{
    auto it = monsterDataTable.find(name);
    if (it != monsterDataTable.end())
    {
        return &(it->second);
    }
        return nullptr;
    
}
