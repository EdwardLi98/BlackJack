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
        player.setStatus(Person::HandStatus::Playing);
        player.setSplitStatus(Person::HandStatus::Inactive);
        auto hand = player.getHand();
        hand->clear();
        auto splitHand = player.getSplitHand();
        splitHand->clear();
        dealer_.deal(hand);
        dealer_.deal(hand);
        player.showHand();
        checkHand(hand, player);
    });
}

void blackJack::Game::runGame() {
    setupGame();
    // Loop through turns
    ranges::for_each(players_, [this](Player &player) {
        while (player.getStatus() == Person::HandStatus::Playing) {
            processTurn(player);
        }
        while (player.getSplitStatus() == Person::HandStatus::Playing){
            processSplitTurn(player);
        }
    });
    // Dealer needs to deal cards to themselves if there are players standing
    if (standingPlayers() > 0) {
        while (sumHand(dealer_.getHand()) <= DEAL_LIMIT) {
            dealer_.deal(dealer_.getHand());
        }
    }
    dealer_.showHand();
    checkHand(dealer_.getHand(), dealer_);
    auto dealerSum = sumHand(dealer_.getHand());
    for (auto player : players_) {
        checkWin(player, dealer_);
        if (player.getSplitStatus() != Person::HandStatus::Inactive) {
            checkSplitWin(player, dealer_);
        }
    }
}

