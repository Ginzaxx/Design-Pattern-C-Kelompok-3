#pragma once
#include "Joker.h"

#include <iostream>

// +4 Mult jika ada Face Card (J=11, Q=12, K=13) di kartu yang dimainkan
class ScaryFaceJoker : public Joker {
public:
    std::string getName() const override { return "Scary Face"; }

    void onScoreCalculated(ScoreContext& context) override {
        for (const Card& c : context.playedCards) {
            if (c.rank >= 11 && c.rank <= 13) {
                std::cout << "  [Joker] Scary Face triggered! +4 Mult\n";
                context.mult += 4;
                return; // cukup satu Face Card untuk trigger
            }
        }
    }
};
