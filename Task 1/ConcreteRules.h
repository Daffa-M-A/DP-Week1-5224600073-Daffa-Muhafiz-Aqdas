#pragma once
#include "Interfaces.h"

class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput Generate() override;
};

class EqualRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore) override;
};

class PlusTwoRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore) override;
};