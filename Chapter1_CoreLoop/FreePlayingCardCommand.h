#pragma once

#include "RewardCommand.h"
#include "SessionState.h"
#include <iostream>
#include <random>
#include <ctime>

class FreePlayingCardCommand : public RewardCommand {
public:
    void execute(SessionState& session) override {
        std::cout << "[Command] FreePlayingCardCommand executed! Added free playing card to deck.\n";
        
        static std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<> rankDist(2, 14);
        char suits[] = {'H', 'D', 'C', 'S'};
        std::uniform_int_distribution<> suitDist(0, 3);
        
        Card c = {rankDist(g), suits[suitDist(g)]};
        session.deck.push_back(c);
        std::cout << "Added Card - Rank: " << c.rank << ", Suit: " << c.suit << "\n";
    }

    RewardTiming getTiming() const override {
        return RewardTiming::Start; // Example timing
    }

    std::string getName() const override {
        return "Free Playing Card";
    }
};
