#pragma once

#include "RewardCommand.h"
#include "SessionState.h"
#include <iostream>

class BonusHandCommand : public RewardCommand {
public:
    void execute(SessionState& session) override {
        std::cout << "[Command] BonusHandCommand executed! +1 base hand play per blind.\n";
        session.base_plays += 1;
        // If we are executing this during a blind, give them an extra play immediately too
        session.remaining_plays += 1;
    }

    RewardTiming getTiming() const override {
        return RewardTiming::NextBlind;
    }

    std::string getName() const override {
        return "Bonus Hand (+1 Hand next blind)";
    }
};
