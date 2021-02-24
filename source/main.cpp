#include <iostream>
#include "../include/dealer.hpp"
#include "../include/player.hpp"
#include "../include/card.hpp"
#include "../include/game.hpp"
#include <random>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>

int main(void) {
    auto game = blackJack::Game();
    game.initialiseGame();
}