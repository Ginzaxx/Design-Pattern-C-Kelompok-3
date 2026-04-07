#pragma once

#include "Hand.h"

// Tambah entry baru di sini kalau ada hand baru
enum class HandRank {
HIGH_CARD,
};

class PokerHandChecker{

public:

virtual HandRank check(const Hand& hand) = 0;

void setNext(PokerHandChecker* next);

protected:

PokerHandChecker* nextChecker = nullptr;

};
