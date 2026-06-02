#pragma once

#include "ChosenHand.h"
#include "PokerHandChecker.h"
#include "FlushHouseChecker.h"
#include "FiveOfAKindChecker.h"
#include "RoyalFlushChecker.h"
#include "StraightFlushChecker.h"
#include "FourOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfAKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "HighCardChecker.h"

#include "ScoreContext.h"
#include "JokerManager.h"

// ============================================================
// Cara tambah checker baru:
// 1. #include "MyChecker.h" di sini
// 2. Tambah member: MyChecker myChecker;
// ============================================================

class ScoringRule{

public:

ScoringRule();

int scoreHand(const ChosenHand& hand);
void addJoker(std::unique_ptr<Joker> joker);

int getJokerCount() const { return jokerManager.getJokerCount(); }
std::string getOldestJokerName() const { return jokerManager.getOldestJokerName(); }
bool hasJoker(const std::string& name) const { return jokerManager.hasJoker(name); }

private:
JokerManager jokerManager;

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
FlushHouseChecker flushHouseChecker;
FiveOfAKindChecker fiveOfAKindChecker;
RoyalFlushChecker royalFlushChecker;
StraightFlushChecker straightFlushChecker;
FourOfAKindChecker fourOfAKindChecker;
FullHouseChecker fullHouseChecker;
FlushChecker flushChecker;
StraightChecker straightChecker;
ThreeOfAKindChecker threeOfAKindChecker;
TwoPairChecker twoPairChecker;
PairChecker pairChecker;
HighCardChecker highCardChecker;

int getBaseChips(HandRank rank);
    int getBaseMult(HandRank rank);
    int getCardChips(const Card& card);

};
