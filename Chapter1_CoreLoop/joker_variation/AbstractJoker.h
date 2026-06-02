#pragma once
#include "Joker.h"

#include <iostream>

// +3 Mult untuk setiap Joker yang dimiliki player
class AbstractJoker : public Joker {
public:
    std::string getName() const override { return "Abstract Joker"; }

    void onScoreCalculated(ScoreContext& context) override {
        int bonus = 3 * context.joker_count;
        if (bonus > 0) {
            std::cout << "  [Joker] Abstract Joker triggered! +" << bonus << " Mult\n";
            context.mult += bonus;
        }
    }
};
