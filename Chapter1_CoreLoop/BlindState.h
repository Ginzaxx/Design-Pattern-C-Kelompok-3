#pragma once

#include <string>
#include <memory>
#include "RewardCommand.h"

class SessionState; // Forward declaration

class BlindState {
public:
    virtual ~BlindState() = default;

    virtual std::string getName() const = 0;
    virtual int getTargetScore(int ante) const = 0;
    virtual int getRewardMoney() const = 0;

    virtual std::shared_ptr<BlindState> getNextState(SessionState& session) = 0;
    virtual std::unique_ptr<RewardCommand> generateSkipReward() = 0;
};