enum blackJack::Game::SystemCommand blackJack::Game::processSystemCommand(const std::string input) const {
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

void blackJack::Game::executeSystemCommand(const std::string input) {
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

enum blackJack::Game::PlayerCommand blackJack::Game::processPlayerCommand(const std::string input) const {
    if (input == "hit")
        return PlayerCommand::Hit;
    else if (input == "hold")
        return PlayerCommand::Hold;
    else if (input == "split")
        return PlayerCommand::Split;

    return PlayerCommand::InvalidP;
}

void blackJack::Game::processTurn(Player &player) {
    player.showHand();
    std::string input;
    std::cout << "What would " << player.getName() << " like to do?" << "\n";
    std::cin >> input;
    auto command = processPlayerCommand(input);
    auto hand = player.getHand();
    switch (command) {
    case PlayerCommand::Hit:
        //std::cout << player.getName() << " hits." << "\n";
        dealer_.deal(hand);
        player.showHand();
        checkHand(hand, player);
        break;
    case PlayerCommand::Hold:
        //std::cout << player.getName() << " holds." << "\n";
        player.setStatus(Person::HandStatus::Standing);
        break;
    case PlayerCommand::Split:
        if (checkSplit(player)) {
            player.setSplitStatus(Person::HandStatus::Playing);
            auto splitHand = player.getSplitHand();
            splitHand->push_back(hand->back());
            hand->pop_back();
        }
        break;
    case PlayerCommand::InvalidP:
        std::cout << "Invalid command. Valid commands are: hit, hold, split." << "\n";
        break;
    }
}

void blackJack::Game::processSplitTurn(Player &player) {
    player.showSplitHand();
    std::string input;
    std::cout << "What would " << player.getName() << " like to do for the second hand?" << "\n";
    std::cin >> input;
    auto command = processPlayerCommand(input);
    auto hand = player.getSplitHand();
    switch (command) {
    case PlayerCommand::Hit:
        //std::cout << player.getName() << " hits." << "\n";
        dealer_.deal(hand);
        player.showSplitHand();
        checkHand(hand, player);
        break;
    case PlayerCommand::Hold:
        //std::cout << player.getName() << " holds." << "\n";
        player.setSplitStatus(Person::HandStatus::Standing);
        break;
    case PlayerCommand::Split:
        std::cout << "Can't split on second hand." << "\n";
        break;
    case PlayerCommand::InvalidP:
        std::cout << "Invalid command. Valid commands are: hit, hold." << "\n";
        break;
    }
}

void blackJack::Game::checkHand(std::shared_ptr<std::vector<Card>> hand, Person& person) {
    auto sum = sumHand(hand);
    if (sum == BLACKJACK) {
        std::cout << person.getName() << " has a blackjack!" << "\n";
        person.setStatus(Person::HandStatus::BlackJack);
    }
    else if (sum > BLACKJACK) {
        std::cout << person.getName() << " has busted!" << "\n";
        person.setStatus(Person::HandStatus::Busted);
    }
}

int blackJack::Game::sumHand(std::shared_ptr<std::vector<Card>> hand) {
    // Remove all ace values from hand and sum them
    auto sumWithoutAces = ranges::accumulate(*hand | ranges::views::transform([](Card card) { return card.getValue() <= 10 ? card.getValue() : 10; }) 
                                                    | ranges::views::filter([](int value) { return value != 1;}), 0);
    // Count all ace values in hand
    auto numAces = ranges::count(*hand | ranges::views::transform([](Card card) { return card.getValue(); }), 1);
    //BLACKJACK - sumWithoutAces - numAces is always positive so dividing by 10 will give floor result
    // x <= (21 - sumWithoutAces - numAces)/10
    // x + y = numAces
    if (numAces > 0) {
        auto x = (BLACKJACK - sumWithoutAces - numAces)/10;
        x = std::min(x, numAces);
        auto y = numAces - x;
        auto sumWithAces = sumWithoutAces + x * LARGE_ACE + y * SMALL_ACE;
        return sumWithAces;
    }
    else {
        return sumWithoutAces;
    }
}

bool blackJack::Game::checkSplit(Person &person) {
    auto hand = person.getHand();
    auto filter = [](Card LCard, Card RCard){ return LCard.getValue() != RCard.getValue(); };
    if (hand->size() == PAIR) {
        //Compares the two cards in hand to see if they have equal value
        if (ranges::adjacent_find(*hand, filter) == hand->end()) {
            return true;
        }
    }
    std::cout << "Invalid hand to split." << "\n";
    return false;
}

void blackJack::Game::checkWin(Player player, Dealer dealer) {
    if (player.getStatus() == Person::HandStatus::BlackJack) {
        std::cout << player.getName() << " wins!" << "\n";
    }
    else if (player.getStatus() == Person::HandStatus::Busted) {
        std::cout << player.getName() << " loses!" << "\n";
    }
    else if (dealer_.getStatus() == Person::HandStatus::Busted) {
        std::cout << player.getName() << " wins!" << "\n";
    }
    else {
        auto playerSum = sumHand(player.getHand());
        auto dealerSum = sumHand(dealer.getHand());
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

void blackJack::Game::checkSplitWin(Player player, Dealer dealer) {
    if (player.getSplitStatus() == Person::HandStatus::BlackJack) {
        std::cout << player.getName() << " wins!" << "\n";
    }
    else if (player.getSplitStatus() == Person::HandStatus::Busted) {
        std::cout << player.getName() << " loses!" << "\n";
    }
    else if (dealer.getStatus() == Person::HandStatus::Busted) {
        std::cout << player.getName() << " wins!" << "\n";
    }
    else {
        auto playerSum = sumHand(player.getSplitHand());
        auto dealerSum = sumHand(dealer.getHand());
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

int blackJack::Game::standingPlayers() const {
    auto num = ranges::accumulate(players_ 
             | ranges::view::transform([](Player player) { return player.getStatus() == Person::HandStatus::Standing ? 1 : 0; }),
                                  0);
    return num;
}

void blackJack::Game::addPlayer(const std::string name) {
    if (players_.size() < PLAYER_LIMIT) {
        auto player = Player(name);
        players_.push_back(player);
        std::cout << name << " has been added to the game." << "\n";
    }
    else {
        std::cout << "Player limit has been reached." << "\n";
    }
}

void blackJack::Game::removePlayer(const std::string name) {
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

void blackJack::Game::showPlayers() const {
    std::cout << "Dealer for this game is: " << dealer_.getName() << "\n";
    std::cout << "Players in the game are: " << "\n";
    for (auto player : players_) {
        std::cout << player.getName() << "\n";
    }
} 