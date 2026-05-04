#include <iostream>
#include "FlushChecker.h"

HandRank FlushChecker::check(const ChosenHand& hand) {
    if (isFlush(hand)) {
        std::cout << "Detected FLUSH\n";
        return HandRank::FLUSH;
    }

    if (nextChecker) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}
