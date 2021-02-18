#include "../include/person.hpp"

void blackJack::Person::showHand() {
    std::cout << name_ << " has the following cards: " << std::endl;
    for (auto card : *hand_) {
        std::cout << card.getValue() << " of " << card.getSuit() << std::endl;
    }
}
