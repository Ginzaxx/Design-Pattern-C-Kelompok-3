#include <iostream>
#include "RoyalFlushChecker.h"

HandRank RoyalFlushChecker::check(const ChosenHand& hand) {
    if (isFlush(hand) && isStraight(hand)) {
        auto counts = countRanks(hand);
        // Check if highest rank is 14 (Ace)
        if (counts.rbegin()->first == 14) {
            std::cout << "Detected ROYAL FLUSH\n";
            return HandRank::ROYAL_FLUSH;
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
