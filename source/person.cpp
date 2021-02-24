#include "../include/person.hpp"

int blackJack::Person::sumHand() const {
    // Remove all ace values from hand and sum them
    auto sumWithoutAces = ranges::accumulate(*hand_ | ranges::views::transform([](Card card) { return card.getValue() <= 10 ? card.getValue() : 10; }) 
                                                    | ranges::views::filter([](int value) { return value != 1;}), 0);
    // Count all ace values in hand
    auto numAces = ranges::count(*hand_ | ranges::views::transform([](Card card) { return card.getValue(); }), 1);
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

void blackJack::Person::showHand() const {
    std::cout << name_ << " has the following cards: " << "\n";
    for (auto card : *hand_) {
        card.showCard();
    }
}
