#pragma once

#include "Hand.h"
#include "PokerHandChecker.h"
#include "HighCardChecker.h"

// ============================================================
// Cara tambah checker baru:
// 1. #include "MyChecker.h" di sini
// 2. Tambah member: MyChecker myChecker;
// ============================================================

class ScoringRule{

public:

ScoringRule();

int scoreHand(const Hand& hand);

private:

// ============================================================
// Urutan chain: checker tertinggi dulu, HighCard selalu terakhir
// Tambah checker baru di atas highCardChecker
// Contoh:
//   FlushChecker flushChecker;
//   PairChecker pairChecker;
//   HighCardChecker highCardChecker;
// ============================================================
HighCardChecker highCardChecker;

int convertRankToScore(HandRank rank);

};
