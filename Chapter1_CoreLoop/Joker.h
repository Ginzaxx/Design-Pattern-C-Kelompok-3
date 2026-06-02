#pragma once

#include "ScoreContext.h"
#include <string>

class Joker {
public:
    virtual ~Joker() = default;

    virtual std::string getName() const = 0;
    virtual void onScoreCalculated(ScoreContext& context) = 0;
};
