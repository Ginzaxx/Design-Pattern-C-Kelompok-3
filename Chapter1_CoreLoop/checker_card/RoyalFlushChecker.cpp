#include <iostream>
#include "RoyalFlushChecker.h"

HandRank RoyalFlushChecker::check(const ChosenHand& hand) {
    if (isFlush(hand) && isStraight(hand)) {
        auto counts = countRanks(hand);
        
        // A Royal Flush is specifically 10, J, Q, K, A
        // In this system: 10, 11, 12, 13, 14
        bool has10 = counts.count(10);
        bool has11 = counts.count(11);
        bool has12 = counts.count(12);
        bool has13 = counts.count(13);
        bool has14 = counts.count(14);

        if (has10 && has11 && has12 && has13 && has14) {
            std::cout << "Detected ROYAL FLUSH\n";
            return HandRank::ROYAL_FLUSH;
        }
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
