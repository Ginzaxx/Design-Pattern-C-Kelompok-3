#include <iostream>
#include "ThreeOfAKindChecker.h"

HandRank ThreeOfAKindChecker::check(const ChosenHand& hand) {
    auto counts = countRanks(hand);
    bool found3 = false;
    for (auto const& [rank, count] : counts) {
        if (count >= 3) {
            found3 = true;
            break;
        }
    }

    if (found3) {
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
