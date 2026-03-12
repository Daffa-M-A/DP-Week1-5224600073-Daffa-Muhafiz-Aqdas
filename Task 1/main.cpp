#include <iostream>
#include <cstdlib>
#include <ctime>

#include "PokerRules.h"
#include "ConcreteRules.h"
#include "DynamicModifiers.h"
#include "ShopSystem.h"
#include "RunSession.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));

    SmartPokerInputGenerator defaultPokerInput; 
    EqualRewardRule defaultReward;
    PokerScoringRule pokerScoring; 

    RandomPokerInputGenerator modRandomInput; 
    PlusTwoRewardRule modPlusTwoReward;

    DynamicInputGenerator dynInput(&defaultPokerInput);
    DynamicRewardRule dynReward(&defaultReward);

    ShopSystem shop(&dynInput, &dynReward, &modRandomInput, &modPlusTwoReward);
    RunSession session(&dynInput, &pokerScoring, &dynReward, &shop);

    session.Run();

    return 0;
}