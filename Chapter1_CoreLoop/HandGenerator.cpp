#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include "HandGenerator.h"

Hand HandGenerator::generateHand(std::vector<Card>& deck) {
    std::cout << "Generating cards for player from physical deck...\n";

    if (deck.empty()) {
        std::cout << "Deck is empty! Cannot generate hand.\n";
        return Hand();
    }

    static std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(deck.begin(), deck.end(), g);

    Hand hand;
    int cardsToDraw = std::min(8, static_cast<int>(deck.size()));
    for (int i = 0; i < cardsToDraw; ++i) {
        hand.cards.push_back(deck[i]);
    }

    std::cout << "Hand generated with " << cardsToDraw << " cards.\n";
    return hand;
}
