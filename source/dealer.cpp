#include "../include/dealer.hpp"

void blackJack::Dealer::generateDeck() {
    if (deck_.size() != 0) {
        deck_.clear();
    }
    std::unordered_map<int, std::string> suitValues = {{1, "Diamonds"}, {2, "Clubs"}, {3, "Hearts"}, {4, "Spades"}};
    for (auto value = 1; value <= 13; ++value) {
        for (auto suit = 1; suit <= 4; ++ suit) {
            auto card = Card(value, suitValues.at(suit));
            deck_.push_back(card);
        }
    }
}

void blackJack::Dealer::shuffleDeck() {
    // Note that using time as a seed may pose security risks, consider changing
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine {seed};
    std::shuffle(std::begin(deck_), std::end(deck_), rng);
}

void blackJack::Dealer::deal(Person person) {
    auto card = deck_.back();
    auto hand = person.getHand();
    hand->push_back(card);
    deck_.pop_back();
    //std::cout << "Dealer dealt a " << card.getValue() << " of " << card.getSuit() << " to " << person.getName() << std::endl;
}

void blackJack::Dealer::setup() {
    setStatus(Person::PlayerStatus::Playing);
    generateDeck();
    shuffleDeck();
    auto hand = getHand();
    hand->clear();
}

void blackJack::Dealer::showDeck() {
    std::cout << "Dealer has the following cards in deck: " << "\n";
    for (auto card : deck_) {
        std::cout << "Card has value: " << card.getValue() << " and suit: " << card.getSuit() << "\n";
    }
}