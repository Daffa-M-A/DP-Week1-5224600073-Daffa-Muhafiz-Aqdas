#include "ShopSystem.h"
#include <iostream>

using namespace std;

ShopSystem::ShopSystem(DynamicInputGenerator* di, DynamicRewardRule* dr, IInputGenerator* modIn, IRewardRule* modRew)
    : dynInput(di), dynReward(dr), modifierRandom(modIn), modifierReward(modRew), shopPhaseCount(1) {}

void ShopSystem::EnterShop(int& money) {
    cout << "[SHOP] Welcome! Shop Phase: " << shopPhaseCount << "\n";
    
    if (shopPhaseCount == 1) {
        cout << "[SHOP] Offered: [Random Input Generator Modifier] | Cost: 0\n";
        cout << "[SHOP] Action: Modifier Acquired! (Will be active in Round 2)\n";
        dynInput->SetStrategy(modifierRandom);
    } 
    else if (shopPhaseCount == 2) {
        cout << "[SHOP] Offered: [Reward +2 Modifier] | Cost: 0\n";
        cout << "[SHOP] Action: Modifier Acquired! (Will be active in Round 3)\n";
        dynReward->SetStrategy(modifierReward);
    }
    else {
        cout << "[SHOP] Shop is empty.\n";
    }
    
    shopPhaseCount++;
}