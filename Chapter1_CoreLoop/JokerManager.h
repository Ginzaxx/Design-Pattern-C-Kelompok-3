#pragma once

#include "Joker.h"
#include <vector>
#include <memory>

class JokerManager {
public:
    void addJoker(std::unique_ptr<Joker> joker);
    void applyJokers(ScoreContext& context) const;
    int getJokerCount() const;
    std::string getOldestJokerName() const;
    bool hasJoker(const std::string& name) const;

private:
    std::vector<std::unique_ptr<Joker>> jokers;
};
