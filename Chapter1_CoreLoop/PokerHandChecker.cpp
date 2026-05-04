#include "PokerHandChecker.h"

void PokerHandChecker::setNext(PokerHandChecker* next) {
    nextChecker = next;
}

std::map<int, int> PokerHandChecker::countRanks(const ChosenHand& hand) {
    std::map<int, int> counts;
    for (const auto& card : hand.getCards()) {
        counts[card.rank]++;
    }
    return counts;
}

std::map<char, int> PokerHandChecker::countSuits(const ChosenHand& hand) {
    std::map<char, int> counts;
    for (const auto& card : hand.getCards()) {
        counts[card.suit]++;
    }
    return counts;
}

bool PokerHandChecker::isStraight(const ChosenHand& hand) {
    if (hand.getCards().size() < 5) return false;
    
    std::vector<int> ranks;
    for (const auto& card : hand.getCards()) {
        ranks.push_back(card.rank);
    }
    std::sort(ranks.begin(), ranks.end());
    ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end());
    
    if (ranks.size() < 5) return false;

    // Check for normal straight
    for (size_t i = 0; i <= ranks.size() - 5; ++i) {
        if (ranks[i+4] - ranks[i] == 4) return true;
    }
    
    // Check for A-2-3-4-5 (Ace is 14)
    bool hasAce = std::find(ranks.begin(), ranks.end(), 14) != ranks.end();
    if (hasAce) {
        bool has2345 = (std::find(ranks.begin(), ranks.end(), 2) != ranks.end() &&
                        std::find(ranks.begin(), ranks.end(), 3) != ranks.end() &&
                        std::find(ranks.begin(), ranks.end(), 4) != ranks.end() &&
                        std::find(ranks.begin(), ranks.end(), 5) != ranks.end());
        if (has2345) return true;
    }
    
    return false;
}

bool PokerHandChecker::isFlush(const ChosenHand& hand) {
    if (hand.getCards().empty()) return false;
    auto counts = countSuits(hand);
    for (auto const& [suit, count] : counts) {
        if (count >= 5) return true;
    }
    return false;
}
