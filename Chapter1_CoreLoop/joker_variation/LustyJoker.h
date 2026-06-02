#pragma once
#include "Joker.h"

#include <iostream>

// +30 Chips jika ada kartu Heart (suit='H') yang dimainkan
class LustyJoker : public Joker {
public:
    std::string getName() const override { return "Lusty Joker"; }

    void onScoreCalculated(ScoreContext& context) override {
        for (const Card& c : context.playedCards) {
            if (c.suit == 'H') {
                std::cout << "  [Joker] Lusty Joker triggered! +30 Chips\n";
                context.chips += 30;
                return;
            }
        }
    }
};
