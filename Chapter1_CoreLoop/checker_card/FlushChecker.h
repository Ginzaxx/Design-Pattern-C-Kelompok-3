#pragma once
#include "PokerHandChecker.h"
class FlushChecker : public PokerHandChecker{
public:
HandRank check(const ChosenHand& hand) override;
};
