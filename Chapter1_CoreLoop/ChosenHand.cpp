#include "ChosenHand.h"

void ChosenHand::setCards(const std::vector<Card>& cards) {
    this->chosenCards = cards;
}

const std::vector<Card>& ChosenHand::getCards() const {
    return chosenCards;
}

void ChosenHand::clear() {
    chosenCards.clear();
}
