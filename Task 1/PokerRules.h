#pragma once
#include "Interfaces.h"
#include <vector>

class BasePokerGenerator : public IInputGenerator {
protected:
    std::vector<Card> deck;
    void InitializeDeck();
    TurnInput EvaluateCombo(std::vector<Card> pool); 

public:
    BasePokerGenerator();
    virtual TurnInput Generate() = 0; 
};

class SmartPokerInputGenerator : public BasePokerGenerator {
public:
    TurnInput Generate() override;
};

class RandomPokerInputGenerator : public BasePokerGenerator {
public:
    TurnInput Generate() override;
};

class PokerScoringRule : public IScoringRule {
public:
    int ComputeBaseScore(TurnInput input) override;
};