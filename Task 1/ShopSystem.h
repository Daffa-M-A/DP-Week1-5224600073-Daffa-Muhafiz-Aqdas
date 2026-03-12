#pragma once
#include "DynamicModifiers.h"

class ShopSystem {
private:
    DynamicInputGenerator* dynInput;
    DynamicRewardRule* dynReward;
    
    IInputGenerator* modifierRandom;
    IRewardRule* modifierReward;
    
    int shopPhaseCount;

public:
    ShopSystem(DynamicInputGenerator* di, DynamicRewardRule* dr, IInputGenerator* modIn, IRewardRule* modRew);
    void EnterShop(int& money);
};