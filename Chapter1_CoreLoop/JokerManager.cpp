#include "JokerManager.h"
#include <iostream>

void JokerManager::addJoker(std::unique_ptr<Joker> joker) {
    if (jokers.size() >= 5) {
        std::cout << "Slot Joker penuh (5/5)! Menghapus Joker paling lama: " << jokers.front()->getName() << "\n";
        jokers.erase(jokers.begin());
    }
    std::cout << "Added Joker: " << joker->getName() << "\n";
    jokers.push_back(std::move(joker));
}

void JokerManager::applyJokers(ScoreContext& context) const {
    for (const auto& joker : jokers) {
        joker->onScoreCalculated(context);
    }
}

int JokerManager::getJokerCount() const {
    return static_cast<int>(jokers.size());
}

std::string JokerManager::getOldestJokerName() const {
    if (jokers.empty()) return "";
    return jokers.front()->getName();
}

bool JokerManager::hasJoker(const std::string& name) const {
    for (const auto& joker : jokers) {
        if (joker->getName() == name) {
            return true;
        }
    }
    return false;
}
