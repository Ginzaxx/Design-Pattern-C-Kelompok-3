#pragma once
#include "PokerHandChecker.h"
class FlushHouseChecker : public PokerHandChecker{
public:
HandRank check(const ChosenHand& hand) override;
};
