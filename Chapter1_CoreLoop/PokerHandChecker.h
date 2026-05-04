#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include "ChosenHand.h"

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

virtual HandRank check(const ChosenHand& hand) = 0;

void setNext(PokerHandChecker* next);

protected:

PokerHandChecker* nextChecker = nullptr;

// Helpers for subclasses
std::map<int, int> countRanks(const ChosenHand& hand);
std::map<char, int> countSuits(const ChosenHand& hand);
bool isStraight(const ChosenHand& hand);
bool isFlush(const ChosenHand& hand);

};
