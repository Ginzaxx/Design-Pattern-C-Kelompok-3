#pragma once

#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "SessionState.h"
#include "ShopSystem.h"
#include <memory>

class GameManager {
public:
    GameManager();
    void runSession();

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    ShopSystem shopSystem;
    
    SessionState session;
};
