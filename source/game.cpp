#include "../include/game.hpp"

void blackJack::Game::initialiseGame() {
    std::cout << "Welcome to Blackjack!" << std::endl;
    std::string userPrompt = "What would you like to do?";
    std::string input;
    while (std::cout << userPrompt << std::endl) {
        std::cin >> input;
        executeSystemCommand(input);
    }
}

void blackJack::Game::setupGame() {
    // Resets the status for both players and dealer
    // Resets hand and redeals
    setActiveGame(true);
    dealer_.setup();
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
        // Loop through turns
        ranges::for_each(players_, [this](Player& player) {
            if (player.getStatus() == Person::PlayerStatus::Playing) {
                processTurn(player);
            }
        });
    }
    // Dealer needs to deal cards to themselves if there are players standing
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
        std::cout << "Dealer wins by deault!" << std::endl;
    }
    setActiveGame(false);
}

enum blackJack::Game::SystemCommand blackJack::Game::processSystemCommand(std::string input) {
    if (input == "add") return Add;
    else if (input == "remove") return SystemCommand::Remove;
    else if (input == "play") return SystemCommand::Play;
    else if (input == "end") return SystemCommand::End;
    return SystemCommand::InvalidS;
}

void blackJack::Game::executeSystemCommand(std::string input) {
    auto command = processSystemCommand(input);
    switch (command) {
        case SystemCommand::Add: {
            std::string name;
            std::cin >> name;
            addPlayer(name);
            break;
        }
        case SystemCommand::Remove:
            break;
        case SystemCommand::Play:
            if (players_.size() != 0) {
                runGame();
            }
            else {
                std::cout << "Not enough players." << std::endl;
            }
            break;
        case SystemCommand::End:
            break;
        case SystemCommand::InvalidS:
            std::cout << "Invalid command. Valid commands are: add [player], remove [player], end." << std::endl;
            break;
    }
}

enum blackJack::Game::PlayerCommand blackJack::Game::processPlayerCommand(std::string input) {
    if (input == "hit") return PlayerCommand::Hit;
    if (input == "hold") return PlayerCommand::Hold;
    return PlayerCommand::InvalidP;
}

void blackJack::Game::processTurn(Player& player) {
    std::string input;
    std::cout << "What would " << player.getName() << " like to do?" << std::endl;
    std::cin >> input;
    auto command = processPlayerCommand(input);
    switch (command) {
        case PlayerCommand::Hit:
            //std::cout << player.getName() << " hits." << std::endl;
            player.hit(dealer_);
            player.showHand();
            checkHand(player);
            break;
        case PlayerCommand::Hold:
            //std::cout << player.getName() << " holds." << std::endl;
            player.setStatus(Person::PlayerStatus::Standing);
            break;
        case PlayerCommand::InvalidP:
            std::cout << "Invalid command. Valid commands are: hit, hold, split." << std::endl;
            break;
    }
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
    std::cout << name << " has been added to the game." << std::endl;
}

void blackJack::Game::showPlayers() {
    std::cout << "Dealer for this game is: " << dealer_.getName() << std::endl;
    std::cout << "Players in the game are: " << std::endl;
    for (auto player : players_) {
        std::cout << player.getName() << std::endl;
    }
}