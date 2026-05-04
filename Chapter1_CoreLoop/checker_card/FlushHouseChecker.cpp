#include <iostream>
#include "FlushHouseChecker.h"

HandRank FlushHouseChecker::check(const ChosenHand& hand) {
    bool hasThree = false;
    bool hasTwo = false;
    auto counts = countRanks(hand);
    
    for (auto const& [rank, count] : counts) {
        if (count == 3) hasThree = true;
        if (count == 2) hasTwo = true;
    }

    if (isFlush(hand) && hasThree && hasTwo) {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }

    if (nextChecker) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}
