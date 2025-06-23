#include <vector>
#include <string>
#include "..\public/CGameManager.h"

#include "CGameView.h"

int main()
{
    CGameManager* pGameMgr = CGameManager::GetInstance();

    pGameMgr->Main();

    pGameMgr->DestroyInstance();

    

    return 0;
}
