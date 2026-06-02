#pragma once

#include "PokerHandChecker.h"
#include "Card.h"
#include <vector>

struct ScoreContext {
    HandRank handType = HandRank::HIGH_CARD;

    int chips = 0;
    int mult  = 1;

    // Kartu yang benar-benar dimainkan pada hand ini
    std::vector<Card> playedCards;

    // Jumlah joker aktif (diisi oleh ScoringRule sebelum applyJokers)
    int joker_count = 0;

    int getFinalScore() const {
        return chips * mult;
    }
};
