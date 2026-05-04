#pragma once
#include "../PokerHandChecker.h"

class HighCardChecker : public PokerHandChecker {
public:
    HandRank check(const ChosenHand& hand) override;
};
