#include "../include/game.hpp"

void blackJack::Game::initialiseGame() {
    std::cout << "Welcome to Blackjack!" << "\n";
    std::string userPrompt = "What would you like to do?";
    std::string input;
    while (std::cout << userPrompt << "\n") {
        std::cin >> input;
        executeSystemCommand(input);
    }
}

void blackJack::Game::setupGame() {
    // Resets the status for both players and dealer
    // Resets hand and redeals
    dealer_.setup();
    std::cout << "=============== Starting Game ================" << "\n";
    ranges::for_each(players_, [this](Player &player) {
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
        ranges::for_each(players_, [this](Player &player) {
            while (player.getStatus() == Person::PlayerStatus::Playing) {
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
        for (auto player : players_) {
            if (player.getStatus() == Person::PlayerStatus::Busted) {
                std::cout << player.getName() << " loses!" << "\n";
            }
            else if (dealer_.getStatus() == Person::PlayerStatus::Busted) {
                std::cout << player.getName() << " wins!" << "\n";
            }
            else {
                auto playerSum = player.sumHand();
                if (playerSum > dealerSum) {
                    std::cout << player.getName() << " wins!" << "\n";
                }
                else if (playerSum == dealerSum) {
                    std::cout << player.getName() << " ties!" << "\n";
                }
                else {
                    std::cout << player.getName() << " loses!" << "\n";
                }
            }
        }
    }
    else {
        std::cout << "Dealer wins by deault!" << "\n";
    }
}

enum blackJack::Game::SystemCommand blackJack::Game::processSystemCommand(std::string input) {
    if (input == "add")
        return Add;
    else if (input == "remove")
        return SystemCommand::Remove;
    else if (input == "play")
        return SystemCommand::Play;
    else if (input == "end")
        return SystemCommand::End;
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
    case SystemCommand::Remove: {
        std::string name;
        std::cin >> name;
        removePlayer(name);
        break;
    }
    case SystemCommand::Play:
        if (players_.size() != 0) {
            runGame();
        }
        else {
            std::cout << "Not enough players." << "\n";
        }
        break;
    case SystemCommand::End:
        exit(0);
        break;
    case SystemCommand::InvalidS:
        std::cout << "Invalid command. Valid commands are: add [player], remove [player], play, end." << "\n";
        break;
    }
}

enum blackJack::Game::PlayerCommand blackJack::Game::processPlayerCommand(std::string input) {
    if (input == "hit")
        return PlayerCommand::Hit;
    if (input == "hold")
        return PlayerCommand::Hold;
    return PlayerCommand::InvalidP;
}

void blackJack::Game::processTurn(Player &player) {
    std::string input;
    std::cout << "What would " << player.getName() << " like to do?" << "\n";
    std::cin >> input;
    auto command = processPlayerCommand(input);
    switch (command) {
    case PlayerCommand::Hit:
        //std::cout << player.getName() << " hits." << "\n";
        player.hit(dealer_);
        player.showHand();
        checkHand(player);
        break;
    case PlayerCommand::Hold:
        //std::cout << player.getName() << " holds." << "\n";
        player.setStatus(Person::PlayerStatus::Standing);
        break;
    case PlayerCommand::InvalidP:
        std::cout << "Invalid command. Valid commands are: hit, hold, split." << "\n";
        break;
    }
}

int blackJack::Game::standingPlayers() {
    auto num = ranges::accumulate(players_ 
             | ranges::view::transform([](Player player) { return player.getStatus() == Person::PlayerStatus::Standing ? 1 : 0; }),
                                  0);
    return num;
}

int blackJack::Game::activePlayers() {
    auto num = ranges::accumulate(players_ 
             | ranges::view::transform([](Player player) { return player.getStatus() == Person::PlayerStatus::Playing ? 1 : 0; }),
                                  0);
    return num;
}

void blackJack::Game::checkHand(Person &person) {
    auto sum = person.sumHand();
    if (sum == BLACKJACK) {
        std::cout << person.getName() << " has a blackjack!" << "\n";
        person.setStatus(Person::PlayerStatus::BlackJack);
    }
    else if (sum > BLACKJACK) {
        std::cout << person.getName() << " has busted!" << "\n";
        person.setStatus(Person::PlayerStatus::Busted);
    }
}

void blackJack::Game::addPlayer(std::string name) {
    auto player = Player(name);
    players_.push_back(player);
    std::cout << name << " has been added to the game." << "\n";
}

void blackJack::Game::removePlayer(std::string name) {
    auto rm = [name](Player player) { 
        auto playerName = player.getName();
        if (std::strcmp(playerName.c_str(), name.c_str()) == 0) {
            std::cout << name << " has been removed from the game." << "\n";
            return true;
        }
        else {
            return false;
        }
    };
    ranges::actions::remove_if(players_, rm);
}

void blackJack::Game::addPlayer(std::string name) {
    auto player = Player(name);
    players_.push_back(player);
    std::cout << name << " has been added to the game." << std::endl;
}

void blackJack::Game::showPlayers() {
    std::cout << "Dealer for this game is: " << dealer_.getName() << "\n";
    std::cout << "Players in the game are: " << "\n";
    for (auto player : players_) {
        std::cout << player.getName() << "\n";
    }
}