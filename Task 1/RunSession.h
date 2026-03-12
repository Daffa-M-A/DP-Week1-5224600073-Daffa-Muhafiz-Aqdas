#pragma once
#include "Interfaces.h"
#include "ShopSystem.h"

class RunSession {
private:
    IInputGenerator* inputGen;
    IScoringRule* scoringRule;
    IRewardRule* rewardRule;
    ShopSystem* shop;
    int money;

public:
    RunSession(IInputGenerator* ig, IScoringRule* sr, IRewardRule* rr, ShopSystem* ss);
    void Run();
};