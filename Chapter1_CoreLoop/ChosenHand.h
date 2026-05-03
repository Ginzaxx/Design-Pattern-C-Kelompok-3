#pragma once
#include <vector>
#include "Card.h"

class ChosenHand {
public:
    void setCards(const std::vector<Card>& cards);
    const std::vector<Card>& getCards() const;
    void clear();
private:
    std::vector<Card> chosenCards;
};
