#include <iostream>
#include "StraightChecker.h"

HandRank StraightChecker::check(const ChosenHand& hand) {
    if (isStraight(hand)) {
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }

    if (nextChecker) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}
