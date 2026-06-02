#include "SmallBlindState.h"
#include "BigBlindState.h"
#include "BossBlindState.h"
#include "SessionState.h"
#include "BonusHandCommand.h"
#include "FreePlayingCardCommand.h"
#include <iostream>
#include <random>
#include <ctime>

static std::unique_ptr<RewardCommand> getRandomReward() {
    static std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> dist(0, 1);
    if (dist(g) == 0) {
        return std::make_unique<BonusHandCommand>();
    } else {
        return std::make_unique<FreePlayingCardCommand>();
    }
}

// SmallBlindState Implementation
std::shared_ptr<BlindState> SmallBlindState::getNextState(SessionState& session) {
    return std::make_shared<BigBlindState>();
}

std::unique_ptr<RewardCommand> SmallBlindState::generateSkipReward() {
    return getRandomReward();
}

// BigBlindState Implementation
std::shared_ptr<BlindState> BigBlindState::getNextState(SessionState& session) {
    return std::make_shared<BossBlindState>();
}

std::unique_ptr<RewardCommand> BigBlindState::generateSkipReward() {
    return getRandomReward();
}

// BossBlindState Implementation
std::shared_ptr<BlindState> BossBlindState::getNextState(SessionState& session) {
    std::cout << "[Boss Defeated] Ante Increased!\n";
    session.current_ante += 1;
    return std::make_shared<SmallBlindState>();
}

std::unique_ptr<RewardCommand> BossBlindState::generateSkipReward() {
    // Boss blind cannot be skipped, but if called, return nullptr
    return nullptr;
}
