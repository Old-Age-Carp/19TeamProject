#include <vector>
#include <string>
#include "..\public/CGameManager.h"

#include "CGameView.h"

int main()
{
    /*CGameManager* pGameMgr = CGameManager::GetInstance();

    pGameMgr->Main();

    pGameMgr->DestroyInstance();*/

    CGameView view;
    CGameObject obj
    {
        L"아무개",
    };

    view.ViewObjectStat(obj);

    return 0;
}
