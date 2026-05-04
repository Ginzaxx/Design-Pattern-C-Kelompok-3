#include <iostream>
#include "TwoPairChecker.h"

HandRank TwoPairChecker::check(const ChosenHand& hand) {
    auto counts = countRanks(hand);
    int pairs = 0;
    for (auto const& [rank, count] : counts) {
        if (count >= 2) {
            pairs++;
        }
    }

    if (pairs >= 2) {
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
