#pragma once
#include "Interfaces.h"

class DynamicInputGenerator : public IInputGenerator {
private:
    IInputGenerator* currentStrategy;
public:
    DynamicInputGenerator(IInputGenerator* initial) : currentStrategy(initial) {}
    
    void SetStrategy(IInputGenerator* newStrategy) {
        currentStrategy = newStrategy;
    }

    TurnInput Generate() override {
        return currentStrategy->Generate(); 
    }
};

class DynamicRewardRule : public IRewardRule {
private:
    IRewardRule* currentStrategy;
public:
    DynamicRewardRule(IRewardRule* initial) : currentStrategy(initial) {}

    void SetStrategy(IRewardRule* newStrategy) {
        currentStrategy = newStrategy;
    }

    int ComputeReward(int baseScore) override {
        return currentStrategy->ComputeReward(baseScore);
    }
};