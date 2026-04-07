#pragma once

#include "Hand.h"
#include "PokerHandChecker.h"
#include "RoyalFlushChecker.h"
#include "StraightFlushChecker.h"
#include "FourOfAKindChecker.h"
#include "FiveOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushHouseChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfAKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
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
//   RoyalFlushChecker royalFlushChecker;
//   StraightFlushChecker straightFlushChecker;
//   FourOfAKindChecker fourOfAKindChecker;
//   FullHouseChecker fullHouseChecker;
//   FlushHouseChecker flushHouseChecker;
//   FlushChecker flushChecker;
//   StraightChecker straightChecker;
//   ThreeOfAKindChecker threeOfAKindChecker;
//   TwoPairChecker twoPairChecker;
//   PairChecker pairChecker;
//   HighCardChecker highCardChecker;
// ============================================================
RoyalFlushChecker royalFlushChecker;
FiveOfAKindChecker fiveOfAKindChecker;
StraightFlushChecker straightFlushChecker;
FourOfAKindChecker fourOfAKindChecker;
FullHouseChecker fullHouseChecker;
FlushHouseChecker flushHouseChecker;
FlushChecker flushChecker;
StraightChecker straightChecker;
ThreeOfAKindChecker threeOfAKindChecker;
TwoPairChecker twoPairChecker;
PairChecker pairChecker;
HighCardChecker highCardChecker;

int convertRankToScore(HandRank rank);

};
