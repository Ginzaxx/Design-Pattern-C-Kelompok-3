#pragma once
#include "../PokerHandChecker.h"

class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank check(const ChosenHand& hand) override;
};
