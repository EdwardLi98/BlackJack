#include "../include/game.hpp"

void blackJack::Game::initialiseGame() {
    //Assign a dealer to the game
    dealer_.generateDeck();
    std::cout << "Please enter player name: ";
    std::string name;
    std::cin >> name;
    addPlayer(name);
    std::cout << name << " has been added to the game." << std::endl;
    while (players_.size() > 0) {
        runGame();
    }
}

void blackJack::Game::runGame() {
    for (auto& player: players_) {
        player.setPlayingStatus(true);
    }
    dealer_.setPlayingStatus(true);
    dealer_.setBustedStatus(false);
    dealer_.shuffleDeck();
    std::cout << "=============== Starting Game ================" << std::endl;
    for (auto& player: players_) {
        dealer_.deal(player);
    }
    for (auto& player: players_) {
        dealer_.deal(player);
    }
    dealer_.deal(dealer_);
    for (auto& player: players_) {
        player.showHand();
        checkHand(player);
    }
    dealer_.showHand();
    while (activePlayers() > 0) {
        for (auto& player: players_) {
            if (player.getPlayingStatus() == true) {
                processTurn(player);
                player.showHand();
            }
        }
    }
    if (bustedPlayers() != players_.size()) {
        while (dealer_.sumHand() <= 16) {
            dealer_.deal(dealer_);
        }
    }
    dealer_.showHand();
    checkHand(dealer_);
    auto dealerSum = dealer_.sumHand();
    for (auto player: players_) {
        if (player.getBustedStatus() == true) {
            std::cout << player.getName() << " loses!" << std::endl;
        }
        else if (dealer_.getBustedStatus() == true) {
            std::cout << player.getName() << " wins!" << std::endl;
        } 
        else {
            auto playerSum = player.sumHand();
            if (playerSum > dealerSum) {
                std::cout << player.getName() << " wins!" << std::endl;
            }
            else if (playerSum == dealerSum) {
                std::cout << player.getName() << " ties!" << std::endl;
            }
            else {
                std::cout << player.getName() << " loses!" << std::endl;
            }
        }
    }
    std::cout << "End game" << std::endl;
    for (auto& player : players_) {
        auto hand = player.getHand();
        while (hand->size() > 0) {
            dealer_.addCardToDeck(hand->back());
            hand->pop_back();
        }
    }
    auto hand = dealer_.getHand();
    while (hand->size() > 0) {
        dealer_.addCardToDeck(hand->back());
        hand->pop_back();
    }
}

void blackJack::Game::processTurn(Player& player) {
    std::string input;
    std::cout << "What would " << player.getName() << " like to do?" << std::endl;
    std::cin >> input;
    auto command = processCommand(input);
    switch (command) {
        case Hit:
            //std::cout << player.getName() << " hits." << std::endl;
            player.hit(dealer_);
            checkHand(player);
            break;
        case Hold:
            //std::cout << player.getName() << " holds." << std::endl;
            player.stand();
            break;
        case Invalid:
            std::cout << "Invalid command. Valid commands are: hit, hold, split." << std::endl;
            break;
    }
}

enum blackJack::Game::Command blackJack::Game::processCommand(std::string input) {
    if (input == "hit") return Hit;
    if (input == "hold") return Hold;
    return Invalid;
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

int blackJack::Game::bustedPlayers() {
    auto busted = 0;
    for (auto player: players_) {
        if (player.getBustedStatus() == true) {
            busted += 1;
        }
    }
    return busted;
}

void blackJack::Game::checkHand(Person& person) {
    auto hand = person.getHand();
    auto sum = person.sumHand();
    if (sum == 21) {
        std::cout << person.getName() << " has a blackjack!" << std::endl;
        person.stand();
    }
    else if (sum > 21) {
        std::cout << person.getName() << " has busted!" << std::endl;
        person.bust();
    }
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