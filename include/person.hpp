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
#include <range/v3/algorithm/count.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>

namespace blackJack {
class Person {
    public:
        Person() : name_{"Default"}, hand_ (std::make_shared<std::vector<Card>>()) {};
        Person(std::string name) : name_{name}, hand_ (std::make_shared<std::vector<Card>>()) {};
        enum PlayerStatus {
            Playing,
            Standing,
            Busted,
            BlackJack
        };
        std::string getName() const {return name_;}
        std::shared_ptr<std::vector<Card>> getHand() const {return hand_;}
        int sumHand() const;
        void showHand() const;
        PlayerStatus getStatus() const { return status_ ;};
        void setStatus(PlayerStatus status) { status_ = status;};
    private:
        std::string name_; 
        std::shared_ptr<std::vector<Card>> hand_;
        PlayerStatus status_;
};
}

#endif //person_hpp