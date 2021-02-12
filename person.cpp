#include "person.hpp"

void blackJack::Person::showHand() {
    std::cout << name_ << " has the following cards: " << std::endl;
    for (auto card : *hand_) {
        std::cout << "Card has value: " << card.getValue() << " and suit: " << card.getSuit() << std::endl;
    }
}