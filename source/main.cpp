#include <iostream>
#include "../include/dealer.hpp"
#include "../include/player.hpp"
#include "../include/card.hpp"
#include "../include/game.hpp"
#include <random>

int main(void) {
    auto dealer = blackJack::Dealer("Dealer");
    auto game = blackJack::Game(dealer);
    game.initialiseGame();
}