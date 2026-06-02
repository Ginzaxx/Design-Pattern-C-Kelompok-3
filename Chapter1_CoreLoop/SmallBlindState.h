#pragma once

#include "BlindState.h"

class SmallBlindState : public BlindState {
public:
    std::string getName() const override { return "Small Blind"; }
    int getTargetScore(int ante) const override { return 300 * ante; }
    int getRewardMoney() const override { return 3; }

    std::shared_ptr<BlindState> getNextState(SessionState& session) override;
    std::unique_ptr<RewardCommand> generateSkipReward() override;
};
