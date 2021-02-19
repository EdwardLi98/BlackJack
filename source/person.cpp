#include "../include/person.hpp"

int blackJack::Person::sumHand() {
    auto sum = 0;
    auto aceCounter = 0;
    for (auto card: *hand_) {
        auto value = card.getValue();
        if (value <= 10) {
            if (value == 1) {
                sum += 11;
                aceCounter += 1;
            }
            else {
                sum += value;
            }
        }
        else {
            sum += 10;
        }
    }
    for (auto counter = 0; counter < aceCounter; ++counter) {
        if (sum > 21) {
            sum -= 9;
        }
    }
    return sum;
}

void blackJack::Person::showHand() {
    std::cout << name_ << " has the following cards: " << std::endl;
    for (auto card : *hand_) {
        std::cout << card.getValue() << " of " << card.getSuit() << std::endl;
    }
}
