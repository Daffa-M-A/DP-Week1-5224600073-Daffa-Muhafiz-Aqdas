#include "RunSession.h"
#include <iostream>

using namespace std;

RunSession::RunSession(IInputGenerator* ig, IScoringRule* sr, IRewardRule* rr, ShopSystem* ss)
    : inputGen(ig), scoringRule(sr), rewardRule(rr), shop(ss), money(0) {}

void RunSession::Run() {
    cout << "=== RUN START ===\n";
    
    for (int round = 1; round <= 3; ++round) {
        cout << "Round " << round << "\n";

        TurnInput input = inputGen->Generate();
        cout << "[PLAY] input generated: " << input.value << "\n";

        int baseScore = scoringRule->ComputeBaseScore(input);
        cout << "[SCORE] base score: " << baseScore << "\n";

        int reward = rewardRule->ComputeReward(baseScore);
        
        money += reward;
        cout << "[REWARD] gain: " << reward << " | money: " << money << "\n";

        shop->EnterShop(money);
        
        cout << "\n";
    }

    cout << "=== RUN END ===\n";
    cout << "Final money: " << money << "\n";
}