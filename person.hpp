#ifndef person_hpp
#define person_hpp

#include "card.hpp"
#include <vector>
#include <iostream>
#include <memory>

namespace blackJack {
class Person {
    public:
        Person(std::string name) : name_{name}, hand_ (std::make_shared<std::vector<Card>>()) {};
        std::string getName() {return name_;}
        std::shared_ptr<std::vector<Card>> getHand() {return hand_;}
        void showHand();
    private:
        std::string name_; 
        std::shared_ptr<std::vector<Card>> hand_;
};
}

#endif //person_hpp