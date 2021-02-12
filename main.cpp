#include <iostream>
#include "dealer.hpp"
#include "player.hpp"
#include "card.hpp"
#include <random>

int main(void) {
    auto dealer = blackJack::Dealer("Mark");
    dealer.generateDeck();
    dealer.shuffleDeck();
    dealer.showDeck();
    auto player = blackJack::Player("Edward");
    dealer.deal(player);
    player.showHand();
    dealer.showDeck();
}