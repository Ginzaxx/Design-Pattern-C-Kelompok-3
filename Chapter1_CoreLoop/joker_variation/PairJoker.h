#pragma once

#include "Joker.h"
#include <iostream>

class PairJoker : public Joker {
public:
    std::string getName() const override { return "Pair Joker"; }
    void onScoreCalculated(ScoreContext& context) override {
        if (context.handType == HandRank::PAIR) {
            std::cout << "  [Joker] Pair Joker triggered! +4 Mult\n";
            context.mult += 4;
        }
    }
};
