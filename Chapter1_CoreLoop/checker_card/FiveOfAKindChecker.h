#pragma once
#include "PokerHandChecker.h"
class FiveOfAKindChecker : public PokerHandChecker{
public:
HandRank check(const ChosenHand& hand) override;
};
