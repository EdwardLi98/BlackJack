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
    while (players_.size() > 0) {
        startGame();
    }
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
    std::cout << "End game" << std::endl;
}

void blackJack::Game::processTurn(Player& player) {
    std::string input;
    std::cout << "What would " << player.getName() << " like to do?" << std::endl;
    std::cin >> input;
    auto command = processCommand(input);
    switch (command) {
        case Hit:
            std::cout << player.getName() << " hits." << std::endl;
            player.hit(dealer_);
            checkHand(player);
            break;
        case Hold:
            std::cout << player.getName() << " holds." << std::endl;
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

void blackJack::Game::checkHand(Player& player) {
    auto hand = player.getHand();
    auto sum = 0;
    auto aceCounter = 0;
    for (auto card: *hand) {
        auto value = card.getValue();
        if (value <= 10) {
            sum += value;
            if (value == 1) {
                aceCounter += 1;
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
    if (sum == 21) {
        std::cout << player.getName() << " has a blackjack!" << std::endl;
        player.stand();
    }
    else if (sum > 21) {
        std::cout << player.getName() << " has busted!" << std::endl;
        player.stand();
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