#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule(){

// Sambungkan chain di sini dengan setNext()
// Urutan: checker tertinggi → ... → highCardChecker (selalu terakhir)
//
// Contoh kalau sudah ada RoyalFlushChecker, FiveOfAKindChecker, dan FlushHouseChecker:
//   royalFlushChecker.setNext(&straightFlushChecker);
//   straightFlushChecker.setNext(&fourOfAKindChecker);
//   fourOfAKindChecker.setNext(&fullHouseChecker);
//   fullHouseChecker.setNext(&flushHouseChecker);
//   flushHouseChecker.setNext(&flushChecker);
//   flushChecker.setNext(&straightChecker);
//   straightChecker.setNext(&threeOfAKindChecker);
//   threeOfAKindChecker.setNext(&twoPairChecker);
//   twoPairChecker.setNext(&pairChecker);
//   pairChecker.setNext(&highCardChecker);
//
// Lalu ganti baris scoreHand() agar mulai dari checker pertama:
//   HandRank rank = royalFlushChecker.check(hand);
flushHouseChecker.setNext(&fiveOfAKindChecker);
fiveOfAKindChecker.setNext(&royalFlushChecker);
royalFlushChecker.setNext(&straightFlushChecker);
straightFlushChecker.setNext(&fourOfAKindChecker);
fourOfAKindChecker.setNext(&fullHouseChecker);
fullHouseChecker.setNext(&flushChecker);
flushChecker.setNext(&straightChecker);
straightChecker.setNext(&threeOfAKindChecker);
threeOfAKindChecker.setNext(&twoPairChecker);
twoPairChecker.setNext(&pairChecker);
pairChecker.setNext(&highCardChecker);

}

int ScoringRule::scoreHand(const Hand& hand){

std::cout << "Calculating hand score...\n";

// Ganti highCardChecker dengan checker pertama di chain
// setelah kamu menambahkan checker baru
HandRank rank = flushHouseChecker.check(hand);

int score = convertRankToScore(rank);

std::cout << "Final score = " << score << "\n";

return score;

}

int ScoringRule::convertRankToScore(HandRank rank){

switch (rank){

// Tambah case baru di sini setiap ada HandRank baru

case HandRank::FLUSH_HOUSE:
return 120;
case HandRank::FIVE_OF_A_KIND:
return 110;
case HandRank::ROYAL_FLUSH:
return 100;
case HandRank::STRAIGHT_FLUSH:
return 90;
case HandRank::FOUR_OF_A_KIND:
return 80;
case HandRank::FULL_HOUSE:
return 70;
case HandRank::FLUSH:
return 60;
case HandRank::STRAIGHT:
return 50;
case HandRank::THREE_OF_A_KIND:
return 40;
case HandRank::TWO_PAIR:
return 30;
case HandRank::PAIR:
return 20;
case HandRank::HIGH_CARD:
default:
return 5;

}

}
