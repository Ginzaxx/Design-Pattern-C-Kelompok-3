#pragma once
#include "../PokerHandChecker.h"

class RoyalFlushChecker : public PokerHandChecker {
public:
    HandRank check(const ChosenHand& hand) override;
};
