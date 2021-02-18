#include "../include/player.hpp"

void blackJack::Player::hit(Dealer &dealer) {
    dealer.deal(*this);
}

void blackJack::Player::stand() {
    playingStatus_ = false;
}