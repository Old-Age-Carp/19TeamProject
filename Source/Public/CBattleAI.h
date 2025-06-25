#pragma once
#include "define.h"
#include <vector>
class CBattleAbleObject;
class CIsBattleAble;

class IBattleAI
{
public :

    virtual ~IBattleAI() = default;
    virtual EActionKind Think() = 0;
    virtual CBattleAbleObject* ThinkTarget(EActionKind action, std::vector<CIsBattleAble*> otherTeams) = 0;
};

class CBattleAI : public IBattleAI
{
private:
    CBattleAbleObject* battler;
    CBattleAI();
public:
    CBattleAI(CBattleAbleObject* _battleObj) : battler(_battleObj) {}
    EActionKind Think(); // 뭘 해야할지 결정
    CBattleAbleObject* ThinkTarget(EActionKind action,
        std::vector<CIsBattleAble*> otherTeams); // 어떤 행동을 할 때 대상 지정
};
