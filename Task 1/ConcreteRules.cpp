#include "ConcreteRules.h"
#include <cstdlib>

TurnInput RandomInputGenerator::Generate() {
    Card randomCard = { rand() % 10 + 1, "Random" };
    return { 1, { randomCard }, "Random Card Mechanic" };
}

int EqualRewardRule::ComputeReward(int baseScore) {
    return baseScore;
}

int PlusTwoRewardRule::ComputeReward(int baseScore) {
    return baseScore + 2; 
}