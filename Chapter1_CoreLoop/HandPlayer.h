#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "Hand.h"
#include "ChosenHand.h"

class HandPlayer {
public:
    ChosenHand playHand(const Hand& hand);
};
