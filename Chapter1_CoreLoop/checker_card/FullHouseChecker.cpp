#include <iostream>
#include "FullHouseChecker.h"

HandRank FullHouseChecker::check(const ChosenHand& hand) {
    bool hasThree = false;
    bool hasTwo = false;
    auto counts = countRanks(hand);

    for (auto const& [rank, count] : counts) {
        if (count == 3) hasThree = true;
        if (count == 2) hasTwo = true;
    }

    if (hasThree && hasTwo) {
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }

    if (nextChecker) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}
