#ifndef card_hpp
#define card_hpp

#define ACE 1
#define JACK 11
#define QUEEN 12
#define KING 13

#include <iostream>
#include <random>
#include <unordered_map>


namespace blackJack {
    
class Card {
    public:
        Card(int value, std::string suit) : value_(value), suit_(suit) {} 
        int getValue() const {return value_;}
        std::string getSuit() const {return suit_;}
        void showCard() const;
    private:
        int value_;
        std::string suit_;
};
}

#endif //card_hpp