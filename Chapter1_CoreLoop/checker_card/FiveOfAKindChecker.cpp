#include <iostream>
#include "FiveOfAKindChecker.h"

HandRank FiveOfAKindChecker::check(const ChosenHand& hand) {
    auto counts = countRanks(hand);
    for (auto const& [rank, count] : counts) {
        if (count == 5) {
            std::cout << "Detected FIVE OF A KIND\n";
            return HandRank::FIVE_OF_A_KIND;
        }
    }

    if (nextChecker) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}
