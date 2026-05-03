#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    std::cout << "Generating cards for player...\n";

    std::vector<Card> deck;
    char suits[] = {'H', 'D', 'C', 'S'};
    for (int r = 2; r <= 14; ++r) {
        for (char s : suits) {
            deck.push_back({r, s});
        }
    }

    static std::mt19937 g(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(deck.begin(), deck.end(), g);

    Hand hand;
    for (int i = 0; i < 8; ++i) {
        hand.cards.push_back(deck[i]);
    }

    std::cout << "Hand generated with 8 cards.\n";
    return hand;
}
