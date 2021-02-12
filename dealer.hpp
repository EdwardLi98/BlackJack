#ifndef dealer_hpp
#define dealer_hpp

#include "person.hpp"
#include "card.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

namespace blackJack {

class Dealer : public Person {
    public:
        using Person::Person;
        void deal(Person);
        void generateDeck();
        void addCardToDeck();
        void shuffleDeck(); 
        void showDeck(); // For debug purposes

    private:
        std::vector<Card> deck_;

};
}

#endif //dealer_hpp