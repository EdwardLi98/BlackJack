#include "../include/game.hpp"

void blackJack::Game::initialiseGame() {
    //Assign a dealer to the game
    std::cout << "Please enter player name: ";
    std::string name;
    std::cin >> name;
    addPlayer(name);
    std::cout << name << " has been added to the game." << std::endl;
    while (players_.size() > 0) {
        runGame();
    }
}

void blackJack::Game::setupGame() {
    // Resets the status to playing for both players and dealer
    // Resets hand and redeals
    std::cout << "=============== Starting Game ================" << std::endl;
    ranges::for_each(players_, [this](Player& player) {
        player.setStatus(Person::PlayerStatus::Playing);
        auto hand = player.getHand();
        hand->clear();
        dealer_.deal(player);
        dealer_.deal(player);
        player.showHand();
        checkHand(player);
    });
    dealer_.deal(dealer_);
    dealer_.showHand();
}

void blackJack::Game::runGame() {
    setupGame();
    while (activePlayers() > 0) {
        ranges::for_each(players_, [this](Player& player) {
            if (player.getStatus() == Person::PlayerStatus::Playing) {
                processTurn(player);
            }
        });
    }
    if (standingPlayers() > 0) {
        while (dealer_.sumHand() <= DEAL_LIMIT) {
            dealer_.deal(dealer_);
        }
        dealer_.showHand();
        checkHand(dealer_);
        auto dealerSum = dealer_.sumHand();
        for (auto player: players_) {
            if (player.getStatus() == Person::PlayerStatus::Busted) {
                std::cout << player.getName() << " loses!" << std::endl;
            }
            else if (dealer_.getStatus() == Person::PlayerStatus::Busted) {
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
    }
    else {
        std::cout << "Dealer wins by default!" << std::endl;
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
            //std::cout << player.getName() << " hits." << std::endl;
            player.hit(dealer_);
            player.showHand();
            checkHand(player);
            break;
        case Hold:
            //std::cout << player.getName() << " holds." << std::endl;
            player.setStatus(Person::PlayerStatus::Standing);
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

int blackJack::Game::standingPlayers() {
    auto num = ranges::accumulate(players_ | 
               ranges::view::transform([](Player player) { return player.getStatus() == Person::PlayerStatus::Standing ? 1 : 0; }), 0);
    return num;
}

int blackJack::Game::activePlayers() {
    auto num = ranges::accumulate(players_ | 
               ranges::view::transform([](Player player) { return player.getStatus() == Person::PlayerStatus::Playing ? 1 : 0; }), 0);
    return num;
}

void blackJack::Game::checkHand(Person& person) {
    auto sum = person.sumHand();
    if (sum == BLACKJACK) {
        std::cout << person.getName() << " has a blackjack!" << std::endl;
        person.setStatus(Person::PlayerStatus::BlackJack);
    }
    else if (sum > BLACKJACK) {
        std::cout << person.getName() << " has busted!" << std::endl;
        person.setStatus(Person::PlayerStatus::Busted);
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