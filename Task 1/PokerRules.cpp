#include "PokerRules.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <ctime>
#include <cstdlib>

using namespace std;

BasePokerGenerator::BasePokerGenerator() {
    InitializeDeck();
}

void BasePokerGenerator::InitializeDeck() {
    deck.clear();
    string suits[] = { "Spades", "Hearts", "Clubs", "Diamonds" };
    for (const string& suit : suits) {
        for (int val = 1; val <= 10; ++val) {
            deck.push_back({ val, suit });
        }
    }
}

TurnInput BasePokerGenerator::EvaluateCombo(vector<Card> pool) {
    if (pool.empty()) return { 0, {}, "None" };

    sort(pool.begin(), pool.end(), [](const Card& a, const Card& b) {
        return a.value > b.value;
    });

    map<int, vector<Card>> valGroups;
    map<string, vector<Card>> suitGroups;
    for (const auto& card : pool) {
        valGroups[card.value].push_back(card);
        suitGroups[card.suit].push_back(card);
    }

    auto findStraight = [](const vector<Card>& sortedCards) -> vector<Card> {
        vector<Card> st;
        if (sortedCards.empty()) return st;
        st.push_back(sortedCards[0]);
        for (size_t i = 1; i < sortedCards.size(); ++i) {
            if (sortedCards[i].value == st.back().value - 1) {
                st.push_back(sortedCards[i]);
                if (st.size() == 5) return st;
            } else if (sortedCards[i].value != st.back().value) {
                st.clear();
                st.push_back(sortedCards[i]);
            }
        }
        return {};
    };

    for (auto& sg : suitGroups) {
        if (sg.second.size() >= 5) {
            vector<Card> suitCards = sg.second;
            sort(suitCards.begin(), suitCards.end(), [](const Card& a, const Card& b) { return a.value > b.value; });
            vector<Card> sf = findStraight(suitCards);
            if (sf.size() == 5) return { 5, sf, "Straight Flush" };
        }
    }

    for (auto it = valGroups.rbegin(); it != valGroups.rend(); ++it) {
        if (it->second.size() >= 4) {
            return { 4, vector<Card>(it->second.begin(), it->second.begin() + 4), "Four of a Kind" };
        }
    }

    vector<Card> fh3, fh2;
    for (auto it = valGroups.rbegin(); it != valGroups.rend(); ++it) {
        if (it->second.size() >= 3 && fh3.empty()) {
            fh3 = vector<Card>(it->second.begin(), it->second.begin() + 3);
        } else if (it->second.size() >= 2 && fh2.empty()) {
            fh2 = vector<Card>(it->second.begin(), it->second.begin() + 2);
        }
    }
    if (!fh3.empty() && !fh2.empty()) {
        fh3.insert(fh3.end(), fh2.begin(), fh2.end());
        return { 5, fh3, "Full House" };
    }

    for (auto& sg : suitGroups) {
        if (sg.second.size() >= 5) {
            vector<Card> flushCards = sg.second;
            sort(flushCards.begin(), flushCards.end(), [](const Card& a, const Card& b) { return a.value > b.value; });
            flushCards.resize(5); 
            return { 5, flushCards, "Flush" };
        }
    }

    vector<Card> uniqueVals; 
    for (auto it = valGroups.rbegin(); it != valGroups.rend(); ++it) {
        uniqueVals.push_back(it->second[0]);
    }
    vector<Card> st = findStraight(uniqueVals);
    if (st.size() == 5) return { 5, st, "Straight" };

    for (auto it = valGroups.rbegin(); it != valGroups.rend(); ++it) {
        if (it->second.size() >= 3) {
            return { 3, vector<Card>(it->second.begin(), it->second.begin() + 3), "Three of a Kind" };
        }
    }

    vector<vector<Card>> pairs;
    for (auto it = valGroups.rbegin(); it != valGroups.rend(); ++it) {
        if (it->second.size() >= 2) {
            pairs.push_back(vector<Card>(it->second.begin(), it->second.begin() + 2));
        }
    }
    if (pairs.size() >= 2) {
        vector<Card> twoPair = pairs[0];
        twoPair.insert(twoPair.end(), pairs[1].begin(), pairs[1].end());
        return { 4, twoPair, "Two Pair" };
    }

    if (pairs.size() == 1) return { 2, pairs[0], "Pair" };

    return { 1, { pool[0] }, "High Card" };
}


TurnInput SmartPokerInputGenerator::Generate() {
    if (deck.size() < 8) InitializeDeck();

    vector<Card> hand;
    for (int i = 0; i < 8; ++i) {
        int r = rand() % deck.size();
        hand.push_back(deck[r]);
        deck.erase(deck.begin() + r);
    }

    cout << "\n[SMART POKER] Hand (8 Cards):\n";
    for (const auto& c : hand) cout << " [" << c.value << " " << c.suit << "]";
    cout << "\n";

    TurnInput result = EvaluateCombo(hand);
    
    cout << "[SMART PLAY] Detected best combo: " << result.comboName << " -> ";
    for (const auto& c : result.comboCards) cout << "[" << c.value << " " << c.suit << "] ";
    cout << "\n";

    return result;
}

TurnInput RandomPokerInputGenerator::Generate() {
    if (deck.size() < 8) InitializeDeck();

    vector<Card> hand;
    for (int i = 0; i < 8; ++i) {
        int r = rand() % deck.size();
        hand.push_back(deck[r]);
        deck.erase(deck.begin() + r);
    }

    cout << "\n[RANDOM POKER] Hand (8 Cards):\n";
    for (const auto& c : hand) cout << " [" << c.value << " " << c.suit << "]";
    cout << "\n";

    int cardsToPlay = rand() % 5 + 1;
    vector<Card> playedCards;
    vector<Card> tempHand = hand;

    for(int i = 0; i < cardsToPlay; ++i) {
        int r = rand() % tempHand.size();
        playedCards.push_back(tempHand[r]);
        tempHand.erase(tempHand.begin() + r);
    }

    cout << "[BLIND PLAY] Playing " << cardsToPlay << " random cards: ";
    for (const auto& c : playedCards) cout << "[" << c.value << " " << c.suit << "] ";
    cout << "\n";

    TurnInput result = EvaluateCombo(playedCards);
    
    cout << "[RESULTING COMBO] " << result.comboName << " -> ";
    for (const auto& c : result.comboCards) cout << "[" << c.value << " " << c.suit << "] ";
    cout << "\n";

    return result;
}


int PokerScoringRule::ComputeBaseScore(TurnInput input) {
    int sum = 0;
    for (const auto& card : input.comboCards) sum += card.value;
    int multiplier = input.comboCards.size();
    
    cout << "[CALCULATION] (" << sum << " total value) * (" << multiplier << " multiplier)\n";
    return sum * multiplier;
}