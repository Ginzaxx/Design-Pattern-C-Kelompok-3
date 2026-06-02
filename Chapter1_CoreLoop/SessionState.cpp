#include "SessionState.h"
#include <iostream>

SessionState::SessionState() {
    char suits[] = {'H', 'D', 'C', 'S'};
    for (int r = 2; r <= 14; ++r) {
        for (char s : suits) {
            deck.push_back({r, s});
        }
    }
}

void SessionState::addPendingCommand(std::unique_ptr<RewardCommand> command) {
    pending_commands.push_back(std::move(command));
}

void SessionState::executeCommandsAt(RewardTiming timing) {
    auto it = pending_commands.begin();
    while (it != pending_commands.end()) {
        if ((*it)->getTiming() == timing) {
            (*it)->execute(*this);
            it = pending_commands.erase(it);
        } else {
            ++it;
        }
    }
}

void SessionState::calculateAndAddReward(int base_reward) {
    int unused_hands_bonus = remaining_plays;
    int interest = std::min(5, money / 5);
    
    int total_reward = base_reward + unused_hands_bonus + interest;
    money += total_reward;
    
    std::cout << "--- Reward Calculation ---\n";
    std::cout << "Base Reward: " << base_reward << "\n";
    std::cout << "Unused Hands Bonus: " << unused_hands_bonus << "\n";
    std::cout << "Interest: " << interest << " (from " << (money - total_reward) << " money)\n";
    std::cout << "Total Money Gained: " << total_reward << "\n";
    std::cout << "Current Money: " << money << "\n";
}

void SessionState::setBlindState(std::shared_ptr<BlindState> nextState) {
    current_blind_state = nextState;
}
