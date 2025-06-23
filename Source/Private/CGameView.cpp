#include "CGameView.h"
#include "define.h"

using std::vector;
using std::unique_ptr;
using std::wstring;

void CGameView::ViewLogs(const std::vector<std::unique_ptr<ILogable>>& logs)

{
    vector<wstring> wrappedLog(logs.size() * 2);
    for (const unique_ptr<ILogable>& log : logs)
    {
        vector<wstring> wrapped = CPrinter::WrapText(log.get()->ToString(), 80); // 80은 박스 너비
        for (size_t i = 0; i < wrapped.size(); ++i)
        {
            if (i < wrappedLog.size())
            {
                wrappedLog[i] += wrapped[i];
            }
            else
            {
                wrappedLog.push_back(wrapped[i]);
            }
        }
    }
    CPrinter::PrintBoxes(wrappedLog, 80, wrappedLog.size() + 3, 1);
}

void CGameView::ViewGameState(const CGameManager& gameMgr)
{
    EGameState state = gameMgr.GetGameState();

    switch (state)
    {
    case EGameState::START:
        CPrinter::PrintLine(L"캐릭터 이름을 입력하세요 : ");
        break;
    case EGameState::IDLE:
        break;
    case EGameState::BATTLE:
        break;
    case EGameState::SELECT:
        break;
    case EGameState::SHOP:
        break;
    case EGameState::LEVELUP:
        break;
    case EGameState::INVENTORY:
        break;
    case EGameState::GAMEOVER:
        break;
    case EGameState::END:
        break;
    }
}

void CGameView::ViewObjectStat(const CGameObject& stat)
{
}

