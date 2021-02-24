#ifndef card_hpp
#define card_hpp

#include <random>
#include <unordered_map>


namespace blackJack {
    
class Card {
    public:
        Card(int value, std::string suit) : value_(value), suit_(suit) {} 
        int getValue() {return value_;}
        std::string getSuit() {return suit_;}
    private:
        int value_;
        std::string suit_;
};
}

#endif //card_hpp