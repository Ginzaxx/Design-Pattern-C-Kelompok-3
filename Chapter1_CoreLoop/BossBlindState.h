#pragma once

#include "BlindState.h"

class BossBlindState : public BlindState {
public:
    std::string getName() const override { return "Boss Blind"; }
    int getTargetScore(int ante) const override { return 600 * ante; }
    int getRewardMoney() const override { return 5; }

    std::shared_ptr<BlindState> getNextState(SessionState& session) override;
    std::unique_ptr<RewardCommand> generateSkipReward() override;
};
