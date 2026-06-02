#pragma once

#include <memory>

class SessionState; // Forward declaration

enum class RewardTiming {
    Start,
    NextBlind,
    NextAnte
};

class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual void execute(SessionState& session) = 0;
    virtual RewardTiming getTiming() const = 0;
    virtual std::string getName() const = 0;
};
