#pragma once

#include "Joker.h"
#include <iostream>

class FlatChipJoker : public Joker {
public:
    std::string getName() const override { return "Flat Chip Joker"; }
    void onScoreCalculated(ScoreContext& context) override {
        std::cout << "  [Joker] Flat Chip Joker triggered! +20 Chips\n";
        context.chips += 20;
    }
};
