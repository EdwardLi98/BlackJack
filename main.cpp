#include <iostream>
#include "dealer.hpp"
#include "player.hpp"
#include "card.hpp"
#include "game.hpp"
#include <random>

int main(void) {
    auto dealer = blackJack::Dealer("Dealer");
    auto game = blackJack::Game(dealer);
    game.initialiseGame();
    game.startGame();
}