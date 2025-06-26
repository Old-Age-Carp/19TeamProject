#include "CGameView.h"
#include "define.h"
#include <memory>

using std::vector;
using std::unique_ptr;
using std::wstring;
using std::to_wstring;

void CGameView::ViewLogs(const std::vector<std::unique_ptr<ILogable>>& logs)
{
    for (int i = 0; i < logs.size(); i++)
        CPrinter::PrintLine(logs[i]->ToString());
}

void CGameView::ViewLogs(const vector<ILogable*>& logs)
{
    for (const ILogable* log : logs)
        CPrinter::PrintLine(log->ToString());
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
    case EGameState::INVENTORY:
        break;
    case EGameState::GAMEOVER:
        break;
    case EGameState::END:
        break;
    }
}

void CGameView::ViewObjectStat(const CGameObject& gameObject)
{
    CPrinter::PrintLine(L"이름 :" + gameObject.getName());
    CPrinter::PrintLine(L"레벨 :" + to_wstring(gameObject.getLevel()));
    CPrinter::PrintLine(L"체력 :" + to_wstring(gameObject.getHealth()));
    CPrinter::PrintLine(L"공격 :" + to_wstring(gameObject.getAttack()));
    CPrinter::PrintLine(L"방어 :" + to_wstring(gameObject.getArmor()));   
}

