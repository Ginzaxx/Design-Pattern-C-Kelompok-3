#pragma once
#include "Joker.h"

#include <iostream>

// +15 Chips untuk setiap Ace (rank=14) yang dimainkan
class AceBoosterJoker : public Joker {
public:
    std::string getName() const override { return "Ace Booster"; }

    void onScoreCalculated(ScoreContext& context) override {
        int count = 0;
        for (const Card& c : context.playedCards) {
            if (c.rank == 14) count++;
        }
        if (count > 0) {
            int bonus = 15 * count;
            std::cout << "  [Joker] Ace Booster triggered! +" << bonus << " Chips\n";
            context.chips += bonus;
        }
    }
};
