#ifndef person_hpp
#define person_hpp

#define BLACKJACK 21
#define LARGE_ACE 11
#define SMALL_ACE 1
#define ACE 1
#define JACK 11
#define QUEEN 12
#define KING 13

#include "card.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <memory>

namespace blackJack {
class Person {
    public:
        Person() : name_{"Default"}, hand_ {std::make_shared<std::vector<Card>>()} {};
        Person(std::string name) : name_{name}, hand_ (std::make_shared<std::vector<Card>>()) {};
        enum HandStatus {
            Playing,
            Standing,
            Busted,
            BlackJack,
            Inactive
        };
        std::string getName() const {return name_;}
        std::shared_ptr<std::vector<Card>> getHand() const {return hand_;}
        void showHand() const;
        HandStatus getStatus() const { return status_ ;};
        void setStatus(HandStatus status) { status_ = status;};
    private:
        std::string name_; 
        std::shared_ptr<std::vector<Card>> hand_;
        HandStatus status_;
};
}

#endif //person_hpp