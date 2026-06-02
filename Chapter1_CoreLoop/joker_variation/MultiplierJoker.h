#pragma once

#include "Joker.h"

#include <iostream>

class MultiplierJoker : public Joker {
public:
    std::string getName() const override { return "Multiplier Joker"; }
    void onScoreCalculated(ScoreContext& context) override {
        std::cout << "  [Joker] Multiplier Joker triggered! +2 Mult\n";
        context.mult += 2;
    }
};
