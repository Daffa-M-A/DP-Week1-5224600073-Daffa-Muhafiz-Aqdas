#pragma once
#include <vector>
#include <string>

struct Card {
    int value; 
    std::string suit; 
};

struct TurnInput {
    int value; 
    std::vector<Card> comboCards;
    std::string comboName;
};

class IInputGenerator {
public:
    virtual TurnInput Generate() = 0;
    virtual ~IInputGenerator() = default;
};

class IScoringRule {
public:
    virtual int ComputeBaseScore(TurnInput input) = 0;
    virtual ~IScoringRule() = default;
};

class IRewardRule {
public:
    virtual int ComputeReward(int baseScore) = 0;
    virtual ~IRewardRule() = default;
};