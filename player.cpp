#include "player.hpp"

void blackJack::Player::hit(Dealer &dealer) {
    dealer.deal(*this);
}