#pragma once

#include "SessionState.h"
#include "ScoringRule.h"
#include <memory>

class ShopSystem {
public:
    void openShop(SessionState& session, ScoringRule& scoringRule);
};
