#pragma once

#include "BlindState.h"

class BigBlindState : public BlindState {
public:
    std::string getName() const override { return "Big Blind"; }
    int getTargetScore(int ante) const override { return 450 * ante; }
    int getRewardMoney() const override { return 4; }

    std::shared_ptr<BlindState> getNextState(SessionState& session) override;
    std::unique_ptr<RewardCommand> generateSkipReward() override;
};
