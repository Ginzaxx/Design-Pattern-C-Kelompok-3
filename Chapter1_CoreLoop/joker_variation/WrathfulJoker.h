#pragma once
#include "Joker.h"

#include <iostream>

// +30 Chips jika ada kartu Spade (suit='S') yang dimainkan
class WrathfulJoker : public Joker {
public:
    std::string getName() const override { return "Wrathful Joker"; }

    void onScoreCalculated(ScoreContext& context) override {
        for (const Card& c : context.playedCards) {
            if (c.suit == 'S') {
                std::cout << "  [Joker] Wrathful Joker triggered! +30 Chips\n";
                context.chips += 30;
                return;
            }
        }
    }
};
