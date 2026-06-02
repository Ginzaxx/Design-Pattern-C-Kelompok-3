#include <iostream>
#include <memory>
#include <string>
#include "GameManager.h"
#include "joker_variation/FlatChipJoker.h"
#include "joker_variation/PairJoker.h"
#include "SmallBlindState.h"

GameManager::GameManager() {
    session.setBlindState(std::make_shared<SmallBlindState>());
}

void GameManager::runSession(){
    std::cout << "=== Run Started ===\n";

    // Setup initial Jokers
    // scoringRule.addJoker(std::make_unique<FlatChipJoker>()); // Start with no jokers or some basic ones? We'll leave it empty to test shop

    bool game_over = false;
    
    while (!game_over) {
        std::cout << "\n--- Current Ante: " << session.current_ante << " ---\n";
        
        session.executeCommandsAt(RewardTiming::Start);

        if (!session.current_blind_state) {
            std::cout << "Error: No active blind state.\n";
            break;
        }

        std::string blindName = session.current_blind_state->getName();
        int targetScore = session.current_blind_state->getTargetScore(session.current_ante);
        
        std::cout << "Upcoming Blind: " << blindName << " (Target: " << targetScore << ")\n";
        
        std::unique_ptr<RewardCommand> skipReward = session.current_blind_state->generateSkipReward();
        if (skipReward) {
            std::cout << "Skip Reward: " << skipReward->getName() << "\n";
            std::cout << "Do you want to PLAY or SKIP? (type PLAY or SKIP): ";
        } else {
            std::cout << "This blind CANNOT be skipped.\n";
            std::cout << "Type PLAY to continue: ";
        }
        
        std::string action;
        std::cin >> action;

        if (action == "SKIP" && skipReward) {
            std::cout << "Skipping " << blindName << "...\n";
            std::cout << "Generated Skip Reward Command.\n";
            session.addPendingCommand(std::move(skipReward));
        } else {
            std::cout << "Playing " << blindName << "...\n";
            
            session.remaining_plays = session.base_plays;
            int blind_score = 0;
            bool cleared = false;
            
            while (session.remaining_plays > 0) {
                std::cout << "\nRemaining Plays: " << session.remaining_plays << "\n";
                std::cout << "Current Blind Score: " << blind_score << " / " << targetScore << "\n";
                
                Hand hand = handGenerator.generateHand(session.deck);
                ChosenHand chosen = handPlayer.playHand(hand);
                int score = scoringRule.scoreHand(chosen);
                
                blind_score += score;
                session.remaining_plays--;
                
                if (blind_score >= targetScore) {
                    cleared = true;
                    break;
                }
            }
            
            if (cleared) {
                std::cout << "\nBLIND CLEARED! Final Score: " << blind_score << "\n";
                int base_reward = session.current_blind_state->getRewardMoney();
                session.calculateAndAddReward(base_reward);
                
                // Open Shop only if not boss blind, or open for boss blind too? Balatro opens shop after boss blind too (before ante up).
                shopSystem.openShop(session, scoringRule);
            } else {
                std::cout << "\nGAME OVER! You failed to reach the target score.\n";
                game_over = true;
                break;
            }
        }

        // Transition to next blind
        std::cout << "\nTransitioning to next state...\n";
        session.setBlindState(session.current_blind_state->getNextState(session));
        
        session.executeCommandsAt(RewardTiming::NextBlind);
        
        // NextAnte happens inside getNextState of BossBlind if triggered, we should execute NextAnte commands if ante changed
        // For simplicity we just call it.
        session.executeCommandsAt(RewardTiming::NextAnte);
    }

    std::cout << "\n=== Run Ended ===\n";
}
