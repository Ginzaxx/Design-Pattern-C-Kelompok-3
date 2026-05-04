#include <iostream>
#include "FourOfAKindChecker.h"

HandRank FourOfAKindChecker::check(const ChosenHand& hand) {
    auto counts = countRanks(hand);
    for (auto const& [rank, count] : counts) {
        if (count == 4) {
            std::cout << "Detected FOUR OF A KIND\n";
            return HandRank::FOUR_OF_A_KIND;
        }
    }

    if (nextChecker) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}
