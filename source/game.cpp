#include "../include/game.hpp"

void blackJack::Game::initialiseGame() {
    //Assign a dealer to the game
    dealer_.generateDeck();
    dealer_.shuffleDeck();
    std::cout << "Please enter player name: ";
    std::string name;
    std::cin >> name;
    addPlayer(name);
    std::cout << name << " has been added to the game." << std::endl;
}

void blackJack::Game::startGame() {
    std::cout << "=============== Starting Game ================" << std::endl;
    for (auto player: players_) {
        dealer_.deal(player);
    }
    for (auto player: players_) {
        dealer_.deal(player);
    }
    dealer_.deal(dealer_);
    for (auto player: players_) {
        player.showHand();
    }
    dealer_.showHand();
    while (activePlayers() > 0) {
        for (auto player: players_) {
            if (player.getPlayingStatus() == true) {
                std::cout << player.getName() << " is still active." << std::endl;
                processTurn(player);
                player.showHand();
            }
        }
    }
    std::cout << "End game" << std::endl;
}

int blackJack::Game::activePlayers() {
    auto active = 0;
    for (auto player: players_) {
        if (player.getPlayingStatus() == true) {
            active += 1;
        }
    }
    return active;
}

int blackJack::Game::checkHand(Person person) {
    auto hand = person.getHand();
    auto sum = 0;
    for (auto card: *hand) {
        sum += card.getValue();
    }
    return sum;
}

void blackJack::Game::processTurn(Player& player) {
    std::string input;
    std::cout << "What would " << player.getName() << " like to do?" << std::endl;
    std::cin >> input;
}

void blackJack::Game::addPlayer(std::string name) {
    auto player = Player(name);
    players_.push_back(player);
}

void blackJack::Game::showPlayers() {
    std::cout << "Dealer for this game is: " << dealer_.getName() << std::endl;
    std::cout << "Players in the game are: " << std::endl;
    for (auto player : players_) {
        std::cout << player.getName() << std::endl;
    }
}

void blackJack::Game::hit(Player& player) {
    std::cout << player.getName() << " hits" << std::endl;
    dealer_.deal(player);
}

void blackJack::Game::hold(Player& player) {
    std::cout << player.getName() << " holds" << std::endl;
    player.setPlayingStatus(false);
}