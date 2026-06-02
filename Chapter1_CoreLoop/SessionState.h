#pragma once

#include <vector>
#include <memory>
#include "RewardCommand.h"
#include "BlindState.h"
#include "Card.h"

class SessionState {
public:
    SessionState();

    int current_ante = 1;
    int total_score = 0;
    int money = 0;
    int base_plays = 4;
    int remaining_plays = 4;
    int remaining_discards = 3;
    
    void calculateAndAddReward(int base_reward);
    
    std::vector<Card> deck; // The player's physical deck
    
    std::shared_ptr<BlindState> current_blind_state;
    std::vector<std::unique_ptr<RewardCommand>> pending_commands;

    void addPendingCommand(std::unique_ptr<RewardCommand> command);
    void executeCommandsAt(RewardTiming timing);
    
    void setBlindState(std::shared_ptr<BlindState> nextState);
};
