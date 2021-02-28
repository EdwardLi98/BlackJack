#include "../include/person.hpp"

void blackJack::Person::showHand() const {
    std::cout << name_ << " has the following cards: " << "\n";
    for (auto card : *hand_) {
        card.showCard();
    }
}
