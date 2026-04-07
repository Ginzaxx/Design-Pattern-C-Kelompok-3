#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule(){

// Sambungkan chain di sini dengan setNext()
// Urutan: checker tertinggi → ... → highCardChecker (selalu terakhir)
//
// Contoh kalau sudah ada FlushChecker dan PairChecker:
//   flushChecker.setNext(&pairChecker);
//   pairChecker.setNext(&highCardChecker);
//
// Lalu ganti baris scoreHand() agar mulai dari checker pertama:
//   HandRank rank = flushChecker.check(hand);

}

int ScoringRule::scoreHand(const Hand& hand){

std::cout << "Calculating hand score...\n";

// Ganti highCardChecker dengan checker pertama di chain
// setelah kamu menambahkan checker baru
HandRank rank = highCardChecker.check(hand);

int score = convertRankToScore(rank);

std::cout << "Final score = " << score << "\n";

return score;

}

int ScoringRule::convertRankToScore(HandRank rank){

switch (rank){

// Tambah case baru di sini setiap ada HandRank baru

case HandRank::HIGH_CARD:
default:
return 5;

}

}
