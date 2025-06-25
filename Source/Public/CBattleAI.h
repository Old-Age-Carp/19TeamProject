#pragma once
#include "define.h"
#include <vector>
class CBattleAbleObject;
class CIsBattleAble;

class CBattleAI
{
private:
    CBattleAbleObject* battler;
    CIsBattleAble* team;
public:
    CBattleAI(CBattleAbleObject* _battleObj, CIsBattleAble* _team) : battler(_battleObj), team(_team) {}
    EActionKind Think(); // 뭘 해야할지 결정
    CBattleAbleObject* ThinkTarget(EActionKind action, std::vector<CIsBattleAble*> otherTeams); // 어떤 행동을 할 때 대상 지정
};
