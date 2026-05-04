#pragma once
#include "../PokerHandChecker.h"

class ThreeOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const ChosenHand& hand) override;
};
