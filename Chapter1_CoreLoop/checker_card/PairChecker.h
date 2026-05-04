#pragma once
#include "../PokerHandChecker.h"

class PairChecker : public PokerHandChecker {
public:
    HandRank check(const ChosenHand& hand) override;
};
