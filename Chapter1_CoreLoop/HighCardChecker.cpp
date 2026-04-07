#include <iostream>
#include "HighCardChecker.h"

HandRank HighCardChecker::check(const Hand& hand){

// Always returns HIGH_CARD if no other checker matched.
std::cout << "Detected HIGH CARD\n";
return HandRank::HIGH_CARD;

}
