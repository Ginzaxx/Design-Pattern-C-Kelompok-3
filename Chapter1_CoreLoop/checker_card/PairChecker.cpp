#include <iostream>
#include "PairChecker.h"

HandRank PairChecker::check(const ChosenHand& hand) {
    auto counts = countRanks(hand);
    bool foundPair = false;
    for (auto const& [rank, count] : counts) {
        if (count >= 2) {
            foundPair = true;
            break;
        }
    }

    if (foundPair) {
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
