#include "../include/player.hpp"

void blackJack::Player::showSplitHand() const {
    std::cout << getName() << " has the following cards: " << "\n";
    for (auto card : *splitHand_) {
        card.showCard();
    }
}