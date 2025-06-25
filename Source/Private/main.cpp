#include <vector>
#include <string>
#include "..\public/CGameManager.h"

#include "CGameView.h"
#include <fcntl.h>      // _O_U16TEXT
#include <io.h>         // _setmode
int main()
{
    // 콘솔 스트림을 UTF-16 모드로 변경
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    CGameManager* pGameMgr = CGameManager::GetInstance();

    while (*pGameMgr->Get_pGameRunning())
    {
        pGameMgr->Main();
    }


    pGameMgr->DestroyInstance();

    

    return 0;
}
