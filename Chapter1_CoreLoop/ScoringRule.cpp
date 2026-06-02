#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule(){

// Sambungkan chain di sini dengan setNext()
// Urutan: checker tertinggi → ... → highCardChecker (selalu terakhir)
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

void ScoringRule::addJoker(std::unique_ptr<Joker> joker) {
    jokerManager.addJoker(std::move(joker));
}

int ScoringRule::scoreHand(const ChosenHand& hand){

    std::cout << "Calculating hand score...\n";

    HandRank rank = flushHouseChecker.check(hand);

    // Get base chips and mult from the hand type
    int baseChips = getBaseChips(rank);
    int baseMult  = getBaseMult(rank);

    // Add chip value from each card played (like Balatro)
    int cardChips = 0;
    for (const Card& c : hand.getCards()) {
        cardChips += getCardChips(c);
    }

    ScoreContext context;
    context.handType   = rank;
    context.chips      = baseChips + cardChips;
    context.mult       = baseMult;
    context.playedCards = hand.getCards();          // untuk joker conditional
    context.joker_count = jokerManager.getJokerCount(); // untuk Abstract Joker

    // Pretty-print the hand name
    std::string rankName;
    switch(rank) {
        case HandRank::FLUSH_HOUSE:     rankName = "Flush House";     break;
        case HandRank::FIVE_OF_A_KIND:  rankName = "Five of a Kind";  break;
        case HandRank::ROYAL_FLUSH:     rankName = "Royal Flush";     break;
        case HandRank::STRAIGHT_FLUSH:  rankName = "Straight Flush";  break;
        case HandRank::FOUR_OF_A_KIND:  rankName = "Four of a Kind";  break;
        case HandRank::FULL_HOUSE:      rankName = "Full House";      break;
        case HandRank::FLUSH:           rankName = "Flush";           break;
        case HandRank::STRAIGHT:        rankName = "Straight";        break;
        case HandRank::THREE_OF_A_KIND: rankName = "Three of a Kind"; break;
        case HandRank::TWO_PAIR:        rankName = "Two Pair";        break;
        case HandRank::PAIR:            rankName = "Pair";            break;
        default:                        rankName = "High Card";       break;
    }

    std::cout << "\n================ SCORE CALCULATION ================\n";
    std::cout << "Hand Type : " << rankName << " (Base: " << baseChips << " Chips x " << baseMult << " Mult)\n";
    
    for (const Card& c : hand.getCards()) {
        int cChips = getCardChips(c);
        std::cout << "  [Card] Played rank " << c.rank << " (+" << cChips << " Chips)\n";
    }

    std::cout << "---------------------------------------------------\n";
    std::cout << "Joker Effects:\n";
    
    // Apply Jokers (they will print their own effects now because we updated them)
    jokerManager.applyJokers(context);
    if (jokerManager.getJokerCount() == 0) {
        std::cout << "  (No active jokers)\n";
    }

    int finalScore = context.getFinalScore();

    std::cout << "---------------------------------------------------\n";
    std::cout << "Total Base Chips : " << context.chips << "\n";
    std::cout << "Total Multiplier : " << context.mult << "\n";
    std::cout << "Final Score      : " << context.chips << " x " << context.mult << " = " << finalScore << "\n";
    std::cout << "===================================================\n\n";

    return finalScore;

}

// ---- Balatro-style base chips per hand type ----
int ScoringRule::getBaseChips(HandRank rank){
    switch (rank){
        case HandRank::FLUSH_HOUSE:     return 140;
        case HandRank::FIVE_OF_A_KIND:  return 120;
        case HandRank::ROYAL_FLUSH:     return 100;
        case HandRank::STRAIGHT_FLUSH:  return 100;
        case HandRank::FOUR_OF_A_KIND:  return  60;
        case HandRank::FULL_HOUSE:      return  40;
        case HandRank::FLUSH:           return  35;
        case HandRank::STRAIGHT:        return  30;
        case HandRank::THREE_OF_A_KIND: return  30;
        case HandRank::TWO_PAIR:        return  20;
        case HandRank::PAIR:            return  10;
        case HandRank::HIGH_CARD:
        default:                        return   5;
    }
}

// ---- Balatro-style base mult per hand type ----
int ScoringRule::getBaseMult(HandRank rank){
    switch (rank){
        case HandRank::FLUSH_HOUSE:     return 14;
        case HandRank::FIVE_OF_A_KIND:  return 12;
        case HandRank::ROYAL_FLUSH:     return  8;
        case HandRank::STRAIGHT_FLUSH:  return  8;
        case HandRank::FOUR_OF_A_KIND:  return  7;
        case HandRank::FULL_HOUSE:      return  4;
        case HandRank::FLUSH:           return  4;
        case HandRank::STRAIGHT:        return  4;
        case HandRank::THREE_OF_A_KIND: return  3;
        case HandRank::TWO_PAIR:        return  2;
        case HandRank::PAIR:            return  2;
        case HandRank::HIGH_CARD:
        default:                        return  1;
    }
}

// ---- Chip value contributed by each individual card ----
// 2-9 → face value, 10/J/Q/K → 10, Ace → 11
int ScoringRule::getCardChips(const Card& card){
    if (card.rank >= 2 && card.rank <= 9)  return card.rank;
    if (card.rank == 10)                   return 10; // 10
    if (card.rank == 11)                   return 10; // Jack
    if (card.rank == 12)                   return 10; // Queen
    if (card.rank == 13)                   return 10; // King
    if (card.rank == 14)                   return 11; // Ace
    return 0;
}

