#pragma once

#include "Hand.h"

// Tambah entry baru di sini kalau ada hand baru
enum class HandRank {
HIGH_CARD,
PAIR,
TWO_PAIR,
THREE_OF_A_KIND,
STRAIGHT,
FLUSH,
FULL_HOUSE,
FOUR_OF_A_KIND,
STRAIGHT_FLUSH,
ROYAL_FLUSH,
FIVE_OF_A_KIND,
FLUSH_HOUSE,
};

class PokerHandChecker{

public:

virtual HandRank check(const Hand& hand) = 0;

void setNext(PokerHandChecker* next);

protected:

PokerHandChecker* nextChecker = nullptr;

};
