#pragma once
#include "../PokerHandChecker.h"

class StraightChecker : public PokerHandChecker {
public:
    HandRank check(const ChosenHand& hand) override;
};
