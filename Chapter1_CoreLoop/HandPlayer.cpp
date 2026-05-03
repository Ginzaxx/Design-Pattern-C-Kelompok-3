#include <iostream>
#include <algorithm>
#include <iomanip>
#include "HandPlayer.h"

ChosenHand HandPlayer::playHand(const Hand& hand)
{
    std::cout << "\n--- Your Hand ---\n";
    for (int i = 0; i < hand.cards.size(); ++i) {
        std::string rankStr;
        int rank = hand.cards[i].rank;
        if (rank == 11) rankStr = "Jack";
        else if (rank == 12) rankStr = "Queen";
        else if (rank == 13) rankStr = "King";
        else if (rank == 14) rankStr = "Ace";
        else rankStr = std::to_string(rank);

        std::string suitName;
        switch (hand.cards[i].suit) {
            case 'H': suitName = "Hearts"; break;
            case 'D': suitName = "Diamonds"; break;
            case 'C': suitName = "Clubs"; break;
            case 'S': suitName = "Spades"; break;
            default: suitName = "Unknown"; break;
        }

        std::cout << i << ". " 
                  << "Rank: " << std::left << std::setw(10) << rankStr 
                  << " - Suit : " << suitName << "\n";
        }
    std::cout << "\nChoose cards to play (up to 5, ex : 0 2 4, then press Enter): ";

    std::vector<Card> selected;
    std::string input;
    std::getline(std::cin >> std::ws, input);
    
    std::stringstream ss(input);
    int index;
    while (ss >> index && selected.size() < 5) {
        if (index >= 0 && index < hand.cards.size()) {
            selected.push_back(hand.cards[index]);
        }
    }

    if (selected.empty()) {
        std::cout << "No valid input detected. Selecting first card by default.\n";
        selected.push_back(hand.cards[0]);
    }

    std::cout << "Playing " << selected.size() << " cards.\n";
    
    ChosenHand chosen;
    chosen.setCards(selected);
    return chosen;
}
