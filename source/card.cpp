#include "../include/card.hpp"

void blackJack::Card::showCard() const {
    if (getValue() == ACE) {
        std::cout << "Ace of " << getSuit() << "\n";
    }
    else if (getValue() <= 10) {
        std::cout << getValue() << " of " << getSuit() << "\n";
    }
    else if (getValue() == JACK) {
        std::cout << "Jack of " << getSuit() << "\n";
    }
    else if (getValue() == QUEEN) {
        std::cout << "Queen of " << getSuit() << "\n";
    }
    else if (getValue() == KING) {
        std::cout << "King of " << getSuit() << "\n";
    }
}